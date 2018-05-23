#version 400

in vec3 texCoords;

out vec4 out_Colour;

uniform samplerCube cubeMap;
uniform samplerCube cubeMap2;
uniform float blendFactor;
uniform vec3 fogColour;

const float lowerLimit = 0.0;
const float upperLimit = 30.0;

void main(void) {
    vec4 tex1 = texture(cubeMap, texCoords);
    vec4 tex2 = texture(cubeMap2, texCoords);

    vec4 finalColour = mix(tex1, tex2, blendFactor);

    float factor = (texCoords.y - lowerLimit) / (upperLimit - lowerLimit);
    factor = clamp(factor, 0.0, 1.0);
    out_Colour = mix(vec4(fogColour, 1.0), finalColour, factor);
}