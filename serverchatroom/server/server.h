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
#include <mutex>
#include <thread>

#include "userthread.h"

class Server {
public:
    Server(int nPort, const char *nip = "127.0.0.1");
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

/* TO DO - implement chat archive (database?)
class Chat {


};
*/

#endif // SERVER_H
