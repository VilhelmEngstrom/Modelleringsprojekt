#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out vec3 interpolatedNormal;
out vec2 st;

void main(void){
    gl_Position =  vec4(position, 1.0);
    interpolatedNormal = normal;
    st = texCoords;
}


#shader fragment
#version 330 core

in vec3 interpolatedNormal;
in vec2 st;

out vec4 color;

void main(void){
    vec4 col = vec4(1.0, 0.5, 1.0, 1.0);
    vec3 normNormal = normalize(interpolatedNormal);
    float diffuse = max(0.0, normNormal.z);
    color = col * diffuse;
}
