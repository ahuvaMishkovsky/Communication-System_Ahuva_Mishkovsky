#pragma once
#include "..\UDPComm\UDPServer.h"
#include "..\Controllers\Controller.h"
class Amplifier :public Controller
{
public:
	Amplifier(int devType, int port,  int port_to_reply, unsigned short recieveOpCode, unsigned short sendOpCode) 
		:Controller(devType, port,port_to_reply, recieveOpCode, sendOpCode) 
	{
		thread t1(&Amplifier::Recieve_message, this);
		t1.detach();
	}

	void Recieve_message()override {
		Controller::Recieve_message();
	}
};

