#include "serverImplementationsP2P.h"
//#include "winsockInit.h"

server::server()
{
	ZeroMemory(&hints,sizeof(hints));
	hints.ai_family=AF_INET;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_protocol=IPPROTO_TCP;
	hints.ai_flags=AI_PASSIVE;

	if((iResultS=getaddrinfo(NULL,DEFAULT_PORT,&hints,&result))!=0)
	{
		printf("getaddrinfo failed: %d\n",iResultS);
		WSACleanup();
		//add error to error system
	}

	// Create a SOCKET for the server to listen for client connections
	if((ListenSocket=socket(result->ai_family,result->ai_socktype,result->ai_protocol))==INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n",WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		//add error to error system
	}

	// Setup the TCP listening socket
	if((iResultS=bind(ListenSocket,result->ai_addr,(int)result->ai_addrlen))==SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n",WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		//add error to error system
	}

	freeaddrinfo(result);

	if(listen(ListenSocket,SOMAXCONN)==SOCKET_ERROR)
	{
		printf("Listen failed with error: %ld\n",WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		//add error to error system
	}
}

//acepting loop for thread
void server::acceptingClient(bool *sharedForListening)
{
	while(true)
	{
		ClientSocket=INVALID_SOCKET;

		// Accept a client socket
		if((ClientSocket=accept(ListenSocket,NULL,NULL))==INVALID_SOCKET)
		{
			printf("accept failed: %d\n",WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			//add error to error system
		}


		*sharedForListening=true;
		do
		{
			iResultS=recv(ClientSocket,recvbuf,recvbuflen,0);
			if(iResultS>0)
			{
				printf("Bytes received: %d\n",iResultS);

				// Echo the buffer back to the sender
				iSendResult=send(ClientSocket,recvbuf,iResultS,0);
				if(iSendResult==SOCKET_ERROR)
				{
					printf("send failed with error: %d\n",WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					//add error to error system
				}
				printf("Bytes sent: %d\n",iSendResult);
			}
			else if(iResultS==0)
				printf("Connection closing...\n");
			else
			{
				printf("recv failed with error: %d\n",WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				//add error to error system
			}

		}
		while(iResultS>0);
		*sharedForListening=false;

		//close server sending
		/*if((iResultS=shutdown(ClientSocket,SD_SEND))==SOCKET_ERROR)
		{
			printf("shutdown failed: %d\n",WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			//add error to error system
		}*/

		//clean client socket
		closesocket(ClientSocket);
		//WSACleanup();
	}
}

std::thread server::threadForListening(bool *sharedForListening)
{
	return std::thread([=]
	{
		acceptingClient(sharedForListening);
	});
}