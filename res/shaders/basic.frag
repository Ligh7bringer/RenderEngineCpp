#version 400 core

in vec2 pass_texCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in float visibility;

out vec4 out_Colour;

uniform sampler2D texSampler;
uniform vec3 lightColour[4];
uniform vec3 attenuation[4];
uniform float shineDamper;
uniform float reflectivity;
uniform vec3 skyColour;

void main() {
    //normalise normal
    vec3 unitNormal = normalize(surfaceNormal);
    //normalise to camera vector
    vec3 unitToCamera = normalize(toCameraVector);

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for(int i = 0; i < 4; i++) {
        float distance = length(toLightVector[i]);
        float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
        vec3 unitLightVector = normalize(toLightVector[i]);
        //calculate the angle between the normal and the to light vector
        float nDotl = dot(unitNormal, unitLightVector);
        //make sure brightness is not less than 0.2, should be 0 but if it's not less than 0.2, then there will be ambient lighting
        float brightness = max(nDotl, 0.0);
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
        //calculate diffuse factor
        totalDiffuse = totalDiffuse + (brightness * lightColour[i]) / attFactor;
        //the final specular colour is everything multiplied together
        totalSpecular = totalSpecular + (dampedFactor * reflectivity * lightColour[i]) / attFactor;
    }

    totalDiffuse = max(totalDiffuse, 0.2); //ambient lighting

    //handle transparent textures
    vec4 texColour = texture(texSampler, pass_texCoords);
    if(texColour.a < 0.5) {
        discard;
    }

    //calculate the colour of the pixel
    out_Colour = vec4(totalDiffuse, 1.0) * texColour + vec4(totalSpecular, 1.0);
    out_Colour = mix(vec4(skyColour, 1.0), out_Colour, visibility);
}
