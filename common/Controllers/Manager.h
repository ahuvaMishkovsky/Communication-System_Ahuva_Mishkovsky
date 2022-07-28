#pragma once
#include "..\UDPComm\UCPClient.h"
#include "..\UDPComm\UDPServer.h"
#include <thread>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Manager
{
private:
	UDPClient _client;
	UDPServer* _server;
	int _dev_type; //in transmitter or in receiver
	vector<Controller_type> _controllers; //which controllers it has
	int _msg_counter;
	unordered_map<int, Header> _sent_messages; //messages sent and not yet received a response

	int hashing(int counter, int i) {
		return counter * 10 + i;
	}

	void checking_response_messages() { //check if didn't get response after 5 seconds
		for (size_t i = 0; i < _controllers.size(); i++)
		{
			int key = hashing(_msg_counter - 5, i);
			if (_sent_messages.find(key) != _sent_messages.end()) { //No response was received to the message within 5 seconds
				cout << "No response was received from the device to a message to port: " << _controllers[i].toOpCode << " sent 5 seconds ago" << endl;
				_sent_messages.erase(key);
			}
		}
	}

public:
	Manager(int port, int devType, vector<Controller_type> controllers) {
		_server = new UDPServer(port, 0);
		_controllers = controllers;
		_dev_type = devType;
		_msg_counter = 0;

		std::thread t1(&Manager::Send_control_mesaages, this);
		t1.detach();

		std::thread t2(&Manager::Get_messages, this);
		t2.detach();
	}

	~Manager() {
		delete _server;
	}

	void Send_control_mesaages() {

		while (true) {
			for (size_t i = 0; i < _controllers.size(); i++)
			{
				Message message;
				message.controlMessage.header.msgCounter = _msg_counter;
				message.controlMessage.header.msgSync = MSG_SYNC;
				message.controlMessage.header.Opcode = _controllers[i].toOpCode;

				_client.Send_message(message, _controllers[i].port);
				_sent_messages[hashing(_msg_counter, i)] = message.header;
				cout << "MANAGER sent control msg number " << _msg_counter << " to " << _controllers[i].toOpCode << endl;
			}
			if (_msg_counter >= 5) { //there may be messages that have not been responded to after 5 seconds
				checking_response_messages();
			}
			_msg_counter++;
			this_thread::sleep_for(chrono::milliseconds(1000)); //the manager sends control messages to the devices every second
		}
	}

	void Get_messages() {

		while (true)
		{
			Message message = _server->Recieve_data();
			if (message.header.Opcode == DATA_MSG_OPCODE) {
				if (_dev_type == TRANSMITTER) {
					cout << "TRANSMITTER send data msg number " << message.dataMessage.header.msgCounter << " to MODEM_TRANSMITTER" << endl;
					_client.Send_message(message, MODEM_TRANSMITTER_PORT);
				}
				else {//dev_type is reciever
					cout << "RECIEVER send data msg number " << message.dataMessage.header.msgCounter << " to MESSAGE_GENERATOR" << endl;
					_client.Send_message(message, MESSAGE_GENERATOR_PORT);
				}
			}
			else //it's a controlMessage
			{
				for (int i = 0; i < _controllers.size(); i++) //what device is the message from
				{
					if (message.controlMessage.header.Opcode == _controllers[i].fromOpCode)
					{
						if (message.controlMessage.Ack != 1)
						{
							cout << "The received message from " << message.controlMessage.header.Opcode << " is invalid" << endl;
						}
						else
						{
							cout << "received control message from " << message.controlMessage.header.Opcode << " msgCounter is: " << message.controlMessage.header.msgCounter << endl;
						}
						_sent_messages.erase(hashing(message.controlMessage.header.msgCounter, i)); //A response was received for this device.
					}
				}
			}
		}
	}
};


