/*****************************************************************
 * Filename: chatroom.cpp
 *
 * Author: Patrick Cook
 * Start Date: 20 Aug 20
 *
 * Description: Implementation for ChatRoom class
 * Handles data displayed on the GUI.
 * Uses Client object to read and send messages.
 * Displays user messages in the chat window and updates the GUI
 * user list accordingly.
 * Applys random color to each user and their message
 * Leaves username validation to the server
 * Displays socket errors/login errors in the GUI
 *
*****************************************************************/

#include <QByteArray>
#include <QRegularExpression>
#include <QString>
#include <QTcpSocket>
#include <QWidget>

#include "chatroom.h"
#include "client.h"
#include "ui_chatroom.h"

ChatRoom::ChatRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatRoom) {

    this->client = new Client(this);
    ui->setupUi(this);
    this->setCentralWidget(ui->centralWidget);
    ui->stackedWidget->setCurrentIndex(0);

    // Connect buttons
    connect(ui->submitLoginInput, SIGNAL(clicked()),
            this, SLOT(attemptConnection()));
    connect(ui->submitMsgButton, SIGNAL(clicked()),
            this, SLOT(sendMessage()));

    // Allow keyboard return to submit login/messages
    connect(ui->userMsgInput, SIGNAL(returnPressed()),
            this, SLOT(sendMessage()));
    connect(ui->inputUsername, SIGNAL(returnPressed()),
            this, SLOT(attemptConnection()));
    connect(ui->inputServerName, SIGNAL(returnPressed()),
            this, SLOT(sendMessage()));

    // Connect client connect/disconnect signal to slots
    connect(client, SIGNAL(connected()),
                this, SLOT(connectedToServer()));
    connect(client, SIGNAL(disconnected()),
                this, SLOT(disconnectedFromServer()));

    // Connect client message signal to handler
    connect(client, SIGNAL(messageReceived(QString,QString)),
                this, SLOT(messageReceived(QString,QString)));

    // Connect login signals
    connect(client, SIGNAL(loggedIn()),
                this, SLOT(loggedIn()));
    connect(client, SIGNAL(loginFailed(QString)),
                this, SLOT(loginFailed(QString)));

    // Connect slots/signals for adding/deleting users to GUI
    connect(client, SIGNAL(addUser(QString)),
                this, SLOT(addUser(QString)));
    connect(client, SIGNAL(deleteUser(QString)),
                this, SLOT(deleteUser(QString)));

    // Connect client socketError signal to slot
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(error(QAbstractSocket::SocketError)));

}

ChatRoom::~ChatRoom() {

    delete client;
    delete ui;
}

void ChatRoom::attemptConnection() {

    QString address = ui->inputServerName->text();
    QRegularExpression re("(.*):(.*)");
    QRegularExpressionMatch match = re.match(address);
    QString ip = match.captured(1);
    QString port = match.captured(2);

    client->connectToServer(ip, port.toUInt());
}

void ChatRoom::connectedToServer() {

    QString userName = ui->inputUsername->text();
    if(userName.isEmpty()) {
        client->disconnectFromServer();
        return;
    }
    tryLogin(userName);
}

void ChatRoom::tryLogin(const QString &userName) {

    client->login(userName);
}

void ChatRoom::loggedIn() {

    ui->stackedWidget->setCurrentIndex(1);
    ui->loginErrorLabel->clear();
}

void ChatRoom::loginFailed(const QString &error) {

    ui->loginErrorLabel->setText(error);
}

void ChatRoom::messageReceived(const QString &user, const QString &msg) {

    // Display server entry/exit messages
    if(user.isEmpty()) {
        ui->chatWindow->setTextColor(Qt::black);
        ui->chatWindow->setFontItalic(true);
        ui->chatWindow->append(msg);
        ui->chatWindow->setFontItalic(false);
        return;
    }

    // Find user in the user list and grab their font color
    auto listOfUsers = ui->userList->findItems(user, Qt::MatchExactly);
    for(auto itUser : listOfUsers) {
        if(itUser->text() == user) {
            QColor userColor = itUser->foreground().color();
            ui->chatWindow->setTextColor(userColor);
            ui->chatWindow->append(msg);
            return;
        }
    }
}

void ChatRoom::sendMessage() {

    QString message = ui->userMsgInput->text();
    client->sendMessage(message.append("\n"));
    ui->userMsgInput->clear();
}

void ChatRoom::disconnectedFromServer() {

    // Return to login screen
    ui->chatWindow->clear();
    ui->userList->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void ChatRoom::addUser(const QString &user) {

    auto listOfUsers = ui->userList->findItems(user, Qt::MatchExactly);
    for(auto itUser : listOfUsers) {
        if(itUser->text() == user) {
            return;
        }
    }
    ui->userList->addItem(user);

    // Generate random RGB font color for their username/messages
    ui->userList->item(ui->userList->count()-1)->setForeground(QColor(rand()%150, rand()%200, rand()%175));
}

void ChatRoom::deleteUser(const QString &user){

    auto listOfUsers = ui->userList->findItems(user, Qt::MatchExactly);
    for(auto itUser : listOfUsers) {
        delete itUser;
    }
}

void ChatRoom::error(QAbstractSocket::SocketError socketError) {

    QString errorMsg;
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            return;
        case QAbstractSocket::ProxyConnectionClosedError:
            errorMsg = "Proxy Connection Closed";
            qInfo() << errorMsg;
            return; // handled by disconnectedFromServer
        case QAbstractSocket::ConnectionRefusedError:
            errorMsg = "Connection Refused";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::ProxyConnectionRefusedError:
            errorMsg = "Proxy Connection Refused";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::ProxyNotFoundError:
            errorMsg = "Proxy Not Found Error";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::HostNotFoundError:
            errorMsg = "Host Not Found Error";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::SocketAccessError:
            errorMsg = "Socket Access Error";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::SocketResourceError:
            errorMsg = "Socket Resource Error";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::SocketTimeoutError:
            errorMsg = "Socket Timeout Error";
            qInfo() << errorMsg;
            return;
        case QAbstractSocket::ProxyConnectionTimeoutError:
            errorMsg = "Proxy Connection Timeout Error";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::NetworkError:
            errorMsg = "Network Error";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::UnknownSocketError:
            errorMsg = "Unknown Socket Error";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::UnsupportedSocketOperationError:
            errorMsg = "Unsupported Socket Operation";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::ProxyAuthenticationRequiredError:
            errorMsg = "Proxy Authentication Error";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::ProxyProtocolError:
            errorMsg = "Proxy Protocol Error";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::TemporaryError:
            errorMsg = "Temporary Socket Error";
            qInfo() << errorMsg;
            break;
        case QAbstractSocket::OperationError:
            errorMsg = "Socket Operation Error";
            qInfo() << errorMsg;
            return;
        default:
            Q_UNREACHABLE();
    }
    ui->loginErrorLabel->setText(errorMsg);
}
