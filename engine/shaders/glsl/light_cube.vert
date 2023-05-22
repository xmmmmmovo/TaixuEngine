#version 410 core

layout (location = 0) in vec3 position;

layout (std140) uniform Matrices {
    mat4 projection;
    mat4 view;
    mat4 vp;

    vec4 camera_pos;
};

uniform mat4 model;

void main() {
    gl_Position = vp * model * vec4(position, 1.0f);
}