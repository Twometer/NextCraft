//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_LOADER_H
#define NEXTCRAFT_LOADER_H

#include <crystal/gl/Texture.h>
#include <glad/glad.h>
#include <string>
#include <cstdint>

struct Image {
    uint8_t *data;
    size_t size;
    uint32_t width;
    uint32_t height;
};

class Loader {
private:
    static Image LoadImage(const std::string &path);

    static void CheckShader(const std::string &name, GLuint shader);

public:
    static std::string ReadAllText(const std::string &path);

    static uint8_t *ReadAllBytes(const std::string &path, size_t &size);

    static crystal::Texture LoadTexture(const std::string &path, int filtering);

    static GLuint LoadShader(const std::string &vertPath, const std::string &fragPath);
};


#endif //NEXTCRAFT_LOADER_H
