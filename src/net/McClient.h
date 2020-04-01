//
// Created by Twometer on 19/09/2019.
//

#ifndef NEXTCRAFT_MCCLIENT_H
#define NEXTCRAFT_MCCLIENT_H


#include "McBuffer.h"
#include "TcpClient.h"
#include "../model/player/Player.h"
#include "../model/world/World.h"
#include "obj/Position.h"
#include "obj/DigAction.h"

class McClient {
private:
    TcpClient *client = new TcpClient();

    int compressionThreshold = 0;

    bool isLoginMode = true;

    bool closeRequested = false;

public:
    Player player{};

    World world{};

    void Connect(const char *username, const char *hostname, unsigned short port);

    void Disconnect();

private:
    int ReadVarInt();

    void HandlePacket(int packetId, McBuffer &buffer);

    void SendPacket(int packetId, McBuffer &buffer);

    static int ComputeRemainingChunkDataSize(bool continuous, bool skylight, int sections);

public:
    void SendHandshake(int protocolVersion, const char *hostname, unsigned short port, int nextState);

    void SendLogin(const char *username);

    void SendKeepAlive(int id);

    void SendChat(const char *message);

    void SendPosLook(double x, double y, double z, float yaw, float pitch, bool onGround);

    void SendDigging(DigAction action, Position pos, uint8_t face);

    void SendBlockPlacement(Position position, uint8_t face, uint8_t x, uint8_t y, uint8_t z);

    void SendRespawn();
};


#endif //NEXTCRAFT_MCCLIENT_H
