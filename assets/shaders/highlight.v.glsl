#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform vec3 offset;
uniform vec3 size;

void main() {
    vec4 pos = vec4((vertexPosition * size) + offset, 1.0);
    gl_Position = projMatrix * viewMatrix * pos;
}