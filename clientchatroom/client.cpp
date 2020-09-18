/*****************************************************************
 * Filename: client.cpp
 *
 * Author: Patrick Cook
 * Start Date: 20 Aug 20
 *
 * Description: Implementation for Client class
 * Handles connecting, disconnecting to server socket
 * Signals ChatRoom if a message has arrived and if the server
 * has disconnected
 *
*****************************************************************/

#include <QByteArray>
#include <QObject>
#include <QRegularExpression>
#include <QString>
#include <QTcpSocket>

#include "client.h"

Client::Client(QObject *parent) : QObject(parent) {

    clientSocket = new QTcpSocket(this);

    // Forward QTcpSocket connect/disconnect signals
    connect(clientSocket, SIGNAL(connected()),
            this, SIGNAL(connected()));
    connect(clientSocket, SIGNAL(disconnected()),
            this, SIGNAL(disconnected()));

    // Connect QTcpSocket ReadyRead signal to message handler
    connect(clientSocket, SIGNAL(readyRead()),
            this, SLOT(processMessage()));

    // Forward the QTcpSocket SocketError signal to error signal
    connect(clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &Client::error);
}

Client::~Client() {

    delete clientSocket;
}

void Client::connectToServer(QString &serverIp, quint16 serverPort) {

    clientSocket->connectToHost(serverIp, serverPort);
}

void Client::login(const QString &userName) {

    if(userName.isEmpty())
        return;

    if(clientSocket->state() == QAbstractSocket::ConnectedState)
        clientSocket->write(userName.toUtf8());
}

void Client::sendMessage(const QString &msg) {

    if(msg.isEmpty())
        return;

    clientSocket->write(msg.toUtf8());
}

void Client::disconnectFromServer() {

    clientSocket->disconnectFromHost();
}

void Client::processMessage() {

    QByteArray message;
    while(clientSocket->canReadLine()) {
        message = clientSocket->read(BUF_SIZE);

        //Remove extra null characters from fixed buffer
        QString processedMsg = QString::fromStdString(message.toStdString());
        processedMsg = processedMsg.remove(QChar::Null);
        processedMsg = processedMsg.remove("\n");

        if(processedMsg.startsWith("<")) {
            QRegularExpression re("^<([^<>]+)>");
            QRegularExpressionMatch matchUserName = re.match(processedMsg);
            QString user = matchUserName.captured(1);
            emit messageReceived(user, processedMsg);
        } else if(processedMsg.startsWith("[LOGINERROR]")) {
            emit loginFailed(processedMsg.remove(0,13));
        } else if(processedMsg.startsWith("[LOGINSUCCESS]")) {
            emit loggedIn();
        } else if(processedMsg.startsWith("[USRADD]")) {
            emit addUser(processedMsg.remove(0,8));
        } else if(processedMsg.startsWith("[USRDEL]")){
            emit deleteUser(processedMsg.remove(0,8));
        } else {
            emit messageReceived("", processedMsg);
        }
    }
}
