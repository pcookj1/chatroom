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
 *
*****************************************************************/

#include <QByteArray>
#include <QRegularExpression>
#include <QString>
#include <QTcpSocket>
#include <QWidget>

#include "chatroom.h"
#include "ui_mainwindow.h"
#include "client.h"


ChatRoom::ChatRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatRoom) {

    this->client = new Client();
    ui->setupUi(this);
    //ui->inputServerName->setInputMask("000.0.0.0");
    this->setCentralWidget(ui->centralWidget);
    ui->stackedWidget->setCurrentIndex(0);


    // Allow keyboard return to submit login/messages
    connect(ui->userMsgInput, SIGNAL(returnPressed()),
            this, SLOT(submitChatMessage()));
    connect(ui->inputUsername, SIGNAL(returnPressed()),
            this, SLOT(submitLoginInfo()));
    // Connect client disconnect signal to handler
    connect(client, SIGNAL(serverHasDisconnected()),
                this, SLOT(exitServerPage()));
    // Connect client message signal to handler
    connect(client, SIGNAL(messageReady()),
                this, SLOT(onMessageToProcess()));

    connect(client, SIGNAL(serverHasConnected()),
                this, SLOT(loginSuccessful()));

    connect(client, SIGNAL(serverCannotConnect()),
                this, SLOT(loginUnsuccessful()));
}

ChatRoom::~ChatRoom() {

    delete client;
    delete ui;
}

void ChatRoom::onMessageToProcess() {
    qInfo() << "Entering onMessageToProcess";
    while(client->clientSocket->canReadLine()) {
        QByteArray message = client->readMessage();

        //Remove extra null characters from fixed buffer
        QString processedMsg = QString::fromStdString(message.toStdString());
        processedMsg = processedMsg.remove(QChar::Null);
        processedMsg = processedMsg.remove("\n");

        if(processedMsg.startsWith("[LOGINERROR]")) {
            qInfo() << "LOGINERROR";
            ui->loginErrorLabel->setText(processedMsg.remove(0,13));
            qInfo() << "Appended login error message to label";
        } else if(processedMsg.startsWith("[LOGINSUCCESS]")) {
            ui->stackedWidget->setCurrentIndex(1);
            ui->loginErrorLabel->clear();
        } else if(processedMsg.startsWith("[USR")) {
            handleUserList(processedMsg);
        } else {
            addMessageToChatRoom(&processedMsg);
        }
    }
}

void ChatRoom::exitServerPage() {
    qInfo() << "inside exitServerPage";
    ui->chatWindow->clear();
    ui->userList->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void ChatRoom::submitLoginInfo() {
    qInfo() << "Login info submitted";
    QString address = ui->inputServerName->text();
    QString userName = ui->inputUsername->text();

    QRegularExpression re("(.*):(.*)");
    QRegularExpressionMatch match = re.match(address);
    QString ip = match.captured(1);
    QString port = match.captured(2);

    if(userName.isEmpty()) {
        ui->loginErrorLabel->setText("You must enter a username");
    } else {
        client->connectToServer(ip, port.toUInt());
    }
    /* } else if(client->connectToServer(ip, port.toUInt())) {
        ui->chatWindowLabel->setText(ip);
        client->sendMessage(userName);
    } else {
        qInfo() << "server address is wrong";
        ui->loginErrorLabel->setText("Server address is not valid");
    } */
    qInfo() << "exiting submitLoginInfo";
}

void ChatRoom::loginSuccessful() {

    QString userName = ui->inputUsername->text();
    client->sendMessage(userName);
}

void ChatRoom::loginUnsuccessful() {

    qInfo() << "server address is wrong";
     client->clientSocket->disconnectFromHost();
    //ui->loginErrorLabel->setText("Error");
}

void ChatRoom::submitChatMessage() {
 qInfo() << "Entering submitChatMessage";
    QString message = ui->userMsgInput->text();
    client->sendMessage(message.append("\n"));
    ui->userMsgInput->clear();

}

void ChatRoom::handleUserList(QString newUser) {
    qInfo() << "Entering handleUserList";
    if(newUser.startsWith("[USRDEL]")) {
        newUser.remove("[USRDEL]");
        auto listOfUsers = ui->userList->findItems(newUser, Qt::MatchExactly);
        for(auto user : listOfUsers) {
            delete user;
        }
    } else {
        newUser.remove("[USRADD]");
        auto listOfUsers = ui->userList->findItems(newUser, Qt::MatchExactly);
        for(auto user : listOfUsers) {
            if(user->text() == newUser) {
                return;
            }
        }
        ui->userList->addItem(newUser);
        // Generate random RGB color for their username/messages
        ui->userList->item(ui->userList->count()-1)->setForeground(QColor(rand()%150, rand()%200, rand()%175));
    }
}

void ChatRoom::addMessageToChatRoom(QString *msg) {
     qInfo() << "Entering addMessageToChatRoom";
    // Match the username prefix from message
    QRegularExpression re("^<([^<>]+)>");
    QRegularExpressionMatch matchMsgOwner = re.match(*msg);
    QString msgOwner = matchMsgOwner.captured(1);

    // Grab user's font color from the user table to apply it to their message
    auto listOfUsers = ui->userList->findItems(msgOwner, Qt::MatchExactly);
    for(auto user : listOfUsers) {
        if(user->text() == msgOwner) {
            QColor userColor = user->foreground().color();
            ui->chatWindow->setTextColor(userColor);
            ui->chatWindow->append(*msg);
            return;
        }
    }
    ui->chatWindow->setTextColor(Qt::black);
    ui->chatWindow->setFontItalic(true);
    ui->chatWindow->append(*msg);
    ui->chatWindow->setFontItalic(false);
}
