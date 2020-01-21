//
// Created by Twometer on 19/09/2019.
//

#ifndef NEXTCRAFT_MCCLIENT_H
#define NEXTCRAFT_MCCLIENT_H


#include "McBuffer.h"
#include "TcpClient.h"
#include "../model/Player.h"

class McClient {
private:
    TcpClient *client = new TcpClient();

    int compressionThreshold = 0;

    bool isLoginMode = true;

    bool closeRequested = false;

public:
    Player player{};

    void Connect(const char *username, const char *hostname, unsigned short port);

    void Disconnect();

private:
    int ReadVarInt();

    void HandlePacket(int packetId, McBuffer &buffer);

    void SendPacket(int packetId, McBuffer &buffer);

public:
    void SendHandshake(int protocolVersion, const char *hostname, unsigned short port, int nextState);

    void SendLogin(const char *username);

    void SendKeepAlive(int id);

    void SendChat(const char *message);

    void SendPosLook(double x, double y, double z, float yaw, float pitch, bool onGround);

    void SendRespawn();
};


#endif //NEXTCRAFT_MCCLIENT_H
