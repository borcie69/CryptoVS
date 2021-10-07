#ifndef WINSOCK_INIT_H
#define WINSOCK_INIT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")

//define default port
constexpr char DEFAULT_PORT[6]="54839";
constexpr short DEFAULT_BUFLEN=512;

class winsockInit
{
protected:
	WSADATA wsaData;
	int iResult;

public:
	winsockInit();
};

#endif