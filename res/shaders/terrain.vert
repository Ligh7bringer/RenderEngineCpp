#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec2 pass_texCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out float visibility; //fog stuff

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

//constants for the fog
const float density = 0.0035;
const float gradient = 5.0;

void main() {
    //calculate world position
    vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
    vec4 posRelativeToCam = viewMatrix * worldPosition;
    //set gl_Position to the correct value
    gl_Position = projectionMatrix * posRelativeToCam;
    //pass texture coordinates to fragment shader
    pass_texCoords = texCoords;

    //pass the surface normal, multiplied by transormation matrix so that any translations and rotations are taken into account
    surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;
    //calculate the vector pointing to the light source
    toLightVector = lightPosition - worldPosition.xyz;

    //calculate the vector pointing to the camera
    toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

    //calculate visibility for the fog
    float distance = length(posRelativeToCam.xyz);
    visibility = exp(-pow((distance * density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);
}
