#version 410 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

out vec4 FragColor;

layout (std140) uniform Matrices {
    mat4 projection;
    mat4 view;
    mat4 vp;

    vec4 camera_pos;
};

layout (std140) uniform Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 emissive;
    float shininess;
};

uniform sampler2D diffuseTexture;

struct DirLight {
    vec4 direction;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight {
    vec4 position;

    float constant;
    float linear;
    float quadratic;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct SpotLight {
    vec4 position;
    vec4 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

#define MAX_DIR_LIGHTS 4

layout (std140) uniform LightSource {
    int dirLightCount;
    int pointLightCount;
    int spotLightCount;

    DirLight dirLights[MAX_DIR_LIGHTS];
    PointLight pointLights[MAX_DIR_LIGHTS];
    SpotLight spotLights[MAX_DIR_LIGHTS];
};

void main()
{
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    //    ambient
    vec3 ambient = 0.05 * color;
    vec3 normal = normalize(fs_in.Normal);
    vec3 viewDir = normalize(camera_pos.xyz - fs_in.FragPos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < pointLightCount; i++) {
        // diffuse
        vec3 lightDir = normalize(pointLights[i].position.xyz - fs_in.FragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);

        float nol = abs(dot(lightDir, normal));
        float noh = abs(dot(normal, halfwayDir));

        float diff = max(nol, 0.0);
        vec3 diffuse = diff * color;

        // specular
        float spec = 0.0;
        spec = pow(max(noh, 0.0), 32.0);
        vec3 specular = vec3(0.3) * spec; // assuming bright white light color

        result += (ambient + diffuse + specular) * pointLights[i].diffuse.rgb;
    }
    FragColor = vec4(result, 1.0);
}