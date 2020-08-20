/*  Patrick Cook
 *  Implementation for Client component of chat room
 *  8/18/20
 *
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

#include "client.h"

using namespace std;

Client::Client(int port, const char *ip) {
    this->port = port;
    this->ip = ip;
}

void Client::initClient() {
    listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if(listenSock < 0)
        perror("Error opening client socket");
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(ip);
    servAddr.sin_port = htons(port);

    if(connect(listenSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
        perror("Error connecting client to socket");
    cout << "Client connected to socket succesfully\n" << endl;
}

void Client::sendClient() {
    cout << "Type messages (max BUF_SIZE chars)\n" << endl;
    //cout << "Sending message..." << endl;
    //strcpy(message, "Hey I'm Client Patrick!\n");
    //cout << "You wrote:" << message << endl;
    fgets(message, BUF_SIZE, stdin);
    if(write(listenSock, message, BUF_SIZE) < 0)
        perror( "Error writing message to socket");
}

void Client::receiveClient() {
    int result, bytesRead = 0;
    //cout << "Receiving message..." << endl;
    /*while(bytesRead < BUF_SIZE) {
        cout << "iterating loop again" << endl;
        result = read(listenSock, message + bytesRead, BUF_SIZE - bytesRead);
        cout << "Bytes read" << result << endl;
        if(result == 0) {
            cout << "Done reading socket" << endl;
            break;
        } else if(result < 0)
            perror( "Error reading from the socket");
        bytesRead += result;
    } */
    while(1) {
        result = read(listenSock, message, BUF_SIZE);
        if(result < 0)
            perror("Error reading user's socket\n");
        else if(result == 0)
            continue;
        cout << "Message is: " << message << endl;
    }
   // result = read(listenSock, message + bytesRead, BUF_SIZE - bytesRead);
   // cout << "Message is: " << message << endl;
}

Client::~Client() {

}
