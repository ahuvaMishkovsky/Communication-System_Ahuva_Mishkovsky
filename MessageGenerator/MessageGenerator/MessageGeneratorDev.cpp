#include "MessageGeneratorDev.h"

Message MessageGeneratorDev::create_data_message()
{
	Message dataMessage;
	dataMessage.dataMessage.header.msgCounter = _msg_counter;
	dataMessage.dataMessage.header.msgSync = MSG_SYNC;
	dataMessage.dataMessage.header.Opcode = DATA_MSG_OPCODE;
	return dataMessage;
}

MessageGeneratorDev::MessageGeneratorDev()
{
	_msg_counter = 0;
	_received_msgs_counter = 0;
	_server = new UDPServer(MESSAGE_GENERATOR_PORT,0);

	thread t1(&MessageGeneratorDev::Tx, this);
	t1.detach();
	thread t2(&MessageGeneratorDev::Rx, this);
	t2.detach();
}

MessageGeneratorDev::~MessageGeneratorDev()
{
	delete _server;
}

void MessageGeneratorDev::Tx()
{
	while (true) {
		_client.Send_message(create_data_message(), MANAGER_TRANSMITTER_PORT);
		_msg_counter++;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

void MessageGeneratorDev::Rx()
{
	while (true)
	{
		Message message = _server->Recieve_data();//returns int
		if (message.header.msgSync != MSG_SYNC)
			continue;
		Header header = message.header;
		if (header.Opcode != DATA_MSG_OPCODE) {
			continue;
		}
		_received_msgs_counter++;//got correct data message
		cout << "message generator got data message number "<<_received_msgs_counter<<" successfully" << endl;
	}
}

int MessageGeneratorDev::Get_msg_counter()
{
	return _msg_counter;
}

int MessageGeneratorDev::Get_received_msgs_counter()
{
	return _received_msgs_counter;
}
