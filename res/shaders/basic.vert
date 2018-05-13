#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec3 colour;
out vec2 pass_texCoords;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);
    pass_texCoords = texCoords;
}
