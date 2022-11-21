#pragma once
#include "MessageModerator.h"

#define DEFAULT_BUFLEN 512

class MyServerSocket {
private:
    WSADATA wsaData;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    std::string defaultPort;
    struct addrinfo* resultAddrInfo = NULL;
    struct addrinfo hints;

    int sendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    void bindSocket();
    void listenSocket();

public:
    MyServerSocket(std::string port);
    ~MyServerSocket();

    void acceptClient();
    std::string receiveMSG();
    void sendAnswer(bool flag);
    void shutDownClient();
    std::string getPort()const;
};
