# chatroom
Simple Server/Client chatroom application built with Qt. The server side is built in plain C++ while the client side uses
Qt. This was done to explore the differences between implementing socket programming more tediously using the C socket library 
(server side) and an approach using Qt's networking module (client side). 

The server is a terminal application.
The client has a GUI.

# Server
Server contains the necessary source and header files for building the server side of the project.
It is implemented using the C socket library and uses multithreading to handle multiple clients.
Validates clients' usernames to ensure they are 6-16 characters long and contain no special characters.
Allows client to exit by typing "/exit" or retrieve user list by submitting "/usrlist".

Consists of a UserThread class which handles an individual connection, as well as a Server class, which
listens to incoming requests and creates new UserThreads accordingly.
Sends fixed sized messages defined by BUF_SIZE, which is 255 in this application.
Requires a newline at the end of every message, which is handled by the client.

# Client
Client contains the necessary source and header files for building the client side of the project.
Consists of a GUI which allows the user to enter an ip and port in the following format: X.X.X.X:Port
as well as a username.
Displays username error and socket error messages to the login screen should login fail.
The chat page has a window to display incoming user messages, which are uniquely colored and labeled by 
the user who sent it. It also has a user list where the user font colors match their message colors.

Consists of a ChatRoom class which handles the GUI, and a Client class which handles communication with the 
server and sends appropriate signals to the GUI to update the display.


