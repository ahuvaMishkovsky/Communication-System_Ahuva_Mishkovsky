#pragma once
#include <iostream>
#include <winsock2.h>
#include "..\IDD.h"
#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996) 
using namespace std;
#define SERVER "127.0.0.1"  

class UDPClient
{
private:
	WSADATA _ws;
	sockaddr_in _server;
	int _client_socket;
	int _buflen;

	void initialise_winsock() {
		cout << "Initialising Winsock..." << endl;
		if (WSAStartup(MAKEWORD(2, 2), &_ws) != 0)
		{
			cout << "Failed. Error Code: " << WSAGetLastError() << endl;
			exit(0);
		}
		cout << "Initialised." << endl;
	}

	void create_socket() {
		if ((_client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) // <<< UDP socket
		{
			cout << "socket() failed with error code: " << WSAGetLastError() << endl;
			exit(0);
		}
	}

	void setup_address_structure(int port) {
		_server.sin_family = AF_INET;
		_server.sin_port = htons(port);
		_server.sin_addr.S_un.S_addr = inet_addr(SERVER);
	}

public:
	UDPClient() {
		_buflen = sizeof(Message);
		initialise_winsock();
		create_socket();
	}

	~UDPClient() {
		closesocket(_client_socket);
		WSACleanup();
	}

	void Send_message(Message message, int port) {
		setup_address_structure(port);
		if (sendto(_client_socket, (char*)&message, sizeof(message), 0, (sockaddr*)&_server, sizeof(sockaddr_in)) == SOCKET_ERROR)
		{
			cout << "sendto() failed with error code : " << WSAGetLastError() << endl;
		}
	}
};

