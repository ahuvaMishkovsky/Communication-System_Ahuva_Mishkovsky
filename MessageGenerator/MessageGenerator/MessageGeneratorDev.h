#pragma once
#include "../../Common/IDD.h"
#include "../../common/UDPComm/UCPClient.h"
#include "../../Common/UDPComm/UDPServer.h"
#include "../../Common/IDD.h"
#include <thread>
using namespace std;
class MessageGeneratorDev
{
private:
	int _msg_counter;
	int _received_msgs_counter;
	UDPClient _client;
	UDPServer* _server;
	Message create_data_message();
public:
	MessageGeneratorDev();
	~MessageGeneratorDev();
	void Tx(); //send data messages to the transmitter's manager
	void Rx(); //receive data messages from the receiver's manager
	int Get_msg_counter();
	int Get_received_msgs_counter();
};

