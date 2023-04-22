#version 410 core

layout (location = 0) in vec3 v3fNormal;
layout (location = 1) in vec2 v2fTexCoord;
layout (location = 2) in vec3 v3fFragPos;

#define MAX_LIGHTS 10

struct Light {
   vec4 position;
   vec4 color;
};

uniform float shininess;
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emissive;

uniform vec3 cameraPos;
layout (std140) uniform Lights {
    Light lights[MAX_LIGHTS];
    int num;
};

//uniform sampler2d texture;

out vec4 FragColor;

void main() 
{ 
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //FragColor = lights[0].color;
    //FragColor = vec4(v2fTexCoord, 1.0f, 1.0f);
    //FragColor = specular;

    vec3 color = vec3(1.0f, 0.5f, 0.2f);
    // ambient
    vec3 ambientColor = 0.05 * color;
    // diffuse
    vec3 lightDir = normalize(lights[0].position.xyz - v3fFragPos);
    vec3 normal = normalize(v3fNormal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuseColor = diff * color;
    // specular
    vec3 viewDir = normalize(cameraPos - v3fFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;

    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specularColor = vec3(0.3) * spec; // assuming bright white light color
    FragColor = vec4(ambientColor + diffuseColor + specularColor + emissive.xyz, 1.0);
}