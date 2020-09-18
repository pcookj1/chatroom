/*****************************************************************
 * Filename: main.cpp
 *
 * Author: Patrick Cook
 * Start Date: 20 Aug 20
 *
 * Description: Main program to initialize server for chatroom
 * Fixed size messages sent over socket (255 chars)
 *
*****************************************************************/

#include <stdlib.h>

#include <iostream>

#include "server.h"


int main(int argc, char **argv) {

    if(argc != 3) {
        std::cout << "You must enter the IP and Port in the format X.X.X.X PORT" << std::endl;
        return -1;
    }

    Server serv(argv[1], atoi(argv[2]));
    serv.initServer();
    serv.startServer();
    return 0;
}
