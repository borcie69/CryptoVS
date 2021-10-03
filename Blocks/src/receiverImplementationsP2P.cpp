#include "receiverImplementationsP2P.h"

receiver::receiver()
{
    //set hints for socket, 1PP
    ZeroMemory(&hints,sizeof(hints));
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_protocol=IPPROTO_TCP;
}

void receiver::sendingPacket(const char* ip, const char* packet)
{
    sendbuf=packet;

    //fill result variable with info from other device, NPP
    iResultR = getaddrinfo(ip, DEFAULT_PORT, &hints, &result);
    if (iResultR != 0) {
        printf("getaddrinfo failed with error: %d\n", iResultR);
        WSACleanup();
        //add error to error system
    }

    // Attempt to connect to an address until one succeeds, NPP
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            //add error to error system
        }

        // Connect to server, NPP
        iResultR = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResultR == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    //NPP
    freeaddrinfo(result);

    //checking if socket is still viable,NPP
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        //add error to error system
    }

    // Send an initial buffer
    //send packet, NPP
    iResultR = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResultR == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        //add error to error system
    }

    printf("Bytes Sent: %ld\n", iResultR);

    // shutdown the connection since no more data will be sent, NPP
    iResultR = shutdown(ConnectSocket, SD_SEND);
    if (iResultR == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        //add error to error system
    }

    //recieve confirmation, NPP
    iResultR = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if (iResultR > 0)
        printf("Bytes received: %d Received message: %s\n",iResultR,recvbuf);
    else if (iResultR == 0)
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());


    // cleanup, NPP
    closesocket(ConnectSocket);
    //WSACleanup();
}