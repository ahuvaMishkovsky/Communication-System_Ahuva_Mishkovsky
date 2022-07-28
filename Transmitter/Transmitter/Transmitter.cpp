#include <iostream>
#include <vector>
#include "..\..\Common\Controllers\Antenna.h"
#include "..\..\Common\Controllers\Manager.h"
#include "..\..\Common\Controllers\Amplifier.h"
#include "..\..\Common\Controllers\Modem.h"
#include "..\..\Common\IDD.h"
#pragma warning(disable:4996) 
using namespace std;

int main()
{
	vector<Controller_type> controllers{
		{MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE,ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE,ANTENNA_TRANSMITTER_PORT},
		{MANAGER_TO_AMPLIFIER_CONTROL_MSG_OPCODE,AMPLIFIER_TO_MANAGER_CONTROL_MSG_OPCODE,AMPLIFIER_TRANSMITTER_PORT},
		{MANAGER_TO_MODEM_CONTROL_MSG_OPCODE,MODEM_TO_MANAGER_CONTROL_MSG_OPCODE,MODEM_TRANSMITTER_PORT} };

	Manager manager(MANAGER_TRANSMITTER_PORT, TRANSMITTER, controllers);
	Antenna antenna(TRANSMITTER, controllers[0].port, MANAGER_TRANSMITTER_PORT, controllers[0].toOpCode, ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE);
	Amplifier amplifier(TRANSMITTER, controllers[1].port, MANAGER_TRANSMITTER_PORT, controllers[1].toOpCode, AMPLIFIER_TO_MANAGER_CONTROL_MSG_OPCODE);
	Modem modem(TRANSMITTER, controllers[2].port, MANAGER_TRANSMITTER_PORT, controllers[2].toOpCode, MODEM_TO_MANAGER_CONTROL_MSG_OPCODE);

	while (true) { //so that the program does not end
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
};
