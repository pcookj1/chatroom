# chatroom
Simple Server/Client chatroom application built with Qt 5.9.5. The server side is built in plain C++ while the client side uses
Qt. This was done to explore the differences between implementing socket programming more tediously using the C socket library 
(server side) and an approach using Qt's networking module (client side). 

# Building and Running Project using Qt Creator
Download the server and client projects and build them separately. The executables are then found in the default build directory set by Qt Creator for the project. In this project, the build directory is "build_files".

Run ./client to open the client GUI.
Run ./server IP Port to run a server on a IP:Port.

The server is a terminal application while the client has a GUI.
![Image of Login](https://github.com/pcookj1/chatroom/blob/master/loginscreen.png?raw=true)
![Image of Chat](https://github.com/pcookj1/chatroom/blob/master/chatscreen.png?raw=true)
![Image of Server](https://github.com/pcookj1/chatroom/blob/master/serverterminal.png?raw=true)

# Server
Server contains the necessary source and header files for building the server side of the project.
It is implemented using the C socket library and uses multithreading to handle multiple clients.
Validates clients' usernames to ensure they are 6-16 characters long and contain no special characters.
Allows client to exit by typing "/exit" or retrieve user list by submitting "/usrlist".

Consists of a UserThread class which handles an individual connection, as well as a Server class, which
listens to incoming requests and creates new threads upon an accepted connection.
Sends fixed sized messages defined by BUF_SIZE, which is 255 in this application.
Requires a newline at the end of every message, which is handled by the client.

# Client
Client contains the necessary source and header files for building the client side of the project.
Consists of a GUI which allows the user to enter an ip and port in the following format: X.X.X.X:Port
as well as a username.
Displays username error and socket error messages to the login screen should login fail.
The chat page has a window to display incoming user messages, which are uniquely colored and labeled by 
the user who sent it. It also has a user list where the user font colors match their message colors.

Consists of a chat room window for the GUI, and a Client class which handles communication with the 
server and sends appropriate signals to the GUI to update the display.


