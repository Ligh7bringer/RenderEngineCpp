#version 400 core

layout (location = 0) in vec2 position;

out vec4 clipSpace;
out vec2 texCoords;
out vec3 toCameraVector;
out vec3 fromLightVector;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 cameraPos;

uniform vec3 lightPosition;

const float tiling = 4.0;

void main() {
    vec4 worldPos = modelMatrix * vec4(position.x, 0.0, position.y, 1.0);
    clipSpace = projectionMatrix * viewMatrix * worldPos;
    gl_Position = clipSpace;
    gl_ClipDistance[0] = 1;
    texCoords = vec2(position.x / 2.0 + 0.5, position.y / 2.0 + 0.5) * tiling;
    toCameraVector = cameraPos - worldPos.xyz;
    fromLightVector = worldPos.xyz - lightPosition;
}