#version 400 core

in vec2 pass_texCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 out_Colour;

uniform sampler2D texSampler;
uniform vec3 lightColour;
uniform float shineDamper;
uniform float reflectivity;

void main() {
    //normalise normal and toLight vector
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);

    //calculate the angle between the normal and the to light vector
    float nDotl = dot(unitNormal, unitLightVector);
    //make sure brightness is not less than 0.2, should be 0 but if it's not less than 0.2, then there will be ambient lighting
    float brightness = max(nDotl, 0.2);
    //calculate diffuse factor
    vec3 diffuse = brightness * lightColour;

    //normalise to camera vector
    vec3 unitToCamera = normalize(toCameraVector);
    //light direction is the opposite of the to light vector
    vec3 lightDir = -unitLightVector;
    //calculate the direction of the reflected light
    vec3 reflectedLightDir = reflect(lightDir, unitNormal);

    //calculate angle between reflected light vector and to camera vector
    float specularFactor = dot(reflectedLightDir, unitToCamera);
    //make sure the specular factor is not less than 0
    specularFactor = max(specularFactor, 0.0);
    //damped factor is just specular factor raised to the power of shine damper
    float dampedFactor = pow(specularFactor, shineDamper);
    //the final specular colour is everything multiplied together
    vec3 finalSpecular = dampedFactor * reflectivity * lightColour;

    //calculate the colour of the pixel
    out_Colour = vec4(diffuse, 1.0) * texture(texSampler, pass_texCoords) + vec4(finalSpecular, 1.0);
}
