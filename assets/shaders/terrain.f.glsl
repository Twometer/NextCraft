#version 330 core

in vec3 fragmentColor;
in vec2 fragmentUV;
in float visibility;

out vec4 color;

uniform sampler2D tex;
uniform vec3 skyColor;
uniform float opacity;
uniform float brightness;

void main() {
    vec4 textureColor = texture(tex, fragmentUV);
    if (textureColor.a < 0.1f) {
        discard;
    }
    color = textureColor * vec4(fragmentColor, 1.0f);
    color = mix(vec4(skyColor, 1.0), color, opacity * visibility);
    color.rgb *= brightness;
}