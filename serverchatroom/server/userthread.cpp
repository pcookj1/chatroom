/*****************************************************************
 * Filename: userthread.cpp
 *
 * Author: Patrick Cook
 * Start Date: 20 Aug 20
 *
 * Description: Implementation for UserThread class
 * Handles single client connection to server.
 * Runs thread which constantly reads from server socket.
 * Uses shared mutex to avoid race condition while accessing
 * a shared user list.
 * Validates client's sent username with regular expression.
 *      *Must be between 6-16 characters with no special characters.
 * Broadcasts client message to all users in shared user list.
 * Prepends the user's name to the beginning of their message before
 * sending to the client, with the exception of entry/exit messages.
 * User disconnect signaled by a recieved "/exit" message.
 * User can request the userlist with the "/usrlist" message
 * Handles destruction of itself during disconnect by
 * removing itself from shared userlist and ending thread.
 *
*****************************************************************/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <list>
#include <mutex>
#include <regex>
#include <string>
#include <thread>

#include "userthread.h"


UserThread::UserThread(int newClientSocket, socklen_t newClientLen,
                       struct sockaddr_in newClientAddress,
                       std::list<UserThread*> *serverUsers,
                       std::mutex *uMtx) {

    this->clientSocket = newClientSocket;
    this->clientLen = newClientLen;
    this->clientAddress = newClientAddress;
    this->usersPtr = serverUsers;
    this->usersMtx = uMtx;
}

const char *UserThread::getUsername() {

    return username;
}

void UserThread::setUserName(char *newUsername) {

    strcpy(username, newUsername);
    strtok(username, "\n");
}

UserThread::~UserThread() {
}

void UserThread::run() {

    clientThread = std::thread(&UserThread::handleUser, this);
}

//add failsafe to end connection if thread should terminate unexpectedly
void UserThread::handleUser() {

    std::cout << "Launched new user thread" << std::endl;
    int result;
    bool runClientThread = true;

    // Get Username from user, disconnect if fails
    if(!requestUsername()) {
        closeConnection();
        return;
    }
    sendActiveUsers();

    // Send welcome message to chatroom
    char message[BUF_SIZE];
    bzero(message, BUF_SIZE);
    strcpy(message, getUsername());
    strcat(message, " has joined the chat\n");
    broadcastMessage(message, false);

    while(runClientThread) {
        bzero(message, BUF_SIZE);
        result = read(clientSocket, message, BUF_SIZE-USERNAME_SIZE);

        try {
            if(result < 0)
                throw 6;
            else if(result == 0 || !strcmp(message, "/exit\n")) {
                runClientThread = false;
            } else if(!strcmp(message, "/usrlist\n")) {
                sendActiveUsers();
            } else {
                std::cout << "  User: " << getUsername() << " is about to broadcast()" << std::endl;
                broadcastMessage(message, true);
            }
        } catch (int e) {
            std::cout << "Error reading user's socket" << std::endl;
            runClientThread = false;
        }
    }

    // Broadcast exit message to remaining users
    std::cout << "  User: " << getUsername() << " has requested to disconnect" << std::endl;
    char exitMessage[BUF_SIZE];
    bzero(exitMessage, BUF_SIZE);
    strcpy(exitMessage, getUsername());
    strcat(exitMessage, " has left the chat\n");
    broadcastMessage(exitMessage, false);
    signalUserListDisconnection();
    closeConnection();
    std::cout << "Exiting thread: " << getUsername() << std::endl;
    //return;
}

void UserThread::broadcastMessage(char *message, bool appendUsrNmToMsg) {

    usersMtx->lock();

    std::cout << "Inside broadcast() message is \"" << message << "\"" <<std::endl;
    if(appendUsrNmToMsg)
        prependUserNameToMessage(message, getUsername());
    for(auto it = usersPtr->begin(); it != usersPtr->end(); ++it) {
        std::cout << "LOOP: connection to send to is: " << (*it)->getUsername() << std::endl;
        if(send((*it)->clientSocket, message, BUF_SIZE,0) < 0)
            std::cout << "Broadcast to user @" << (*it)->getUsername() << " failed" << std::endl;
    }
    usersMtx->unlock();
}

bool UserThread::isUserNameValid(char *usrNm) const {

    std::string userName(usrNm);
    char infoMessage[BUF_SIZE];
    bzero(infoMessage, BUF_SIZE);

    // Validate username (6-16 characters, numbers and letters)
    std::regex e("[a-zA-Z0-9]{6,16}");
    if(!std::regex_match(userName,e)) {
        strcpy(infoMessage, "[LOGINERROR] Username must be between 6-16 characters long with no special characters\n");
        try {
            if(send(clientSocket, infoMessage, BUF_SIZE,0) < 0)
                throw 7;
        } catch (int e) {
            std::cout << "Login error message failed to send" << std::endl;
        }
        return false;
    }

    // Check if username is taken
    usersMtx->lock();
    for(auto it = usersPtr->begin(); it != usersPtr->end(); ++it) {
        std::cout << "Current user is: " << (*it)->getUsername() << std::endl;
        if(std::string((*it)->getUsername()) == userName) {
            std::cout << "Username already taken" << std::endl;
            strcpy(infoMessage, "[LOGINERROR] Username already taken\n");
            try {
                if(send(clientSocket, infoMessage, BUF_SIZE,0) < 0)
                    throw 7;
            } catch (int e) {
                std::cout << "Login error message failed to send" << std::endl;
            }
            usersMtx->unlock();
            return false;
        }
    }
    usersMtx->unlock();

    strcpy(infoMessage, "[LOGINSUCCESS]\n");
    try {
        if(send(clientSocket, infoMessage, BUF_SIZE,0) < 0)
            throw 8;
    } catch (int e) {
        std::cout << "Login Success message failed to send" << std::endl;
        return false;
    }
    return true;
}

bool UserThread::requestUsername() {

    std::cout << "Requesting username\n" << std::endl;
    char receivedUsername[USERNAME_SIZE];
    bzero(receivedUsername, USERNAME_SIZE);

    try {
        if(!read(clientSocket, receivedUsername, USERNAME_SIZE)) {
            throw 9;
        } else if(isUserNameValid(receivedUsername)) {
            setUserName(receivedUsername);
            std::cout << "Connection @: " << clientAddress.sin_port << " has username: " << getUsername() << std::endl;
            return true;
        }
    } catch (int e) {
        std::cout << "Failed to get username: connection failed. Disconnecting" << std::endl;
        return false;
    }
}

//TO DO: change to use broadcastMessage()
void UserThread::sendActiveUsers() {

    usersMtx->lock();

    std::cout << "Sending user list" << std::endl;
    char userNameToSend[BUF_SIZE];
    for(auto it = usersPtr->begin(); it != usersPtr->end(); ++it) {
        std::cout << "Attempting to send "<< (*it)->getUsername() << std::endl;
        for(auto it2 = usersPtr->begin(); it2 != usersPtr->end(); ++it2) {
            bzero(userNameToSend, BUF_SIZE);
            strcat(userNameToSend, "[USRADD]");
            strcat(userNameToSend, (*it2)->getUsername());
            strcat(userNameToSend, "\n");
            if(send((*it)->clientSocket, userNameToSend, BUF_SIZE,0) > 0)
                std::cout << "Sent user " << getUsername() << " the username: " << (*it)->getUsername() << std::endl;
        }
    }
    usersMtx->unlock();
}

void UserThread::signalUserListDisconnection() {

    char exitUser[BUF_SIZE];
    bzero(exitUser, BUF_SIZE);
    strcat(exitUser, "[USRDEL]");
    strcat(exitUser, getUsername());
    strcat(exitUser, "\n");
    broadcastMessage(exitUser, false);
}

//make so prepending the username doesn't cause message buffer overflow
void UserThread::closeConnection() {

    std::cout << "Closing connection. " << std::endl;
    close(clientSocket);

    usersMtx->lock();
    usersPtr->remove(this);
    std::cout << "Userlist after disconnection:" << std::endl;

    for(auto it = usersPtr->begin(); it != usersPtr->end(); ++it) {
        if((*it)->getUsername() == getUsername()){
            std::cout << "Found the username even after deleting" << std::endl;
        }
        std::cout << "@" << (*it)->getUsername() << std::endl;
    }
    usersMtx->unlock();

    clientThread.detach();
    delete this;
    std::cout << "Exiting thread hopefully" << std::endl;
}

void UserThread::prependUserNameToMessage(char* msg, const char* usr) {

    char tempMessage[BUF_SIZE];
    bzero(tempMessage, BUF_SIZE);
    strcat(tempMessage, "<");
    strcat(tempMessage, usr);
    strcat(tempMessage, "> ");
    strcat(tempMessage, msg);
    strcpy(msg, tempMessage);
}
