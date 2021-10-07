#ifndef SERVER_IMPLEMENTATIONS_P2P_H
#define SERVER_IMPLEMENTATIONS_P2P_H

#include <thread>
#include "winsockInit.h"

class server//:public winsockInit
{
	addrinfo *result=NULL,*ptr=NULL,hints;
	SOCKET ListenSocket=INVALID_SOCKET;
	SOCKET ClientSocket;
	char recvbuf[DEFAULT_BUFLEN];
	int iResultS,iSendResult;
	int recvbuflen=DEFAULT_BUFLEN;
	void acceptingClient(bool *);
	winsockInit wInit;

public:
	server();
	std::thread threadForListening(bool *);
};

#endif