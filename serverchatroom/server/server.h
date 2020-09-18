/*****************************************************************
 * Filename: server.h
 *
 * Author: Patrick Cook
 * Start Date: 20 Aug 20
 *
 * Description: Interface for Server class
 * Provides members for starting the server,
 * storing the server socket information, storing current users,
 * and spawning a threads to handle user connections
 *
*****************************************************************/

#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>

#include <list>
#include <mutex>
#include <thread>

#include "userthread.h"


class Server {
public:
    Server(const char *nIp, int nPort);
    void initServer();
    void startServer();
    ~Server();
private:
    int port;
    const char *ip;
    int listenSocket;
    struct sockaddr_in serverAddress;
    std::list<UserThread*> users;
    std::mutex usersMutex;
    void handleNewConnections();
};

#endif // SERVER_H
