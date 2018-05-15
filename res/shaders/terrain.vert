#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec2 pass_texCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

void main() {
    //calculate world position
    vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
    //set gl_Position to the correct value
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
    //pass texture coordinates to fragment shader
    pass_texCoords = texCoords * 40.0;

    //pass the surface normal, multiplied by transormation matrix so that any translations and rotations are taken into account
    surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;
    //calculate the vector pointing to the light source
    toLightVector = lightPosition - worldPosition.xyz;

    //calculate the vector pointing to the camera
    toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}
