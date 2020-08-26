#include <iostream>

#include "server.h"

using namespace std;

int main()
{
    //cout << "Starting Server...!" << endl;
    Server serv(14001);
    serv.initServer();
    serv.startServer();
    cout << "Ending Server...!" << endl;
    return 0;
}
