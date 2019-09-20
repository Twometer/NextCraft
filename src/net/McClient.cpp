//
// Created by Twometer on 19/09/2019.
//

#include "McClient.h"

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
    buf.WriteVarInt(packetId);
    buf.Write(buffer);

    McBuffer buf2;
    buf2.WriteVarInt(buf.GetAllocated());
    buf2.Write(buf);

    client->Send(buf2.GetBytes(), buf2.GetAllocated());
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
