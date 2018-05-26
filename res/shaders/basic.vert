#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec2 pass_texCoords;
out vec3 surfaceNormal;
out vec3 toLightVector[4]; //a vector per light
out vec3 toCameraVector;
out float visibility; //used for fog

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition[4]; //positions of all lights
uniform float useFakeLighting;
uniform float numberOfRows; //texture atlas vars
uniform vec2 offset;

//fog constants
const float density = 0.0035;
const float gradient = 5.0;
//clipping plane
uniform vec4 plane;

void main() {
    //calculate world position
    vec4 worldPosition = transformationMatrix * vec4(position, 1.0);

    gl_ClipDistance[0] = dot(worldPosition, plane);

    vec4 posRelativeToCam = viewMatrix * worldPosition;
    //set gl_Position to the correct value
    gl_Position = projectionMatrix * posRelativeToCam;
    //pass texture coordinates to fragment shader
    pass_texCoords = (texCoords / numberOfRows) + offset;

    //change the normal to point up if fake lighting is used for this vertex
    vec3 actualNormal = normal;
    if(useFakeLighting > 0.5) {
        actualNormal = vec3(0.0, 1.0, 0.0);
    }

    //pass the surface normal, multiplied by transormation matrix so that any translations and rotations are taken into account
    surfaceNormal = (transformationMatrix * vec4(actualNormal, 0.0)).xyz;

    for(int i = 0; i < 4; i++) {
          //calculate the vector pointing to the light source
            toLightVector[i] = lightPosition[i] - worldPosition.xyz;
    }

    //calculate the vector pointing to the camera
    toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

    float distance = length(posRelativeToCam.xyz);
    visibility = exp(-pow((distance * density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);
}
