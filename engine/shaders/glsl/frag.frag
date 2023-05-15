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
    vec3 light_position;
    vec3 light_color;
    vec3 camera_position;
};

layout (std140) uniform Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 emissive;
    float shininess;
};

void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }

// void main() 
// { 
//     //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); 
//     //FragColor = vec4(v2fTexCoord, 1.0f, 1.0f); 
//     //FragColor = texture(texturesampler,v2fTexCoord).rgba;
//     //FragColor = diffuse;
//     mat3 V3X3 = mat3(view);
//     vec3 color = vec3(1.0f, 0.5f, 0.2f);
//     // ambient
//     vec3 ambientColor = 0.05 * color;
//     // diffuse
//     vec3 lightDir = normalize(V3X3*light_position - fs_in.FragPos);
//     vec3 normal = normalize(fs_in.Normal);
//     float diff = max(dot(lightDir, normal), 0.0);
//     vec3 diffuseColor = diff * color;
//     // specular
//     vec3 viewDir = normalize(camera_position - fs_in.FragPos);
//     vec3 reflectDir = reflect(-lightDir, normal);
//     float spec = 0.0;

//     vec3 halfwayDir = normalize(lightDir + viewDir);  
//     spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

//     vec3 specularColor = vec3(0.3) * spec; // assuming bright white light color
//     FragColor = vec4(ambientColor + diffuseColor + specularColor + emissive.xyz, 1.0);

// }