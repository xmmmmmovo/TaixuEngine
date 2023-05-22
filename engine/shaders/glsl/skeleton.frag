#version 410 core

out vec4 FragColor;

in vec2 TexCoords;

flat in ivec4 IboneIds;

void main()
{
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
