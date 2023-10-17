#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

layout (location = 0) out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

layout (std140, binding = 0) uniform Matrices {
    mat4 projection;
    mat4 view;
    mat4 vp;

    vec4 camera_pos;
};

layout (std140, binding = 1) uniform Model {
    mat4 model;
    mat3 invModel3x3;
};

void main() {
    gl_Position = vp * model * vec4(position, 1.0f);
    vs_out.FragPos = vec3(model * vec4(position, 1.0));

    vs_out.TexCoords = texCoords;
    vs_out.Normal = invModel3x3 * normal;

}