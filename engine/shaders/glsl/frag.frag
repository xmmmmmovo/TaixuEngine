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
 
    vec3 color = texture(textureSampler,fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.05 * color;
    // diffuse
    vec3 lightDir = normalize(light_position.xyz - fs_in.FragPos);
    vec3 normal = normalize(fs_in.Normal);

    vec3 viewDir = normalize(camera_position.xyz - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir); 

    float nol = abs(dot(lightDir, normal));
    float noh = abs(dot(normal,halfwayDir ));

    float diff = max(nol, 0.0);
    vec3 diffuse = diff * color;
    
    // specular
    float spec = 0.0;
    spec = pow(max(noh, 0.0), 32.0);
    vec3 specular = vec3(0.3) * spec; // assuming bright white light color

    FragColor = vec4(ambient + diffuse + specular + emissive.xyz, 1.0);
    //FragColor = vec4(normal,1.0f);
    //FragColor = light_position;
}