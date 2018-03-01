#shader vertex
#version 330 core

layout(location = 0) in vec3 mPos;
layout(location = 1) in vec3 mNormal;
layout(location = 2) in vec2 texCoords;

out vec3 Position;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void){
    Normal = mat3(transpose(inverse(model))) * mNormal;
    Position = vec3(model * vec4(mPos, 1.0));
    gl_Position = (projection * model) * vec4(mPos, 1.0);
}


#shader fragment
#version 330 core

// Outputs
out vec4 FragColor;

// Inputs
in vec3 Position;
in vec3 Normal;

// Uniforms
uniform vec3 cameraPos;
// power, scale and bias
uniform vec3 fresnelValues;
// Ratios for rgb refractions
uniform vec3 colorRatios;
uniform samplerCube skybox;

// Empirical approximation of fresnel reflection
float fast_fresnel(vec3 I, vec3 N, vec3 fresnelValues){
    float power = fresnelValues.x;
    float scale = fresnelValues.y;
    float bias = fresnelValues.z;

    return bias + scale * pow(1.0 - dot(I,N), power);
}

float weighted_mix(vec3 refraction, vec3 reflection, vec3 fresnal, vec3 wights){
    
}

void main(void){

    vec3 I = normalize(Position - cameraPos);
    vec3 normalVec = normalize(Normal);
    vec3 refractColor;

    refractColor.r = textureCube(skybox, refract(I, normalVec, colorRatios.r)).r;
    refractColor.g = textureCube(skybox, refract(I, normalVec, colorRatios.g)).g;
    refractColor.b = textureCube(skybox, refract(I, normalVec, colorRatios.b)).b;

    vec3 reflectColor = textureCube(skybox, reflect(I, normalVec)).rgb;

    vec3 fresnelTerm = vec3(fast_fresnel(-I, normalVec, fresnelValues));

    FragColor = vec4(mix(refractColor, reflectColor, fresnelTerm), 1.0);
}
