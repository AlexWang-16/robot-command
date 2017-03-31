#pragma once
#ifndef MS1_LIBRARY_H
#define MS1_LIBRARY_H

#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

enum CmdType {DRIVE, SLEEP, ARM, CLAW, ACK};
const int FORWARD = 1;
const int BACKWARD = 2;
const int RIGHT = 3;
const int LEFT = 4;
const int UP = 5;
const int DOWN = 6;
const int OPEN = 7;
const int CLOSE = 8;
const int HEADERSIZE = 3;

struct CmdPacket {
	Header header;
	char* data;
	char crc;
};

struct Header {
	char pktCount;
	char drive : 1;
	char status : 1;
	char sleep : 1;
	char arm : 1;
	char claw : 1;
	char ack : 1;
	char : 2; //Padding
	char length;
};

struct MotorBody {
	char direction;
	char duration;
};

class PktDef {
	CmdPacket cmdPacket;
	char* rawBuffer;
public:
	PktDef();
	PktDef(char*);
	void setCmd(CmdType);

}; 

class winsock {
protected:
	int version_num1, version_num2; // determines the WSADATA version numbers
	int port; // port number
	std::string ip; //ip string e.g. "127.0.0.1"
	char rx_buffer[128] = {}; //note that the rx_buffer has only 128 bytes
	WSADATA wsa_data;
public:
	void start_DLLS();
	SOCKET initialize_tcp_socket();
	winsock();
};

class winsock_client : public winsock {
protected:
	SOCKET client_socket;
public:
	char * receive_message(); //receives message from the client_socket
	void send_message(char *); //sends message to the client_socket
	void get_messages(); //continuously prints messages received
	void connect_to_tcp_server(); //tries to connect, exits if no server available
	void connect_to_tcp_server_loop(); //keeps trying to connect until successful
	winsock_client(int, std::string);
	~winsock_client();
};


#endif