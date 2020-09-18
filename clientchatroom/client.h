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
    void connectToServer(QString &serverIp, quint16 serverPort);
    bool sendMessage(QString msg);
    QByteArray readMessage();
    QTcpSocket *clientSocket;
signals:
    void serverHasDisconnected();
    void serverHasConnected();
    void serverCannotConnect();
    void messageReady();
    void disconnectSocket();
private slots:
    void onDisconnectSocket();
    void notifyServerOfMessage();
};


#endif // CLIENT_H
