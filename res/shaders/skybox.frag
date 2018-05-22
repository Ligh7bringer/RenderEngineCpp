#version 400

in vec3 texCoords;

out vec4 out_Colour;

uniform samplerCube cubeMap;

void main(void) {
    out_Colour = texture(cubeMap, texCoords);
}