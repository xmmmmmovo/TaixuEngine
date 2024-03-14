#version 460

layout (location = 0) in vec3 v3fColor;

layout (location = 0) out vec4 outColor;

void main() { outColor = vec4(v3fColor, 1.0f); }