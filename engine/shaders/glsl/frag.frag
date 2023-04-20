#version 410 core

layout (location = 0) in vec3 v3fNormal;
layout (location = 1) in vec2 v2fTexCoord;
layout (location = 2) in vec4 LightData[MAX_LIGHTS];

layout (std140) uniform Lights {
    vec4 lights[MAX_LIGHTS];
    int numLights;
};



//uniform sampler2d texture;

out vec4 FragColor;

void main() 
{ 
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); 
    FragColor = vec4(v2fTexCoord, 1.0f, 1.0f); 
    //FragColor = texture(texture,v2fTexCoord); 
}