#pragma once
#include <thread>
#include "..\UDPComm\UDPServer.h"
class Controller
{
protected:
	UDPServer* _server;
	int _port;
	unsigned short _receive_opCode;
	unsigned short _send_opCode;
	int _expected_message_counter; //nextExpectedCounter
	int _dev_type; //reciever or transmitter

public:
	Controller(int devType, int port, int port_to_reply, unsigned short recieveOpCode, unsigned short sendOpCode) {
		_dev_type = devType;
		_expected_message_counter = 0;
		_port = port;
		_receive_opCode = recieveOpCode;
		_send_opCode = sendOpCode;
		_server = new UDPServer(port, port_to_reply);

		thread t1(&Controller::Recieve_message, this);
		t1.detach();
	}

	virtual ~Controller()
	{
		delete _server;
	}

	virtual void Recieve_message() {

		while (true)
		{
			Message message = _server->Recieve_data();
			if (message.header.msgSync != MSG_SYNC)
				continue;
			if (message.header.Opcode == _receive_opCode)
			{
				cout << _receive_opCode << "recived control msg from " << _dev_type << endl;
				if (message.controlMessage.header.msgCounter == this->_expected_message_counter) {
					message.controlMessage.Ack = 1;
					_expected_message_counter++;
				}
				else {
					message.controlMessage.Ack = 0;
					_expected_message_counter = message.controlMessage.header.msgCounter++;
				}
				message.controlMessage.header.Opcode = _send_opCode;
				_server->Reply_the_client(message);
			}
		}


	}
};

