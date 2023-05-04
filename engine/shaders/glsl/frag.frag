#version 410 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

out vec4 FragColor;

void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }