#shader vertex

#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}

#shader fragment

#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, TexCoords);
}

/*
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex;

out vec3 texCoords;

uniform mat4 view;
uniform mat4 perspective;

void main(){
    vec4 pos = perspective * view * vec4(position, 1.0f);
    gl_Position = pos.xyww;

    texCoords = vec3(tex, 1.0);
}

#shader fragment

#version 330 core
in vec3 texCoords;

out vec4 color;

uniform samplerCube skybox;

void main(){
    color = texture(skybox, texCoords);
}
*/
