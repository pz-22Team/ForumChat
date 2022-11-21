#include "myserversocket.h"
#include "mainwindow.h"

MyServerSocket::MyServerSocket() {
    std::string fileName = "server-config.txt";
    this->port = getPortFromFile(fileName);

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        throw MyException("WSAStartup failed with error: " + std::to_string(iResult));
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, port.c_str(), &this->hints, &this->resultAddrInfo);
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
    WSACleanup();
    if(threadAccept)
        CloseHandle(threadAccept);
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

DWORD WINAPI acceptPrepare(LPVOID lpParameter) {
    MyServerSocket* tempSocket = (MyServerSocket*) lpParameter;

    while (true) {
        try {
            tempSocket->logger.log("INFO", "Server is listening port: " + std::string(tempSocket->port));

            //--------------------accept client----------------------------
            tempSocket->ClientSocket = accept(tempSocket->ListenSocket, NULL, NULL);
            if (tempSocket->ClientSocket == INVALID_SOCKET) {
                closesocket(tempSocket->ListenSocket);
                WSACleanup();
                throw MyException("Accept failed with error: " + std::to_string(WSAGetLastError()));
            }

            tempSocket->receiveMessageFromClient();
            tempSocket->shutdownClient();

        } catch(const MyException &e) {
            tempSocket->logger.log("ERROR", e.what());
        } 
    }
}

void MyServerSocket::receiveMessageFromClient() {
    //-----------------------receive message-----------------------------
    ZeroMemory(recvbuf, DEFAULT_BUFLEN);
    int iResult = recv(ClientSocket, recvbuf, recvbuflen,0);

    if (iResult > 0) {
        std::string str = std::string(recvbuf);
        logger.log("INFO", "Received message from client: " + str.substr(0, iResult - 2));

        Notification message(str);
        //-----------------create client socket and send message-------------
        MyClientSocket myForum;
        myForum.sendMessageToServer(message.getMessage());//send,shutdown connection and receive answer
        //---------------show message on forun if true------------------------
        std::string ans = myForum.getAnswer();
        if(ans == "true") {
            MainWindow::updateTable(message.getMessage(), message.getUserName(), message.getAmountOfUsers());
        } else {
            logger.log("ERROR", "Cannot display message because of too many ban words");
        }

        sendAnswerToClient(ans);

    } else if (iResult == 0) {
        logger.log("INFO", "Connection closing...");
    } else {
        closesocket(ClientSocket);
        WSACleanup();
    }
}

void MyServerSocket::sendAnswerToClient(std::string answer) {
    int iSendResult = send(ClientSocket, answer.c_str(), strlen(answer.c_str()), 0);
    if (iSendResult == SOCKET_ERROR) {
        closesocket(ClientSocket);
        WSACleanup();
        throw MyException("Send failed with error: " + std::to_string(WSAGetLastError()));
    }
    logger.log("INFO", "Message sent to client: " + answer);
}

void MyServerSocket::shutdownClient() {
    int iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        closesocket(ClientSocket);
        WSACleanup();
        throw MyException("Client shutdown failed with error: " + std::to_string( WSAGetLastError()));
    }
    closesocket(ClientSocket);
}

void MyServerSocket::acceptClient() {
    bindSocket();
    listenSocket();

    threadAccept = CreateThread(NULL, NULL, acceptPrepare, this, NULL, &threadID);
    SetThreadPriority(threadAccept, REALTIME_PRIORITY_CLASS);
}

std::string MyServerSocket::getPortFromFile(std::string fileName) {
    std::string line;
    std::ifstream in(fileName);
    if (in.is_open()) {
        getline(in, line);
    }
    else {
        logger.log("ERROR", "Failed to open file: " + fileName);
    }
    in.close();
    std::string port = line.substr(line.find_first_of("=") + 1, line.size() - 1);
    return std::to_string(atoi(port.c_str()));
}
