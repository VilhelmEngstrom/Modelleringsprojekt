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

LightSource Light = LightSource(
    vec3(5.0, 15.0, 5.0),
    200.0
);

Material SoapFilm = Material(
    vec3(1.0, 0.2, 1.0),
    1000.0
);


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


void main(){
    vec3 ViewDirection = normalize(ModelPosition - cameraPos);
    vec3 Normal = normalize(ModelNormal);

    vec3 RefractColor = calculate_refraction(ViewDirection, Normal);

    vec3 ReflectColor = textureCube(skybox, reflect(ViewDirection, Normal)).rgb;

    vec3 FresnelTerm = vec3(fast_fresnel(-ViewDirection, Normal, fresnelValues));

    vec3 SpecularComponent = specular_highlight(ViewDirection, Normal);

    FragColor = vec4(mix(RefractColor, ReflectColor, FresnelTerm) + SpecularComponent, 0.2);

}
