#version 400 core

in vec2 pass_texCoords;

out vec4 FragColor;

uniform sampler2D texSampler;

void main() {
    FragColor = texture(texSampler, pass_texCoords);
}
