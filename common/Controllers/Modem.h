#pragma once
#include "..\UDPComm\UCPClient.h"
#include "..\UDPComm\UDPServer.h"
#include "Controller.h"
#include "..\..\common\IDD.h"
class Modem :public Controller
{
private:
	UDPClient client;
public:
	Modem(int devType, int port, int port_to_reply, unsigned short recieveOpCode, unsigned short sendOpCode) 
		:Controller(devType, port, port_to_reply, recieveOpCode, sendOpCode)
	{
		thread t1(&Modem::Recieve_message, this);
		t1.detach();
	}

	void Recieve_message() override {//override because it also receives data messages differently from the other devices

		while (true)
		{
			Message msg = _server->Recieve_data();
			if (msg.header.msgSync != MSG_SYNC)
				continue;
			if (msg.controlMessage.header.Opcode == _receive_opCode)
			{
				cout << _receive_opCode << "recived control msg from " << _dev_type << endl;
				if (msg.controlMessage.header.msgCounter == this->_expected_message_counter) {
					msg.controlMessage.Ack = 1;
					_expected_message_counter++;
				}
				else {
					msg.controlMessage.Ack = 0;
					_expected_message_counter = msg.controlMessage.header.msgCounter++; //correct number
				}
				msg.controlMessage.header.Opcode = _send_opCode;
				_server->Reply_the_client(msg);
				continue;
			}
			if (msg.dataMessage.header.Opcode == DATA_MSG_OPCODE) {
				if (this->_dev_type == TRANSMITTER) {
					this->client.Send_message(msg, MODEM_RECIEVER_PORT);
					continue;
				}
				else { //dev_type is reciever
					this->client.Send_message(msg, MANAGER_RECIEVER_PORT);
				}
			}
		}
	}
};

