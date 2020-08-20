/*  Author: Patrick Cook
 *  Interface for Server component of chat room
 *  8/18/20
 *
*/

#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>

#include <list>
#include <thread>

#define BUF_SIZE 255

// TO DO: move userThread to User class and make server inherit User
// More intuitive and may come in handy when deleting a user and ending their thread.
class User {
public:
    User(int clientSocket, socklen_t clientLen, struct sockaddr_in clientAddress);
    ~User();
private:
    int clientSocket;
    socklen_t clientLen;
    struct sockaddr_in  clientAddress;
    //add thread function
    //void userThread();
    friend class Server;
};

/* TO DO - implement chat archive (database?)
class Chat {


};
*/

class Server {
public:
    Server(int port, const char *ip = "127.0.0.1");
    void initServer();
    void startServer();
    ~Server();
private:
    int port;
    const char *ip;
    char message[BUF_SIZE]; //doesn't make sense to have this
    int listenSocket;
    std::list<User> users;
    struct sockaddr_in serverAddress;
    std::thread entry; //prob get rid of this
    std::list<std::thread> userThreads;
    void broadcastMessages(char *message);
    void handleNewUsers();
    void userThread(User const *connection);
    void userExit();
};

#endif // SERVER_H
