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
#include <thread>

#include "server.h"
#include "serverthreads.h"


Server::Server(int port, const char *ip) {
    this->port = port;
    this->ip = ip;
    std::cout << "Server: Initiated port " << port << " @ " << ip << std::endl;
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

/* void Server::startServer() {
    if(listen(listenSocket,1) < 1)
        perror( "Error listening to socket");
    clientLen = sizeof(clientAddress);
    clientSocket = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientLen);
    if(clientSocket < 0)
        perror( "Error accepting socket");
    std::cout << "Socket accepted..." << std::endl;
} */

void Server::startServer() {
    if(listen(listenSocket,5) < 0)
        perror( "Error listening to socket");
    entry = std::thread(&Server::handleNewUsers, this);
    entry.join();
    broadcastMessages("Welcome");
    //handleNewUsers();
}
/*
void Server::readServer() {
    // start threads here which 1) handle new users 2) multicast incoming messages
    read(clientSocket, message, 255);
    std::cout << "The message is: " << message << std::endl;
} */

//Thread function for broadcasting messages to all users
void Server::broadcastMessages(char *message) {
    std::list<User>::iterator connection;
    //make atomic so everyone receives message in same order? or not important?
    for(connection = users.begin(); connection != users.end(); ++connection) {
        //std::cout << "connection to send to is: " << connection->clientAddress.sin_port << std::endl;
        send(connection->clientSocket, message, BUF_SIZE,0);
    }
}
void Server::userThread(User const *connection) {
    int result;
    std::cout << "Launched new user thread for port " << connection->clientAddress.sin_port << std::endl;
    while(1) {
        result = read(connection->clientSocket, message, 255);
        if(result < 0)
            perror("Error reading user's socket\n");
        else if(result == 0)
            continue;
        std::cout << "Attemping to broadcast received message:" << std::endl;
        std::cout << message << std::endl;
        broadcastMessages(message);
    }
}

//TO DO: check user message in user thread code and close connection upon request.
//also, check result in userThread, the value probably indicates whether a connection abruptly closed also
void Server::userExit() {

}

//Thread function to accept new users
void Server::handleNewUsers() {
    socklen_t clientLen;
    struct sockaddr_in clientAddress;
    int clientSocket;
    while(1) {
        clientSocket = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientLen);
        if(clientSocket < 0)
            perror( "Error accepting socket");
        //Move thread to User class and start thread during construction
        User newUser(clientSocket, clientLen, clientAddress);
        users.push_back(newUser);
        //spawn new thread for each user
        userThreads.push_back(std::thread(&Server::userThread, this, &newUser));
    }
}

Server::~Server() {
}

// USER CLASS
User::User(int clientSocket, socklen_t clientLen, struct sockaddr_in clientAddress) {
    this->clientSocket = clientSocket;
    this->clientLen = clientLen;
    this->clientAddress = clientAddress;
}

User::~User() {
}










