#include "myclientsocket.h"

MyClientSocket::MyClientSocket() {
    std::string fileName = "client_config.txt";
    std::vector<std::string> portAndHost = getPortAndHostFromFile(fileName);
    this->port = portAndHost[0];
    this->host = portAndHost[1];

    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        throw MyException("WSAStartup failed with error: " + std::to_string(iResult));
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("localhost", port.c_str(), &hints, &result);
    if ( iResult != 0 ) {
        WSACleanup();
        throw MyException("getaddrinfo failed with error: " + std::to_string(iResult));
    }

    connectSocket();
}

MyClientSocket::~MyClientSocket() {
    closesocket(ConnectSocket);
    WSACleanup();
}

void MyClientSocket::sendMessageToServer(std::string message) {
    int iResult = send(ConnectSocket, message.c_str(), (int)strlen(message.c_str()), 0);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        WSACleanup();
        throw MyException("send failed with error: " + std::to_string(iResult));
    }
    logger.log("INFO", "Message sent to server: " + message);
    shutdownConnection();
    receiveAnswerFromServer(); //receive Answer from server
}

std::string MyClientSocket::getAnswer() {
    return this->answer;
}

void MyClientSocket::connectSocket() {
    int iResult;
    for(ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                               ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            WSACleanup();
            throw MyException("socket failed with error: " + std::to_string(WSAGetLastError()));
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        WSACleanup();
        throw MyException("Unable to connect to server!\n");
    }
}

void MyClientSocket::shutdownConnection() {
    int iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        WSACleanup();
        throw MyException("Forum-server shutdown failed with error: " + std::to_string(iResult));
    }
}

void MyClientSocket::receiveAnswerFromServer() {
    int iResult;

    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    std::string str(recvbuf);
    str = str.substr(0, iResult);
    this->answer = str;
    if (iResult > 0)
        logger.log("INFO", "Message received: " + str);
    else if ( iResult == 0 )
        logger.log("INFO", "Connection closed");
    else
        logger.log("ERROR", "Reciving(recv) failed with error: " + std::to_string(WSAGetLastError()));
}

std::vector<std::string> MyClientSocket::getPortAndHostFromFile(std::string FileName) {
    std::string line;
    std::ifstream in(FileName);

    if (in.is_open()) {
        getline(in, line);
    }
    std::vector<std::string> PortAndHost;
    std::string port;
    std::string sub = line.substr(line.find_first_of("=") + 1, line.size() - 1);

    PortAndHost.push_back(std::to_string(stoi(sub)));

    getline(in, line);
    int check = line.find_first_of(" ");
    if (check == -1) {
        sub = line.substr(line.find_first_of("=") + 1, line.size() - 1);

    } else
        sub = line.substr(line.find_first_of("=") + 1, line.find_first_of(" ") - line.find_first_of("=")-1);

    PortAndHost.push_back(sub);
    in.close();
    return PortAndHost;
}
