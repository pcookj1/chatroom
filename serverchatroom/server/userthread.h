#ifndef USERTHREAD_H
#define USERTHREAD_H

#include <sys/socket.h>
#include <string.h>

#include <iostream>
#include <list>
#include <mutex>
#include <thread>

#define USERNAME_SIZE 16

class UserThread {
public:
    UserThread(int newClientSocket, socklen_t newClientLen,
               struct sockaddr_in newClientAddress,
               std::list<UserThread*> *serverUsers, std::mutex *uMtx);
     ~UserThread();
    void run();
    const char *getUsername() {return username;}
    void setUsername(const char *newUsername) {strcpy(username, newUsername);}
    int clientSocket;
    socklen_t clientLen;
    struct sockaddr_in  clientAddress;
private:
    char username[USERNAME_SIZE];
    std::thread clientThread;
    std::list<UserThread*> *users;
    std::mutex *usersMtx;
    void handleUser();
    void broadcastMessage(char const *message);
    void requestUsername();
    void closeConnection();
};

#endif // USERTHREAD_H
