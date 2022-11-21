#pragma once

#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <QDebug>
#include <windows.h>
#include <iostream>
#include <ctype.h>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include "myexception.h"
#include "notification.h"
#include "myclientsocket.h"
#include "logger.h"

#define DEFAULT_BUFLEN 512

class MyServerSocket {
   friend DWORD WINAPI acceptPrepare(LPVOID lpParameter);
private:
    std::string port;
    WSADATA wsaData;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* resultAddrInfo = NULL;
    struct addrinfo hints;

    int sendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    void bindSocket();
    void listenSocket();
    void receiveMessageFromClient();
    void sendAnswerToClient(std::string answer);
    void shutdownClient();

    HANDLE threadAccept;
    DWORD threadID;
    std::string getPortFromFile(std::string fileName);

    Logger logger;
public:
    MyServerSocket();
    ~MyServerSocket(); 
    void acceptClient();
};

