/*  Patrick Cook
 *  Implementation for Server component of chat room
 *  8/18/20
 *
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <list>
#include <mutex>
#include <thread>

#include "server.h"
#include "userthread.h"

#define USERNAME_SIZE 16
//GET RID OF SHADOW VARIABLES
//Stick read (and write?) into loops to get all data

Server::Server(int nPort, const char *nip) {
    this->port = nPort;
    this->ip = nip;
    std::cout << "Server Initiating at " << ip << ":" << port << std::endl;
}

void Server::initServer() {
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSocket < 0)
        perror( "Socket could not be opened");

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(ip);
    serverAddress.sin_port = htons(port);

    if(bind(listenSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
        perror( "Error binding the socket");
    std::cout << "Server socket binded..." << std::endl;
    std::cout << "------------------------------" << std::endl;
}

void Server::startServer() {
    if(listen(listenSocket,5) < 0)
        perror( "Error listening to socket");
    handleNewConnections();
}

//Main thread to to accept new users and spawn new thread to handle clients
void Server::handleNewConnections() {
    socklen_t nClientLen;
    struct sockaddr_in nClientAddress;
    int nClientSocket;
    //make while(!quitServer) to end it
    while(1) {
        nClientSocket = accept(listenSocket, (struct sockaddr *) &nClientAddress, &nClientLen);
        if(nClientSocket < 0) {
            perror( "Error accepting socket");
            continue;
        }
        std::cout << "About to enter new user in main thread" <<std::endl;

        UserThread *user = new UserThread(nClientSocket, nClientLen, nClientAddress, &users, &usersMutex);
        usersMutex.lock();
        users.push_back(user);
        usersMutex.unlock();
        user->run();
    }
}

Server::~Server() {
}










