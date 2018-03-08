#shader vertex
#version 330 core



layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 TexCoords;

out vec3 ModelPosition;
out vec3 ModelNormal;

uniform mat4 model;
uniform mat4 projection;

void main(){
    ModelNormal = mat3(transpose(inverse(model))) * VertexNormal;
    ModelPosition = vec3(model * vec4(VertexPosition, 1.0));
    gl_Position = (projection * model) * vec4(VertexPosition, 1.0);
}


#shader fragment
#version 330 core

#define MOTHER_OF_PEARL

out vec4 FragColor;

in vec3 ModelPosition;
in vec3 ModelNormal;


uniform vec3 cameraPos;
// power, scale and bias
uniform vec3 fresnelValues;
// Ratios for rgb refractions
uniform vec3 colorRatios;
uniform samplerCube skybox;


struct LightSource{
    vec3 Position;
    float Intensity;
};

struct Material{
    vec3 Color;
    float Shininess;
};

const LightSource Light = LightSource(
    vec3(5.0, 15.0, 5.0),
    200.0
);

const Material SoapFilm = Material(
    vec3(1.0, 0.2, 1.0),
    1000.0
);

const float MotherPearlBrightness = 1.5;

// Empirical approximation of fresnel reflection
float fast_fresnel(vec3 I, vec3 N, vec3 FresnelValues){
    float Power = FresnelValues.x;
    float Scale = FresnelValues.y;
    float Bias = FresnelValues.z;

    return max(0, min(1, Bias + Scale * pow(1.0 + dot(I,N), Power)));
}


vec3 modified_refraction(vec3 I, vec3 N, float Eta){
    float Cosi = dot(-I, N);
    float Cost2 = 1.0 - Eta * Eta * (1.0 - Cosi*Cosi);
    vec3 T = Eta * I + ((Eta * Cosi - sqrt(abs(Cost2))) * N);

    return T * vec3(Cost2 > 0.0);
}

vec3 calculate_refraction(vec3 ViewDirection, vec3 Normal){
    vec3 RefractColor;

    RefractColor.r = textureCube(skybox, modified_refraction(ViewDirection, Normal, colorRatios.r)).r;
    RefractColor.g = textureCube(skybox, modified_refraction(ViewDirection, Normal, colorRatios.g)).g;
    RefractColor.b = textureCube(skybox, modified_refraction(ViewDirection, Normal, colorRatios.b)).b;

    return RefractColor;
}

vec3 specular_highlight(vec3 ViewDirection, vec3 Normal){
    vec3 IncidentLight = normalize(ModelPosition - Light.Position);
    vec3 SpecularDirection = reflect(IncidentLight, Normal);

    float Angle = max(0.0, dot(-ViewDirection, SpecularDirection));

    float SpecularCoefficient = pow(Angle, SoapFilm.Shininess);

    return SpecularCoefficient * SoapFilm.Color * Light.Intensity;
}

#ifdef MOTHER_OF_PEARL
// Calculate a mother of pearl effect (color patterns)
vec3 mother_of_pearl(vec3 ViewDirection, vec3 Normal, vec3 NormalizedReflection, vec3 Colors){
    float ViewNormalAngle = max(0.0, dot(Normal, ViewDirection));
    float ViewNormalAngleInverse = 1.0 - ViewNormalAngle;

    vec3 Effect = textureCube(skybox, NormalizedReflection).rgb * ViewNormalAngle;

    Effect.r += MotherPearlBrightness * textureCube(skybox, NormalizedReflection + vec3(Colors.r, 0.0, 0.0) * ViewNormalAngleInverse).r * ViewNormalAngleInverse;
    Effect.g += MotherPearlBrightness * textureCube(skybox, NormalizedReflection + vec3(0.0, Colors.g, 0.0) * ViewNormalAngleInverse).g * ViewNormalAngleInverse;
    Effect.b += MotherPearlBrightness * textureCube(skybox, NormalizedReflection + vec3(0.0, 0.0, Colors.b) * ViewNormalAngleInverse).b * ViewNormalAngleInverse;

    return Effect;
}
#endif


void main(){
    vec3 ViewDirection = normalize(ModelPosition - cameraPos);
    vec3 Normal = normalize(ModelNormal);
    vec3 NormalizedReflection = normalize(reflect(ViewDirection, Normal));


    vec3 RefractColor = calculate_refraction(ViewDirection, Normal);

    vec3 ReflectColor = textureCube(skybox, NormalizedReflection).rgb;

    vec3 FresnelTerm = vec3(fast_fresnel(-ViewDirection, Normal, fresnelValues));

    vec3 SpecularComponent = specular_highlight(ViewDirection, Normal);


    #ifdef MOTHER_OF_PEARL
    vec3 MotherOfPearlEffect = mother_of_pearl(ViewDirection, Normal, NormalizedReflection, vec3(1.0, 0.1, 1.0));
    vec3 Color = mix(mix(RefractColor, ReflectColor, FresnelTerm), MotherOfPearlEffect, 0.5);
    FragColor = vec4(Color + SpecularComponent, 0.15);
    #else
    FragColor = vec4(mix(RefractColor, ReflectColor, FresnelTerm) + SpecularComponent, 0.15);
    #endif

}
