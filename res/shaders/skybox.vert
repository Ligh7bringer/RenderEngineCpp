#version 400

layout (location = 0) in vec3 position;

out vec3 texCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(void) {
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
    gl_ClipDistance[0] = 1;
    texCoords = position;
}