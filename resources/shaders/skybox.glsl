#shader vertex
#version 330 core


layout (location = 0) in vec3 VertexPosition;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main(){
    TexCoords = VertexPosition;
    gl_Position = (projection * view * vec4(VertexPosition, 1.0)).xyww;;
}

#shader fragment
#version 330 core


out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main(){
    FragColor = texture(skybox, TexCoords);
}
