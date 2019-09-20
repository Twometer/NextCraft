//
// Created by Twometer on 19/09/2019.
//

#ifndef NEXTCRAFT_MCCLIENT_H
#define NEXTCRAFT_MCCLIENT_H


#include "McBuffer.h"
#include "TcpClient.h"

class McClient {
private:
    TcpClient *client = new TcpClient();

    int compressionThreshold = 0;

    bool closeRequested = false;

public:
    void Connect(const char *username, const char *hostname, unsigned short port);

    void Disconnect();

    void SendPacket(int packetId, McBuffer &buffer);

    void SendHandshake(int protocolVersion, const char* hostname, unsigned short port, int nextState);

    void SendLogin(const char* username);

};


#endif //NEXTCRAFT_MCCLIENT_H
