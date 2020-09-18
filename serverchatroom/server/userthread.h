/*****************************************************************
 * Filename: userthread.h
 *
 * Author: Patrick Cook
 * Start Date: 20 Aug 20
 *
 * Description: Interface for UserThread class
 * Includes members for managing the socket connection
 * and for starting a thread to send and recieve messages
 * as well as remove itself from a shared user list
 *
*****************************************************************/

#ifndef USERTHREAD_H
#define USERTHREAD_H

#include <netinet/in.h>
#include <sys/socket.h>

#include <list>
#include <mutex>
#include <thread>

#define BUF_SIZE 255
#define USERNAME_SIZE 16


class UserThread {
public:
    UserThread(int newClientSocket, socklen_t newClientLen,
               struct sockaddr_in newClientAddress,
               std::list<UserThread*> *serverUsers, std::mutex *uMtx);
     ~UserThread();
    void run();
    const char *getUsername();
    void setUserName(char *newUsername);
    int clientSocket;
    socklen_t clientLen;
    struct sockaddr_in  clientAddress;
private:
    char username[USERNAME_SIZE];
    std::thread clientThread;
    std::list<UserThread*> *usersPtr;
    std::mutex *usersMtx;
    void handleUser();
    void broadcastMessage(char *message, bool appendUsrNmToMsg);
    bool isUserNameValid(char *usrNm) const;
    bool requestUsername();
    void sendActiveUsers();
    void signalUserListDisconnection();
    void closeConnection();
    void prependUserNameToMessage(char* msg, const char* usr);
};

#endif // USERTHREAD_H
