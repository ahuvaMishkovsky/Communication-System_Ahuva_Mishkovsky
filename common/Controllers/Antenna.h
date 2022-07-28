#pragma once
#include <thread>
#include <iostream>
#include "Controller.h"
using namespace std;

class Antenna :public Controller
{
public:
	Antenna(int devType, int port,int port_to_reply, unsigned short recieveOpCode, unsigned short sendOpCode) 
		:Controller(devType, port, port_to_reply, recieveOpCode, sendOpCode)
	{
		thread t1(&Antenna::Recieve_message, this);
		t1.detach();
	}

	void Recieve_message() {
		Controller::Recieve_message();
	}
};


