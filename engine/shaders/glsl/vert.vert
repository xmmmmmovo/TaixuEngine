#version 410 core

#define MAX_LIGHTS 10

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (location = 0) out vec3 v3fNormal;
layout (location = 1) out vec2 v2fTexCoord;
layout (location = 2) out vec4 LightData[MAX_LIGHTS];

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;
//uniform vec3 LightPosition_worldspace;

struct Light {
    vec4 position;
    vec4 color;
};

layout(std140) uniform Lights {
    Light lights[MAX_LIGHTS];
    int numLights;
};


void main() 
{ 
    gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    v2fTexCoord = aTexCoord;
    v3fNormal = aNormal;
}