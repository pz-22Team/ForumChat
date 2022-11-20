#include "myserversocket.h"

MyServerSocket::MyServerSocket() {
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        throw MyException("WSAStartup failed with error: " + std::to_string(iResult));
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &this->hints, &this->resultAddrInfo);
    if (iResult != 0) {
        WSACleanup();
        throw MyException("getaddrinfo failed with error: " + std::to_string(iResult));
    }

    ListenSocket = socket(resultAddrInfo->ai_family, resultAddrInfo->ai_socktype, resultAddrInfo->ai_protocol);
      if (ListenSocket == INVALID_SOCKET) {
        freeaddrinfo(resultAddrInfo);
        WSACleanup();
        throw MyException("socket failed with error: " + std::to_string( WSAGetLastError()));
      }
}

MyServerSocket::~MyServerSocket() {
    closesocket(ListenSocket);
    closesocket(ClientSocket);
    WSACleanup();
}

void MyServerSocket::bindSocket() {
    // Setup the TCP listening socket
      int iResult = bind(ListenSocket, resultAddrInfo->ai_addr, (int)resultAddrInfo->ai_addrlen);


      if (iResult == SOCKET_ERROR) {
        freeaddrinfo(resultAddrInfo);
        closesocket(ListenSocket);
        WSACleanup();
        throw MyException("bind failed with error: " + std::to_string( WSAGetLastError()));
      }

      freeaddrinfo(resultAddrInfo);
}

void MyServerSocket::listenSocket() {
    int iResult = listen(ListenSocket, SOMAXCONN);
     if (iResult == SOCKET_ERROR) {
       closesocket(ListenSocket);
       WSACleanup();
       throw MyException("listen failed with error: " + std::to_string( WSAGetLastError()));
     }
}

void MyServerSocket::acceptClient() {
    bindSocket();
    listenSocket();

    int iResult, iSendResult;
    while (true) {
        std::cout << "server is listening" << std::endl;
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            closesocket(ListenSocket);
            WSACleanup();
            throw MyException("accept failed with error: " + std::to_string( WSAGetLastError()));
        }
        ZeroMemory(recvbuf, DEFAULT_BUFLEN);
        iResult = recv(ClientSocket, recvbuf, recvbuflen,0);

        if (iResult > 0) {
            std::string str = std::string(recvbuf);
            std::cout << str.size() << std::endl;
            str = str.substr(0, iResult-2);

            qDebug() << str.c_str();

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                closesocket(ClientSocket);
                WSACleanup();
                throw MyException("send failed with error: " + std::to_string( WSAGetLastError()));
            }
            printf("Bytes sent: %d\n", iSendResult);
        } else if (iResult == 0) {
            printf("Connection closing...\n");
        } else {
            closesocket(ClientSocket);
            WSACleanup();
            throw MyException("recv failed with error: " + std::to_string( WSAGetLastError()));
        }


        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            closesocket(ClientSocket);
            WSACleanup();
            throw MyException("shutdown failed with error: " + std::to_string( WSAGetLastError()));
        }
        closesocket(ClientSocket);
    }

}
