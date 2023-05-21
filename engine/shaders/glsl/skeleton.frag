#version 430 core
out vec4 FragColor;

in vec2 TexCoords;
in flat ivec4 IboneIds;
//uniform sampler2D texture_diffuse1;

void main()
{    
    //FragColor = texture(texture_diffuse1, TexCoords);
    FragColor = vec4(1.0,0.5,0.2,1.0);
}
