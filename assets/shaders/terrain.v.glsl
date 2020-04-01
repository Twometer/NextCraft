#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec3 fragmentColor;
out vec2 fragmentUV;

uniform mat4 matrix;

void main() {
    gl_Position = matrix * vec4(vertexPosition, 1.0f);

    fragmentColor = vertexColor;
    fragmentUV = vertexUV;
}