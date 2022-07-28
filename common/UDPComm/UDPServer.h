#pragma once
#include <iostream>
#include <winsock2.h>
#include "..\IDD.h"
#pragma comment(lib,"ws2_32.lib") // Winsock Library
#pragma warning(disable:4996) 
using namespace std;

class UDPServer
{
private:
	sockaddr_in _server, _client;
	WSADATA _wsa;
	SOCKET _server_socket;
	int _port;
	int _port_to_reply;
	boolean _bound;

	void initialize_winsock() {
		cout << "Initialising Winsock..." << endl;
		if (WSAStartup(MAKEWORD(2, 2), &_wsa) != 0)
		{
			cout << "Failed. Error Code: " << WSAGetLastError() << endl;
			exit(0);
		}
		cout << "Initialised.\n";
	}

	void create_socket() {
		if ((_server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		{
			cout << "Could not create socket: " << WSAGetLastError();
			exit(0);
		}
		cout << "Socket SERVER created.\n";
	}

	void prepare_the_sockaddr_in_structure() {
		_server.sin_family = AF_INET;
		_server.sin_addr.s_addr = INADDR_ANY;
		_server.sin_port = htons(_port);
	}

	void try_bind() {
		cout << "binding " << _port << endl;
		if (bind(_server_socket, (sockaddr*)&_server, sizeof(_server)) == SOCKET_ERROR)
		{
			cout << "Bind failed with error code: " << WSAGetLastError() << endl;
		}
		_bound = true;
		cout << "Bind done." << endl;
	}
public:
	UDPServer(int port, int port_to_reply) {
		_port = port;
		_port_to_reply = port_to_reply;
		_bound = false;
		prepare_the_sockaddr_in_structure();
		initialize_winsock();
		create_socket();
		try_bind();
	}

	~UDPServer() {
		closesocket(_server_socket);
		WSACleanup();
	}

	Message Recieve_data() {//receive data from the server

		while (_bound)//if not bound will not do recvfrom()
		{
			cout << _port << ": Waiting for data... " << endl;
			Message message;
			int message_len;
			int slen = sizeof(sockaddr_in);
			if (message_len = recvfrom(_server_socket, (char*)&message, sizeof(Message), 0, (sockaddr*)&_client, &slen) == SOCKET_ERROR)
			{
				cout << "recvfrom()  failed with error code: " << WSAGetLastError() << " port: " << _port << endl;
			}
			cout << "Received packet from " << inet_ntoa(_client.sin_addr) << ntohs(_client.sin_port) << endl;
			int x;
			return message;
		}
		if (!_bound)
		{
			cout << "can't receive data from port: " << _port << " socket isn't bound " << endl;
		}
	}

	void Reply_the_client(Message message) {

		sockaddr_in managerListenerSocket;
		managerListenerSocket.sin_family = AF_INET;
		managerListenerSocket.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		managerListenerSocket.sin_port = htons(_port_to_reply);

		if (sendto(_server_socket, (char*)&message, sizeof(message), 0, (sockaddr*)&managerListenerSocket, sizeof(sockaddr_in)) == SOCKET_ERROR)
		{
			cout << "sendto() failed with error code: %d" << WSAGetLastError() << endl;
		}
	}
};
