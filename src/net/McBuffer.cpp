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
    ownsBuffer = true;
};

McBuffer::McBuffer(uint8_t *buf, int length) {
    this->data = buf;
    this->dataSize = length;
}

McBuffer::~McBuffer() {
    if (ownsBuffer)
        delete[] data;
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
    Reverse(&v, sizeof(v));
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

int64_t McBuffer::ReadLong() {
    int64_t v = 0;
    Read(&v, sizeof(v));
    Reverse(&v, sizeof(v));
    return v;
}


uint64_t McBuffer::ReadULong() {
    uint64_t v = 0;
    Read(&v, sizeof(v));
    Reverse(&v, sizeof(v));
    return v;
}

double McBuffer::ReadDouble() {
    double v = 0;
    Read(&v, sizeof(v));
    Reverse(&v, sizeof(v));
    return v;
}

float McBuffer::ReadFloat() {
    float v = 0;
    Read(&v, sizeof(v));
    Reverse(&v, sizeof(v));
    return v;
}

int16_t McBuffer::ReadShort() {
    int16_t v = 0;
    Read(&v, sizeof(v));
    Reverse(&v, sizeof(v));
    return v;
}

uint16_t McBuffer::ReadBlockData() {
    uint16_t v = 0;
    Read(&v, sizeof(v));
    // For whatever reason, this is the only time the
    // byte order is little-endian
    return v;
}

uint8_t McBuffer::ReadByte() {
    uint8_t b = *GetPosition();
    offset++;
    return b;
}

bool McBuffer::ReadBool() {
    return ReadByte() == 0x01;
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
    Reverse(&value, sizeof(uint16_t));
    Write(&value, sizeof(value));
}

void McBuffer::WriteULong(uint64_t value) {
    Reverse(&value, sizeof(uint64_t));
    Write(&value, sizeof(value));
}

void McBuffer::WriteString(const char *value) {
    int len = strlen(value);
    WriteVarInt(len);
    Write((uint8_t *) value, len);
}

void McBuffer::WriteDouble(double value) {
    Reverse(&value, sizeof(double));
    Write(&value, sizeof(value));
}

void McBuffer::WriteFloat(float value) {
    Reverse(&value, sizeof(float));
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
    this->ownsBuffer = true;
}

void McBuffer::Reverse(void *ptr, int len) {
    auto *bytePtr = (uint8_t *) ptr;
    std::reverse(bytePtr, bytePtr + len);
}

void McBuffer::Skip(int len) {
    offset += len;
}

