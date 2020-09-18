/*****************************************************************
 * Filename: client.h
 *
 * Author: Patrick Cook
 * Start Date: 20 Aug 20
 *
 * Description: Interface for Client class
 * Handles client connection to server, message sending and reading,
 * signaling the ChatWindow when a message has arrived, and signaling
 * when the server has disconnected
 *
*****************************************************************/

#ifndef CLIENT_H
#define CLIENT_H

#include <QByteArray>
#include <QObject>
#include <QString>
#include <QTcpSocket>

#define BUF_SIZE 255
#define LOGIN_TIMEOUT 2000


class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
public slots:
    void connectToServer(QString &serverIp, quint16 serverPort);
    void login(const QString &userName);
    void sendMessage(const QString &msg);
    void disconnectFromServer();
private slots:
    void processMessage();
signals:
    void connected();
    void loggedIn();
    void loginFailed(const QString &error);
    void disconnected();
    void messageReceived(const QString &user, const QString &msg);
    void addUser(const QString &user);
    void deleteUser(const QString &user);
    void error(QAbstractSocket::SocketError socketError);
private:
      QTcpSocket *clientSocket;
};


#endif // CLIENT_H
