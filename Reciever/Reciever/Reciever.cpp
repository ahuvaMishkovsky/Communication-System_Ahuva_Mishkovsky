#include <iostream>
#include <thread>
#include <vector>
#include "..\..\Common\Controllers\Antenna.h"
#include "..\..\Common\Controllers\Manager.h"
#include "..\..\Common\Controllers\Modem.h"
#pragma warning(disable:4996) 
using namespace std;

int main()
{
    vector<Controller_type> controllers{
        {MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE,ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE,ANTENNA_RECIEVER_PORT},
        {MANAGER_TO_MODEM_CONTROL_MSG_OPCODE,MODEM_TO_MANAGER_CONTROL_MSG_OPCODE,MODEM_RECIEVER_PORT}};

    Manager manager(MANAGER_RECIEVER_PORT, RECIEVER, controllers);
    Antenna antenna(RECIEVER, controllers[0].port,MANAGER_RECIEVER_PORT, controllers[0].toOpCode, ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE);
    Modem modem(RECIEVER, controllers[1].port, MANAGER_RECIEVER_PORT, controllers[1].toOpCode, MODEM_TO_MANAGER_CONTROL_MSG_OPCODE);

    while (true) {//so that the program does not end
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}
