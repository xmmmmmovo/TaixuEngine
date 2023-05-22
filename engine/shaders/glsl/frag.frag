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

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightPos = light.position.xyz;
    vec3 lightDir = normalize(lightPos - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance = length(lightPos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient.rgb;
    vec3 diffuse = light.diffuse.rgb * diff * vec3(texture(diffuseTexture, fs_in.TexCoords));
    vec3 specular = light.specular.rgb * spec;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 objectColor = vec3(texture(diffuseTexture, fs_in.TexCoords));
    vec3 normal_norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(camera_pos.xyz - fs_in.FragPos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < pointLightCount; i++) {
        // ambient
        float ambientStrength = 0.3;
        vec3 ambient = ambientStrength * pointLights[i].ambient.rgb;

        // diffuse
        vec3 lightDir = normalize(pointLights[i].position.xyz - fs_in.FragPos);

        vec3 halfwayDir = normalize(lightDir + viewDir);

        float noh = abs(dot(normal_norm, halfwayDir));

        float diff = max(dot(normal_norm, lightDir), 0.0);
        vec3 diffuse = diff * pointLights[i].diffuse.rgb;

        // specular
        float specularStrength = 0.3;
        float spec = pow(max(noh, 0.0), 32.0f);
        vec3 specular = specularStrength * spec * pointLights[i].specular.rgb;

        result += (ambient + diffuse + specular) * objectColor;
    }
    FragColor = vec4(result, 1.0);
}