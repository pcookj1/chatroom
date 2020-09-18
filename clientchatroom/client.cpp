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
#include <QString>
#include <QTcpSocket>

#include "client.h"


Client::Client(QObject *parent) : QObject(parent) {

    clientSocket = new QTcpSocket(this);

    // Connect QTcpSocket signals to slots
    connect(clientSocket, SIGNAL(readyRead()),
            this, SLOT(notifyServerOfMessage()));
    connect(clientSocket, SIGNAL(disconnected()),
            this, SLOT(onDisconnectSocket()));
    connect(this, SIGNAL(disconnectSocket()),
            this, SLOT(onDisconnectSocket()));
    connect(clientSocket, SIGNAL(connected()),
            this, SIGNAL(serverHasConnected()));
    connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SIGNAL(serverCannotConnect()));
}

void Client::connectToServer(QString &serverIp, quint16 serverPort) {
    qInfo() << "Entering connectToServer";
    clientSocket->connectToHost(serverIp, serverPort);
    //return clientSocket->waitForConnected(LOGIN_TIMEOUT);
    qInfo() << "Exiting connectToServer";
}

bool Client::sendMessage(QString msg) {
    qInfo() << "inside sendMessage";
    if(msg.startsWith("/exit")) {
        qInfo() << "user requested to disconnect socket";
        emit disconnectSocket();
        return false;
    }

    if(clientSocket->state() == QAbstractSocket::ConnectedState) {
        clientSocket->write(msg.toUtf8());
        return clientSocket->waitForBytesWritten();
    } else {
        return false;
    }
}

QByteArray Client::readMessage() {
    qInfo() << "inside readMessage";
    QByteArray message;
    message = clientSocket->read(BUF_SIZE);
    return message;
}

void Client::onDisconnectSocket() {
    qInfo() << "Entering disconnectSocket";
    clientSocket->disconnectFromHost();
    qInfo() << "Exiting disconnectSocket";
    emit serverHasDisconnected();
}

void Client::notifyServerOfMessage() {
    qInfo() << "notifying server of message";
    emit messageReady();
}

Client::~Client() {

    delete clientSocket;
}
