/*****************************************************************
 * Filename: chatroom.h
 *
 * Author: Patrick Cook
 * Start Date: 20 Aug 20
 *
 * Description: Interface for ChatRoom class
 * Includes slots for handling button events on GUI, handling receieved messages,
 * and exiting the server when a disconnection occurs.
 * Includes instance of Client class to handle actual message transfer to server
 *
*****************************************************************/

#ifndef CHATROOM_H
#define CHATROOM_H

#include <QMainWindow>
#include <QString>

#include "client.h"

namespace Ui {
class ChatRoom;
}

class ChatRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = 0);
    ~ChatRoom();
private slots:
    void attemptConnection();
    void connectedToServer();
    void tryLogin(const QString &userName);
    void loggedIn();
    void loginFailed(const QString &error);
    void messageReceived(const QString &user, const QString &msg);
    void sendMessage();
    void disconnectedFromServer();
    void addUser(const QString &user);
    void deleteUser(const QString &user);
    void error(QAbstractSocket::SocketError socketError);
private:
    Ui::ChatRoom *ui;
    Client *client;
};

#endif // CHATROOM_H
