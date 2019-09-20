//
// Created by Twometer on 19/09/2019.
//

#include <cstring>
#include <algorithm>
#include "McBuffer.h"
#include "NetUtils.h"

McBuffer::McBuffer() {
    this->data = new uint8_t[8192];
    this->dataSize = 8192;
};

McBuffer::McBuffer(uint8_t *buf, int length) {
    this->data = buf;
    this->dataSize = length;
}

uint8_t *McBuffer::GetBytes() {
    return data;
}

uint8_t *McBuffer::ReadToEnd(int *read) {
    *read = dataSize - offset;
    auto *result = new uint8_t[*read];
    memcpy(result, GetPosition(), *read);
    return result;
}

char *McBuffer::ReadString() {
    return nullptr;
}

int32_t McBuffer::ReadInt() {
    int32_t v = 0;
    memcpy(&v, GetPosition(), sizeof(v));
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
    memcpy(&v, GetPosition(), sizeof(v));
    std::reverse(&v, &v + sizeof(v));
    return v;
}

double McBuffer::ReadDouble() {
    double v = 0;
    memcpy(&v, GetPosition(), sizeof(v));
    std::reverse(&v, &v + sizeof(v));
    return v;
}

float McBuffer::ReadFloat() {
    float v = 0;
    memcpy(&v, GetPosition(), sizeof(v));
    std::reverse(&v, &v + sizeof(v));
    return v;
}

int16_t McBuffer::ReadShort() {
    int16_t v = 0;
    memcpy(&v, GetPosition(), sizeof(v));
    std::reverse(&v, &v + sizeof(v));
    return v;
}

uint8_t McBuffer::ReadByte() {
    uint8_t b = *GetPosition();
    offset++;
    return b;
}

void McBuffer::ReadArray(uint8_t *target, int len) {
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
