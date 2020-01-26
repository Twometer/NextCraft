//
// Created by twome on 26/01/2020.
//

#include "IShader.h"
#include "../../gl/Loader.h"

void IShader::Initialize(const std::string &name) {
    this->id = Loader::LoadShader("assets/shaders/" + name + ".v.glsl", "assets/shaders/" + name + ".f.glsl");
    BindUniforms();
}

GLint IShader::GetLocation(const char *uniform) {
    return glGetUniformLocation(id, uniform);
}

void IShader::LoadMatrix(int loc, glm::mat4 matrix) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}

void IShader::LoadVec2(int loc, glm::vec2 vector) {
    glUniform2f(loc, vector.x, vector.y);
}

void IShader::LoadVec3(int loc, glm::vec3 vector) {
    glUniform3f(loc, vector.x, vector.y, vector.z);
}

void IShader::LoadVec4(int loc, glm::vec4 vector) {
    glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
}

void IShader::Use() {
    glUseProgram(id);
}