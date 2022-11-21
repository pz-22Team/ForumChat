#include "MyServerSocket.h"


MyServerSocket::MyServerSocket(std::string port) {
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        throw MyException("WSAStartup failed with error: " + std::to_string(iResult));
    }
    defaultPort = port;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, defaultPort.c_str(), &this->hints, &this->resultAddrInfo);
    if (iResult != 0) {
        WSACleanup();
        throw MyException("getaddrinfo failed with error: " + std::to_string(iResult));
    }

    ListenSocket = socket(resultAddrInfo->ai_family, resultAddrInfo->ai_socktype, resultAddrInfo->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        freeaddrinfo(resultAddrInfo);
        WSACleanup();
        throw MyException("socket failed with error: " + std::to_string(WSAGetLastError()));
    }
    bindSocket();
    listenSocket();
}

std::string MyServerSocket::getPort() const{
    return defaultPort;
}

MyServerSocket::~MyServerSocket() {
    closesocket(ListenSocket);
    WSACleanup();
}

void MyServerSocket::bindSocket() {
    int iResult = bind(ListenSocket, resultAddrInfo->ai_addr, (int)resultAddrInfo->ai_addrlen);


    if (iResult == SOCKET_ERROR) {
        freeaddrinfo(resultAddrInfo);
        closesocket(ListenSocket);
        WSACleanup();
        throw MyException("bind failed with error: " + std::to_string(WSAGetLastError()));
    }

    freeaddrinfo(resultAddrInfo);
}

void MyServerSocket::listenSocket() {
    int iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        closesocket(ListenSocket);
        WSACleanup();
        throw MyException("listen failed with error: " + std::to_string(WSAGetLastError()));
    }
}

void MyServerSocket::acceptClient() {
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        closesocket(ListenSocket);
        WSACleanup();
        throw MyException("accept failed with error: " + std::to_string(WSAGetLastError()));
    }
}

std::string MyServerSocket::receiveMSG() {
    std::string str = "";
    ZeroMemory(recvbuf, DEFAULT_BUFLEN);
    int iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0) {
        str = std::string(recvbuf);
        //str = str.substr(0, iResult - 2);
    } else {
        closesocket(ClientSocket);
        WSACleanup();
        throw MyException("recv failed with error: "+std::to_string(WSAGetLastError())+'\n');
    }
    return str;
}

void MyServerSocket::sendAnswer(bool flag) {
    std::string bufAnswer;
    int iSendResult;
    if (flag)
        bufAnswer = "true";
    else
        bufAnswer = "false";
    iSendResult = send(ClientSocket, bufAnswer.c_str(), strlen(bufAnswer.c_str()), 0);
    if (iSendResult == SOCKET_ERROR) {
        closesocket(ClientSocket);
        WSACleanup();
        throw MyException("send failed with error: " + std::to_string(WSAGetLastError()));
    }
    printf("Bytes sent back: %d\n", sizeof(bufAnswer));
    printf("Message sent back: %s\n", bufAnswer.c_str());
}

void MyServerSocket::shutDownClient() {
    int iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        closesocket(ClientSocket);
        WSACleanup();
        throw MyException("shutdown failed with error: "+ std::to_string(WSAGetLastError()));
    }
    closesocket(ClientSocket);
}
