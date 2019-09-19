//
// Created by Twometer on 19/09/2019.
//

#include "McClient.h"

void McClient::Connect(const char *username, const char *hostname, unsigned short port) {

}

void McClient::Disconnect() {
    closeRequested = true;
}

void McClient::SendPacket(int packetId, McBuffer *buffer) {

}
