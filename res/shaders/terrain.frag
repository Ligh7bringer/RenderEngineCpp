#version 400 core

in vec2 pass_texCoords;
in vec3 surfaceNormal;
in vec3 toLightVector[4];
in vec3 toCameraVector;
in float visibility;

out vec4 out_Colour;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

uniform vec3 lightColour[4];
uniform vec3 attenuation[4];
uniform float shineDamper;
uniform float reflectivity;
uniform vec3 skyColour;

void main() {
    //get colour of blend map to find out how much of each texture should be rendered
    vec4 blendMapColour = texture(blendMap, pass_texCoords);
    //amount of background texture
    float backTextureAmount = 1 - (blendMapColour.r + blendMapColour.g + blendMapColour.b);
    //repeat texture
    vec2 tiledCoords = pass_texCoords * 40.0;
    //calculate colours of each texture
    vec4 backgroundTextureCol = texture(backgroundTexture, tiledCoords) * backTextureAmount;
    vec4 rTextureCol = texture(rTexture, tiledCoords) * blendMapColour.r; //this texture amount depends on how much red there is in the blendmap texture
    vec4 gTextureCol = texture(gTexture, tiledCoords) * blendMapColour.g; //same but green
    vec4 bTextureCol = texture(bTexture, tiledCoords) * blendMapColour.b; //same but blue
    vec4 totalCol = backgroundTextureCol + rTextureCol + gTextureCol + bTextureCol;

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

    totalSpecular = max(totalSpecular, 0.0);

    //calculate the colour of the pixel
    out_Colour = vec4(totalDiffuse, 1.0) * totalCol + vec4(totalSpecular, 1.0);
    out_Colour = mix(vec4(skyColour, 1.0), out_Colour, visibility);
}
