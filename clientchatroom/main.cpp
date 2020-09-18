/*****************************************************************
 * Filename: main.cpp
 *
 * Author: Patrick Cook
 * Start Date: 20 Aug 20
 *
 * Description: Main program to launch the ChatRoom application
 * User can connect to a server socket by specifying an IP address, port
 * and valid username.
 *      * Valid username must be between 6-16 characters and must contain
 *      * no special characters (case insensitive letters and numbers)
 * User can exit by typing "/exit"
 * User can update their user list by typing "/usrlist"
 *
*****************************************************************/

#include <QApplication>

#include "chatroom.h"


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    ChatRoom w;
    w.show();

    return a.exec();
}
