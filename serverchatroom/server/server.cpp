/*****************************************************************
 * Filename: server.cpp
 *
 * Author: Patrick Cook
 * Start Date: 20 Aug 20
 *
 * Description: Implementation for Server class
 * Operates on single thread which listens to incoming connections.
 * Accepts incoming connection and creates UserThread object to handle it.
 * Maintains a list of UserThreads ptrs to be shared with all UserThreads.
 *      * Uses mutex shared by all UserThread objects to avoid race condition
 *      * while accessing shared user list.
 *
*****************************************************************/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <list>
#include <mutex>

#include "server.h"
#include "userthread.h"


Server::Server(const char *nIp, int nPort) {

    this->ip = nIp;
    this->port = nPort;
    std::cout << "Server Initiating at " << ip << ":" << port << std::endl;
}

void Server::initServer() {

    try {
        listenSocket = socket(AF_INET, SOCK_STREAM, 0);
        if(listenSocket < 0)
            throw 1;
    } catch(int e) {
        std::cout << "Server socket could not be opened. Exiting Server" << std::endl;
        return;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(ip);
    serverAddress.sin_port = htons(port);

    try {
        if(bind(listenSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
            throw 2;
    } catch (int e) {
        std::cout << "Server socket could not be binded. Exiting Server" << std::endl;
        return;
    }
    std::cout << "Server socket binded..." << std::endl;
    std::cout << "------------------------------" << std::endl;
}

void Server::startServer() {

    try {
        if(listen(listenSocket,1) < 0)
            throw 3;
    } catch (int e) {
        std::cout << "Error listening to socket. Exiting Server" << std::endl;
        return;
    }
    handleNewConnections();
}

//Main thread to to accept new users and spawn new threads to handle clients
void Server::handleNewConnections() {

    struct sockaddr_in nClientAddress;
    socklen_t nClientLen = sizeof(nClientAddress);
    int nClientSocket;

    while(1) {
        try {
            nClientSocket = accept(listenSocket, (struct sockaddr *) &nClientAddress, &nClientLen);
            if(nClientSocket < 0)
                throw 4;
        } catch (int e){
            std::cout << "Error accepting socket. Proceeding to accept new clients" << std::endl;
            continue;
        }

        try {
            UserThread *user = new UserThread(nClientSocket, nClientLen, nClientAddress, &users, &usersMutex);
            usersMutex.lock();
            users.push_back(user);
            usersMutex.unlock();
            user->run();
        } catch (const std::bad_alloc&) {
            std::cout << "Memory allocation for new user failed. Exiting Server" << std::endl;
            return;
        }
    }
}

Server::~Server() {

    close(listenSocket);
}










