/*  Patrick Cook
 *  Interface for Client component of chat room
 *  8/18/20
 *
*/

#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>
#include <sys/socket.h>

#define BUF_SIZE 255

class Client {
public:
    Client(int port, const char *ip = "127.0.0.1");
    void initClient();
    void sendClient();
    void receiveClient();
    ~Client();
private:
    int port;
    const char *ip;
    char message[BUF_SIZE];
    int listenSock, acceptSock;
    socklen_t clientLen;
    struct sockaddr_in servAddr, clientAddr;
};

#endif // CLIENT_H
