//
// Created by Twometer on 19/09/2019.
//

#ifndef NEXTCRAFT_MCCLIENT_H
#define NEXTCRAFT_MCCLIENT_H


#include "McBuffer.h"

class McClient {
private:
    bool closeRequested = false;

public:
    void Connect(const char* username, const char* hostname, unsigned short port);

    void Disconnect();

    void SendPacket(int packetId, McBuffer* buffer);

};


#endif //NEXTCRAFT_MCCLIENT_H
