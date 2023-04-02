#version 410 core

layout (location = 0) in vec3 aPos;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;
uniform vec3 LightPosition_worldspace;
uniform mat4 transform;

void main() { gl_Position = MVP * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0); }