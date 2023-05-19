#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

layout (std140) uniform Matrices {
    mat4 projection;
    mat4 view;
    mat4 vp;
};

uniform mat4 model;
uniform mat3 invModel3x3;

void main() {
    gl_Position = vp * model * vec4(position, 1.0f);
    vs_out.FragPos = vec3(model * vec4(position, 1.0));

    vs_out.TexCoords = texCoords;
    vs_out.Normal = invModel3x3 * normal;

}