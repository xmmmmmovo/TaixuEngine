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
};

layout (std140) uniform LightSourse {
    vec4 light_position;
    vec4 light_color;
    vec4 camera_position;
};

layout (std140) uniform Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 emissive;
    float shininess;
};

uniform sampler2D textureSampler;

void main() 
{ 
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); 
    //FragColor = vec4(v2fTexCoord, 1.0f, 1.0f); 
    //FragColor = texture(textureSampler,fs_in.TexCoords).rgba;
    //FragColor = camera_position;
    //mat3 V3X3 = mat3(view);
    // vec3 color = texture(textureSampler,fs_in.TexCoords).rgb;
    // // ambient
    // vec3 ambient = color * 0.05;
    // // diffuse
    // vec3 lightDir = normalize(light_position.xyz - fs_in.FragPos);
    // vec3 normal = normalize(fs_in.Normal);
    // float diff = max(dot(lightDir, normal), 0.0);
    // vec3 diffuseColor = diff * color;
    // // specular
    // vec3 viewDir = normalize(camera_position.xyz - fs_in.FragPos);
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = 0.0;

    // vec3 halfwayDir = normalize(lightDir + viewDir);  
    // spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    // vec3 specularColor = vec3(0.3) * spec;
    // FragColor = vec4(ambient + diffuseColor + specularColor + emissive.xyz, 1.0);

    vec3 color = texture(textureSampler,fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.05 * color;
    // diffuse
    vec3 lightDir = normalize(light_position.xyz - fs_in.FragPos);
    vec3 normal = normalize(fs_in.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 viewDir = normalize(camera_position.xyz - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;

    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    
    vec3 specular = vec3(0.3) * spec; // assuming bright white light color
    FragColor = vec4(ambient + diffuse + specular, 1.0);
    //FragColor = vec4(viewDir,1.0f);
    //FragColor = light_position;
}