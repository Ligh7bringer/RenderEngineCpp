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
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);

    float nDotl = dot(unitNormal, unitLightVector);
    float brightness = max(nDotl, 0.0);
    vec3 diffuse = brightness * lightColour;

    vec3 unitToCamera = normalize(toCameraVector);
    vec3 lightDir = -unitLightVector;
    vec3 reflectedLightDir = reflect(lightDir, unitNormal);

    float specularFactor = dot(reflectedLightDir, unitToCamera);
    specularFactor = max(specularFactor, 0.0);
    float dampedFactor = pow(specularFactor, shineDamper);
    vec3 finalSpecular = dampedFactor * reflectivity * lightColour;

    out_Colour = vec4(diffuse, 1.0) * texture(texSampler, pass_texCoords) + vec4(finalSpecular, 1.0);
}
