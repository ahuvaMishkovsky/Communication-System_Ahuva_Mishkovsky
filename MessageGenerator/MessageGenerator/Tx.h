#pragma once
#include "..\..\Common\UDPClient.h"
#include "..\..\Common\IDD.h"

class Tx//Sending data messages
{
private:
	UDPClient client;
	int messageCounter;
public:
	Tx();
	
};

