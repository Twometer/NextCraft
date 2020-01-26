//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_ISHADER_H
#define NEXTCRAFT_ISHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class IShader {
protected:
    GLuint id = 0;

    void Initialize(const std::string &name);

    virtual void BindUniforms() = 0;

    GLint GetLocation(const char *uniform);

    static void LoadMatrix(int loc, glm::mat4 matrix);

    static void LoadVec2(int loc, glm::vec2 vector);

    static void LoadVec3(int loc, glm::vec3 vector);

    static void LoadVec4(int loc, glm::vec4 vector);

public:
    void Use();

};


#endif //NEXTCRAFT_ISHADER_H
