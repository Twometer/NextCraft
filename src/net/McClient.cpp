//
// Created by Twometer on 19/09/2019.
//

#include <iostream>
#include "McClient.h"
#include "NetUtils.h"

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

void McClient::HandlePacket(int packetId, McBuffer &buffer) {
    if (isLoginMode) {
        if (compressionThreshold == 0 && packetId == 3)
            compressionThreshold = buffer.ReadVarInt();
        else if (packetId == 2)
            isLoginMode = false;
        return;
    }

    std::cout << "Handling packet " << packetId << std::endl;
}

void McClient::SendPacket(int packetId, McBuffer &buffer) {
    McBuffer buf;

    if (compressionThreshold > 0) {
        buf.WriteVarInt(NetUtils::GetVarIntSize(packetId) + NetUtils::GetVarIntSize(0) + buffer.GetAllocated());
        buf.WriteVarInt(packetId);
        buf.WriteVarInt(0);
        buf.Write(buffer);
    } else {
        buf.WriteVarInt(NetUtils::GetVarIntSize(packetId) + buffer.GetAllocated());
        buf.WriteVarInt(packetId);
        buf.Write(buffer);
    }

    client->Send(buf.GetBytes(), buf.GetAllocated());
}

void McClient::SendHandshake(int protocolVersion, const char *hostname, unsigned short port, int nextState) {
    McBuffer buf;
    buf.WriteVarInt(protocolVersion);
    buf.WriteString(hostname);
    buf.WriteUShort(port);
    buf.WriteVarInt(nextState);
    SendPacket(0, buf);
}

void McClient::SendLogin(const char *username) {
    McBuffer buf;
    buf.WriteString(username);
    SendPacket(0, buf);
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
