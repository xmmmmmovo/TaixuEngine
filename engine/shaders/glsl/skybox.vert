#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

layout (std140) uniform Matrices {
    mat4 projection;
    mat4 view;
    mat4 vp;
};

void main()
{
    TexCoords = aPos;
    vec4 pos = vp * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}