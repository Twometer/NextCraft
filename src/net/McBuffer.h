//
// Created by Twometer on 19/09/2019.
//

#ifndef NEXTCRAFT_MCBUFFER_H
#define NEXTCRAFT_MCBUFFER_H

#include <cstdint>

class McBuffer {

private:
    uint8_t* data = nullptr;

    int dataSize = 0;

    int offset = 0;

public:
    McBuffer();

    McBuffer(uint8_t * buf, int length);

    uint8_t *GetBytes();

    uint8_t *ReadToEnd(int* read);

    char* ReadString();

    int32_t ReadInt();

    int32_t ReadVarInt();

    uint64_t ReadULong();

    double ReadDouble();

    float ReadFloat();

    int16_t ReadShort();

    uint8_t ReadByte();

    void ReadArray(uint8_t *target, int len);

    void Write(void *data, int len);

    void WriteVarInt(int32_t value);

    void WriteUShort(uint16_t value);

    void WriteULong(uint64_t value);

    void WriteString(const char* value);

    void WriteDouble(double value);

    void WriteFloat(float value);

    void WriteBool(bool value);

    inline uint8_t *GetPosition() {
        return data + offset;
    }

};


#endif //NEXTCRAFT_MCBUFFER_H
