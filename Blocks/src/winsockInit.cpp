#include "winsockInit.h"

winsockInit::winsockInit()
{
	// Initialize Winsock
	iResult=WSAStartup(MAKEWORD(2,2),&wsaData);

	if(iResult!=0)
	{
		printf("WSAStartup failed: %d\n",iResult);
		//add error to error system
	}
}