#include <iostream>
#include <QApplication>

#include "client.h"
#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */
    Client client(14001);
    client.initClient();
    client.sendClient();
    client.receiveClient();
    cout << "Done receiving\n" << endl;
    //while(1);
    //client.sendClient();

}
