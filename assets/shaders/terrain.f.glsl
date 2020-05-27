#version 330 core

in vec3 fragmentColor;
in vec2 fragmentUV;

uniform sampler2D tex;

uniform float opacity;

out vec4 color;

void main() {
    vec4 textureColor = texture(tex, fragmentUV);
    if (textureColor.a < 0.1f) {
        discard;
    }
    color = textureColor * vec4(fragmentColor, 1.0f);
    color.a *= opacity;
}