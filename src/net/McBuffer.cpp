//
// Created by Twometer on 19/09/2019.
//

#include <cstring>
#include <algorithm>
#include "McBuffer.h"
#include "NetUtils.h"

#define INITIAL_SIZE 8192

McBuffer::McBuffer() {
    this->data = new uint8_t[INITIAL_SIZE];
    this->dataSize = INITIAL_SIZE;
};

McBuffer::McBuffer(uint8_t *buf, int length) {
    this->data = buf;
    this->dataSize = length;
}

uint8_t *McBuffer::GetBytes() {
    return data;
}

char *McBuffer::ReadString() {
    int len = ReadVarInt();
    char *result = new char[len + 1];
    result[len] = 0; // Null byte terminator
    Read(result, len);
    return result;
}

int32_t McBuffer::ReadInt() {
    int32_t v = 0;
    Read(&v, sizeof(v));
    std::reverse(&v, &v + sizeof(v));
    return v;
}

int32_t McBuffer::ReadVarInt() {
    int i = 0;
    int j = 0;
    int k = 0;
    while (true) {
        k = (int) (ReadByte());
        i |= (k & 0x7F) << j++ * 7;
        if (j > 5) return 0;
        if ((k & 0x80) != 128) break;
    }
    return i;
}

uint64_t McBuffer::ReadULong() {
    uint64_t v = 0;
    Read(&v, sizeof(v));
    std::reverse(&v, &v + sizeof(v));
    return v;
}

double McBuffer::ReadDouble() {
    double v = 0;
    Read(&v, sizeof(v));
    std::reverse(&v, &v + sizeof(v));
    return v;
}

float McBuffer::ReadFloat() {
    float v = 0;
    Read(&v, sizeof(v));
    std::reverse(&v, &v + sizeof(v));
    return v;
}

int16_t McBuffer::ReadShort() {
    int16_t v = 0;
    Read(&v, sizeof(v));
    std::reverse(&v, &v + sizeof(v));
    return v;
}

uint8_t McBuffer::ReadByte() {
    uint8_t b = *GetPosition();
    offset++;
    return b;
}

void McBuffer::Read(void *target, int len) {
    memcpy(target, GetPosition(), len);
    offset += len;
}

void McBuffer::Write(void *data, int len) {
    memcpy(GetPosition(), data, len);
    offset += len;
}

void McBuffer::Write(McBuffer &buf) {
    Write(buf.data, buf.offset);
}

void McBuffer::WriteVarInt(int32_t value) {
    int len = NetUtils::WriteVarInt(GetPosition(), value);
    offset += len;
}

void McBuffer::WriteUShort(uint16_t value) {
    Write(&value, sizeof(value));
}

void McBuffer::WriteULong(uint64_t value) {
    Write(&value, sizeof(value));
}

void McBuffer::WriteString(const char *value) {
    int len = strlen(value);
    WriteVarInt(len);
    Write((uint8_t *) value, len);
}

void McBuffer::WriteDouble(double value) {
    Write(&value, sizeof(value));
}

void McBuffer::WriteFloat(float value) {
    Write(&value, sizeof(value));
}

void McBuffer::WriteBool(bool value) {
    Write(&value, sizeof(value));
}

int32_t McBuffer::GetAllocated() {
    return offset;
}

void McBuffer::DecompressRemaining(int sizeUncompressed) {
    auto *buf = new uint8_t[sizeUncompressed];
    ZLib::Decompress(GetPosition(), dataSize - offset, buf, sizeUncompressed);
    this->data = buf;
    this->dataSize = sizeUncompressed;
    this->offset = 0;
}
