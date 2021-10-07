#ifndef RECEIVER_IMPLEMENTATIONS_P2P_H
#define RECEIVER_IMPLEMENTATIONS_P2P_H

#include <thread>
#include "winsockInit.h"

#pragma comment(lib,"AdvApi32.lib")

class receiver:public winsockInit
{
	addrinfo *result=NULL,*ptr=NULL,hints;
	int iResultR;
	SOCKET ConnectSocket=INVALID_SOCKET;
	const char *sendbuf;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen=DEFAULT_BUFLEN;

public:
	receiver(const char *ip,const char *packet);
};

#endif