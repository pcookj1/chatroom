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
    bool operator== (const User& u);
    ~User();
private:
    const char *username;
    int clientSocket;
    socklen_t clientLen;
    struct sockaddr_in  clientAddress;
    friend class Server;
};

class Server {
public:
    Server(int port, const char *ip = "127.0.0.1");
    void initServer();
    void startServer();
    ~Server();
private:
    int port;
    const char *ip;
    int listenSocket;
    struct sockaddr_in serverAddress;
    std::list<User> users; //pointer to list of objects
    std::list<std::thread> userThreads;
    void broadcastMessages(char const *message);
    void handleNewUsers();
    void userThread(User *connection);
    void closeConnection(User *connection);
    void checkConnections();
};

/* TO DO - implement chat archive (database?)
class Chat {


};
*/

#endif // SERVER_H
