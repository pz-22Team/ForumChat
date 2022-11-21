#pragma once
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
#include "logger.h"

#define DEFAULT_BUFLEN 512

class MyClientSocket {
private:
    std::string host;
    std::string port;
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    std::string answer;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    void connectSocket();
    void shutdownConnection();
    void receiveAnswerFromServer();
    std::vector<std::string> getPortAndHostFromFile(std::string FileName);

    Logger logger;
public:
    MyClientSocket();
    ~MyClientSocket();

    void sendMessageToServer(std::string message);
    std::string getAnswer();
};

