//
// Created by Twometer on 19/09/2019.
//

#include <iostream>
#include "McClient.h"
#include "NetUtils.h"
#include "../chat/ChatParser.h"
#include "../model/world/Chunk.h"
#include "obj/DigAction.h"
#include "obj/Position.h"

#define BUF_LEN 65565

using namespace chunk;

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
            std::cout << "Chat message: " << ChatParser::ToString(msg) << std::endl;
            break;
        }
        case 0x03: { // Time
            world.worldAge = buffer.ReadLong();
            world.time = buffer.ReadLong();
            break;
        }
        case 0x06: { // Health
            player.health = buffer.ReadFloat();
            player.hunger = buffer.ReadVarInt();
            break;
        }
        case 0x08: { // PosLook
            player.posX = buffer.ReadDouble();
            player.posY = buffer.ReadDouble();
            player.posZ = buffer.ReadDouble();

            player.yaw = buffer.ReadFloat();
            player.pitch = buffer.ReadFloat();
            break;
        }
        case 0x1F: { // Experience
            player.xpBar = buffer.ReadFloat();
            player.xpLevel = buffer.ReadVarInt();
            break;
        }
        case 0x21: { // Chunk data
            ChunkMeta meta = ReadChunkMeta(buffer, false);
            if (meta.continuous && meta.bitmask == 0) {
                world.RemoveChunk(meta.x, meta.z);
            } else {
                int filledSections = 0;
                auto *chunk = Chunk::Create(meta, buffer, filledSections);
                world.AddChunk(chunk);
            }
            break;
        }
        case 0x22: { // Multiple block update
            int chunkX = buffer.ReadInt();
            int chunkZ = buffer.ReadInt();
            Chunk *chunk = world.GetChunk(chunkX, chunkZ);
            int records = buffer.ReadVarInt();
            for (int i = 0; i < records; i++) {
                uint8_t horizontalPosition = buffer.ReadByte();
                uint8_t x = (horizontalPosition & 0xF0u) >> 4u;
                uint8_t z = (horizontalPosition & 0x0Fu);
                uint8_t y = buffer.ReadByte();
                BlockData data = BlockData(buffer.ReadVarInt());
                chunk->SetBlockData(x, y, z, data);
            }
            break;
        }
        case 0x23: { // Block update
            Position pos = Position(buffer.ReadULong());
            BlockData data = BlockData(buffer.ReadVarInt());
            world.SetBlockData(pos.x, pos.y, pos.z, data);
            break;
        }
        case 0x26: { // Chunk bulk
            bool skylight = buffer.ReadBool();
            int chunks = buffer.ReadVarInt();

            ChunkMeta metas[chunks];
            for (int i = 0; i < chunks; i++) {
                metas[i] = ReadChunkMeta(buffer, true);
            }

            for (int i = 0; i < chunks; i++) {
                ChunkMeta &meta = metas[i];

                int filledSections = 0;
                auto *chunk = Chunk::Create(meta, buffer, filledSections);
                world.AddChunk(chunk);

                buffer.Skip(ComputeRemainingChunkDataSize(meta.continuous, skylight, filledSections) - 8);
            }
            break;
        }
        case 0x40: { // Disconnect
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

void McClient::SendDigging(DigAction action, Position pos, uint8_t face) {
    McBuffer buf;
    buf.WriteVarInt(static_cast<int32_t> (action));
    buf.WriteULong(pos.Serialize());
    buf.Write(&face, 1);
    SendPacket(0x07, buf);
}

void McClient::SendBlockPlacement(Position position, uint8_t face, uint8_t x, uint8_t y, uint8_t z) {
    McBuffer buf;
    buf.WriteULong(position.Serialize());
    buf.Write(&face, 1);

    buf.WriteUShort(0);
    buf.WriteBool(false);
    buf.WriteUShort(0);
    buf.WriteBool(false);

    buf.Write(&x, 1);
    buf.Write(&y, 1);
    buf.Write(&z, 1);
    SendPacket(0x08, buf);
}

void McClient::SendRespawn() {
    McBuffer buf;
    buf.WriteVarInt(0);
    SendPacket(0x16, buf);
}

int McClient::ComputeRemainingChunkDataSize(bool continuous, bool skylight, int sectionsRead) {
    // int blockData = sectionsRead * 2 * 16 * 16 * 16; // <-- This is read, don't add
    int blocklightData = sectionsRead * 16 * 16 * 16 / 2;
    int skylightData = skylight ? sectionsRead * 16 * 16 * 16 / 2 : 0;
    int biomeData = continuous ? 256 : 0;
    return blocklightData + skylightData + biomeData;
}
