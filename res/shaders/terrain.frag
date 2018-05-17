#version 400 core

in vec2 pass_texCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in float visibility;

out vec4 out_Colour;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

uniform vec3 lightColour;
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
    out_Colour = vec4(diffuse, 1.0) * totalCol + vec4(finalSpecular, 1.0);
    out_Colour = mix(vec4(skyColour, 1.0), out_Colour, visibility);
}
