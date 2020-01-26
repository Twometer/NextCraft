//
// Created by twome on 26/01/2020.
//

#include <fstream>
#include <vector>
#include <spng.h>
#include "Loader.h"
#include "../util/Logger.h"

std::string Loader::ReadAllText(const std::string &path) {
    std::ifstream stream(path);
    std::string content((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    return content;
}

uint8_t *Loader::ReadAllBytes(const std::string &path, size_t &size) {
    std::ifstream file(path);
    file.seekg(0, std::ios::end);
    size_t length = file.tellg();
    file.seekg(0, std::ios::beg);

    if (length == -1)
        return nullptr;

    auto *buf = new uint8_t[length];
    file.read((char *) buf, length);
    size = length;

    file.close();
    return buf;
}

Image Loader::LoadImage(const std::string &path) {
    spng_ctx *ctx = spng_ctx_new(0);

    size_t inputSize;
    uint8_t *input = ReadAllBytes(path, inputSize);
    spng_set_png_buffer(ctx, input, inputSize);

    spng_ihdr ihdr{};
    spng_get_ihdr(ctx, &ihdr);

    size_t outputSize;
    spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &outputSize);

    auto *output = new uint8_t[outputSize];
    spng_decode_image(ctx, output, outputSize, SPNG_FMT_RGBA8, 0);

    delete[] input;

    return {output, outputSize, ihdr.width, ihdr.height};
}

void Loader::CheckShader(const std::string &name, GLuint shader) {
    int infoLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        std::vector<char> errorMsg(infoLogLength + 1);
        glGetShaderInfoLog(shader, infoLogLength, nullptr, &errorMsg[0]);
        Logger::Error("[" + name + "] " + std::string(&errorMsg[0]));
    }
}

GLuint Loader::LoadTexture(const std::string &path) {
    Image img = LoadImage(path);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return texture;
}

GLuint Loader::LoadShader(const std::string &vertPath, const std::string &fragPath) {
    Logger::Debug("Loading shader " + vertPath + " // " + fragPath);

    std::string vertSource = ReadAllText(vertPath);
    std::string fragSource = ReadAllText(fragPath);

    if (vertSource.empty() || fragSource.empty()) {
        Logger::Error("Shader is empty or does not exist");
        return 0;
    }

    GLuint program = glCreateProgram();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vs = vertSource.c_str();
    glShaderSource(vertShader, 1, &vs, nullptr);
    glCompileShader(vertShader);
    CheckShader("Vertex", vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fs = fragSource.c_str();
    glShaderSource(fragShader, 1, &fs, nullptr);
    glCompileShader(fragShader);
    CheckShader("Fragment", fragShader);

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);

    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}
