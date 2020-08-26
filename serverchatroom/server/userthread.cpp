#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <list>
#include <mutex>
#include <thread>

#include "userthread.h"

#define BUF_SIZE 255
#define USERNAME_SIZE 16

UserThread::UserThread(int newClientSocket, socklen_t newClientLen,
                       struct sockaddr_in newClientAddress,
                       std::list<UserThread*> *serverUsers, std::mutex *uMtx) {
    this->clientSocket = newClientSocket;
    this->clientLen = newClientLen;
    this->clientAddress = newClientAddress;
    this->users = serverUsers;
    this->usersMtx = uMtx;
}

UserThread::~UserThread() {
}

void UserThread::run() {
    clientThread = std::thread(&UserThread::handleUser, this);
}

//add failsafe to end connection if thread should terminate unexpectedly
void UserThread::handleUser() {
    int result;
    char message[BUF_SIZE];
    bool runClientThread = true;
    requestUsername();
    strcpy(message, getUsername());
    strcat(message, " has joined the chat");
    broadcastMessage(message);
    std::cout << "Launched new user thread for user " << getUsername()<< std::endl;
    while(runClientThread) {
        bzero(message,BUF_SIZE);
        result = read(clientSocket, message, 255);
        if(result < 0) {
            perror("Error reading user's socket\n");
            runClientThread = false;
        } else if(result == 0 || !strcmp(message, "exit\n")) {
            runClientThread = false;
        } else {
            std::cout << "  User: " << getUsername() << "user is about to broadcast()" << std::endl;
            broadcastMessage(message);
        }
    }
    std::cout << "  User: " << getUsername() << "has requested to disconnect" << std::endl;
    closeConnection();
}

void UserThread::closeConnection() {
    std::cout << "Closing connection @ username: " << getUsername()<< std::endl;
    close(clientSocket);
    clientThread.detach();
    usersMtx->lock();
    users->remove(this);
    usersMtx->unlock();
    delete this;
}

void UserThread::broadcastMessage(char const *message) {
    usersMtx->lock();
    std::cout << "Inside broadcast() message is \"" << message << "\"" <<std::endl;
    //make atomic so everyone receives message in same order? or not important?
    for(std::list<UserThread*>::iterator it = users->begin(); it != users->end(); ++it) {
        std::cout << "LOOP: connection to send to is: " << (*it)->getUsername() << std::endl;

        //check if send succeeds, if not then connection closed unexpectedly
        //doesn't actually return useful info so UNDO this condition check
        if(send((*it)->clientSocket, message, BUF_SIZE,0) < 0)
            //perror("Broadcast to this connection failed");
            std::cout << "Broadcast to user @" <<(*it)->getUsername() << " failed" << std::endl;
    }
    usersMtx->unlock();
}

void UserThread::requestUsername() {
    std::cout << "Requesting username\n" << std::endl;
    char receivedUsername[USERNAME_SIZE];
    char greeting[BUF_SIZE];
    bzero(greeting, BUF_SIZE);
    bzero(receivedUsername, BUF_SIZE);
    strcpy(greeting,"Please send username");
    if(send(clientSocket, greeting, BUF_SIZE,0) < 0)
        perror("Request for username failed");
    read(clientSocket, receivedUsername, USERNAME_SIZE);
    //routine to check if valid username or exists already, yada yada
    char *temp;
    if((temp=strchr(receivedUsername, '\n')) != NULL)
        *temp = '\0';
    setUsername(receivedUsername);
    //runClientThread = false;
    std::cout << "Connection @: " << clientAddress.sin_port << " has username: " << getUsername() << std::endl;
}
