//
// Created by Twometer on 19/09/2019.
//

#include <iostream>
#include "McClient.h"
#include "NetUtils.h"
#include "../chat/ChatParser.h"

#define BUF_LEN 65565

void McClient::Connect(const char *username, const char *hostname, unsigned short port) {
    if (!client->Connect(hostname, port))
        return;

    SendHandshake(47, hostname, port, 2);
    SendLogin(username);

    auto *recvBuf = new uint8_t[BUF_LEN];

    do {
        int packetLen = ReadVarInt();
        if (packetLen <= 0) continue;

        int received = client->Receive(recvBuf, packetLen);
        if (received <= 0) return;

        McBuffer buffer(recvBuf, packetLen);

        if (compressionThreshold > 0) {
            int sizeUncompressed = buffer.ReadVarInt();
            if (sizeUncompressed != 0)
                buffer.DecompressRemaining(sizeUncompressed);
        }

        int packetId = buffer.ReadVarInt();
        HandlePacket(packetId, buffer);

    } while (!closeRequested);

    if (!closeRequested)
        std::cout << "Connection lost" << std::endl;
}

void McClient::Disconnect() {
    client->Close();
    closeRequested = true;
}

int McClient::ReadVarInt() {
    int i = 0;
    int j = 0;
    int k = 0;
    while (true) {
        k = (int) ((unsigned char) client->ReadByte());
        i |= (k & 0x7F) << j++ * 7;
        if (j > 5) return 0;
        if ((k & 0x80) != 128) break;
    }
    return i;
}

void McClient::HandlePacket(int packetId, McBuffer &buffer) {
    if (isLoginMode) {
        if (compressionThreshold == 0 && packetId == 3)
            compressionThreshold = buffer.ReadVarInt();
        else if (packetId == 2)
            isLoginMode = false;
        return;
    }

    switch (packetId) {
        case 0x00: { // Keep Alive
            SendKeepAlive(buffer.ReadVarInt());
            break;
        }
        case 0x02: { // Chat
            auto msg = buffer.ReadString();
            std::cout << "Chat message: " << msg << std::endl;
            ChatParser::Parse(msg);
            break;
        }
        case 0x06: {
            float health = buffer.ReadFloat();
            break;
        }
        case 0x08: {
            break;
        }
        case 0x40: {
            auto msg = buffer.ReadString();
            std::cout << "Kicked from server: " << msg << std::endl;
            break;
        }
    }
}

void McClient::SendPacket(int packetId, McBuffer &buffer) {
    McBuffer buf;

    if (compressionThreshold > 0) {
        buf.WriteVarInt(NetUtils::GetVarIntSize(packetId) + NetUtils::GetVarIntSize(0) + buffer.GetAllocated());
        buf.WriteVarInt(0);
        buf.WriteVarInt(packetId);
        buf.Write(buffer);
    } else {
        buf.WriteVarInt(NetUtils::GetVarIntSize(packetId) + buffer.GetAllocated());
        buf.WriteVarInt(packetId);
        buf.Write(buffer);
    }

    client->Send(buf.GetBytes(), buf.GetAllocated());
}

// Login Packets
void McClient::SendHandshake(int protocolVersion, const char *hostname, unsigned short port, int nextState) {
    McBuffer buf;
    buf.WriteVarInt(protocolVersion);
    buf.WriteString(hostname);
    buf.WriteUShort(port);
    buf.WriteVarInt(nextState);
    SendPacket(0x00, buf);
}

void McClient::SendLogin(const char *username) {
    McBuffer buf;
    buf.WriteString(username);
    SendPacket(0x00, buf);
}

// Play Packets
void McClient::SendKeepAlive(int id) {
    McBuffer buf;
    buf.WriteVarInt(id);
    SendPacket(0x00, buf);
}

void McClient::SendChat(const char *message) {
    McBuffer buf;
    buf.WriteString(message);
    SendPacket(0x01, buf);
}

void McClient::SendPosLook(double x, double y, double z, float yaw, float pitch, bool onGround) {
    McBuffer buf;
    buf.WriteDouble(x);
    buf.WriteDouble(y);
    buf.WriteDouble(z);
    buf.WriteFloat(yaw);
    buf.WriteFloat(pitch);
    buf.WriteBool(onGround);
    SendPacket(0x06, buf);
}

void McClient::SendRespawn() {
    McBuffer buf;
    buf.WriteVarInt(0);
    SendPacket(0x16, buf);
}
