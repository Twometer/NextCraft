//
// Created by Twometer on 20/09/2019.
//


#include "TcpClient.h"
#include "../util/Logger.h"

#include <string>
#include <cstdio>

bool TcpClient::Connect(const char *host, unsigned short port) {
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = nullptr, *ptr = nullptr, hints;

    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return false;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(host, std::to_string(port).c_str(), &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return false;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("Socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return false;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        Logger::Error("Unable to connect to server!");
        WSACleanup();
        return false;
    }

    this->tcpSocket = ConnectSocket;
    return true;
}

void TcpClient::Close() {
    closesocket(tcpSocket);
    WSACleanup();
}

int TcpClient::Receive(uint8_t *buf, int len) {
    int read = 0;
    int c = 0;
    while (read < len) {
        c = recv(tcpSocket, (char *) (buf + read), len - read, 0);
        if (c < 0)
            return c;
        read += c;
    }
    return read > 0 ? read : -1;
}

void TcpClient::Send(uint8_t *buf, int len) {
    int result = send(tcpSocket, (char *) buf, len, 0);
    if (result == SOCKET_ERROR)
        Close();
}

uint8_t TcpClient::ReadByte() {
    uint8_t buf;
    recv(tcpSocket, (char *) &buf, 1, 0);
    return buf;
}
