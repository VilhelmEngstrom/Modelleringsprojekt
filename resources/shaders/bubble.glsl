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

out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

uniform vec3 cameraPos;
uniform samplerCube skybox;


void main(void){
    float ratio = 1.00 / 1.33;

    vec3 I = normalize(Position - cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio);
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}
