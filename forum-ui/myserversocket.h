#ifndef MYSERVERSOCKET_H
#define MYSERVERSOCKET_H

#undef UNICODE
#define WIN32_LEAN_AND_MEAN


#include <windows.h>
#include <iostream>
#include <ctype.h>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include "myexception.h"
#include <QDebug>

//#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "46327"

class MyServerSocket {
private:
    WSADATA wsaData;
    //int iResult;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* resultAddrInfo = NULL;
    struct addrinfo hints;

    int sendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    void bindSocket();
    void listenSocket();

public:
    MyServerSocket();
    ~MyServerSocket();

    void acceptClient();
};

#endif // MYSERVERSOCKET_H
