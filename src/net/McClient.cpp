//
// Created by Twometer on 19/09/2019.
//

#include "McClient.h"
#include "NetUtils.h"

void McClient::Connect(const char *username, const char *hostname, unsigned short port) {
    if (!client->Connect(hostname, port))
        return;

    SendHandshake(47, hostname, port, 2);
    SendLogin(username);
}

void McClient::Disconnect() {
    client->Close();
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
