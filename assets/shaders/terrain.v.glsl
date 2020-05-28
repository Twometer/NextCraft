#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec3 fragmentColor;
out vec2 fragmentUV;
out float visibility;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;

const float fogDensity = 0.0115;
const float fogGradient = 2.5;
const float fogDistance = 45;
const float fogHeight = 64;
const float fogYGradient = 60;

void main() {
    vec4 position = vec4(vertexPosition, 1.0f);
    vec4 camPosition = viewMatrix * position;
    gl_Position = projMatrix * camPosition;

    fragmentColor = vertexColor;
    fragmentUV = vertexUV;

    float distance = length(camPosition.xyz);
    if (distance > fogDistance) {
        float yFac = 1 - ((position.y - fogHeight) / fogYGradient);
        visibility = exp(-pow(((distance - fogDistance) * fogDensity * yFac), fogGradient));
        visibility = clamp(visibility, 0.0, 1.0);
    } else visibility = 1.0;
}