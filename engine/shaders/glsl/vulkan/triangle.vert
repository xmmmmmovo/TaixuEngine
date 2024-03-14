#version 460

const vec2 kVertexPositions[6] =
vec2[6](vec2(0.0f, -0.8f), vec2(-0.7f, 0.8f), vec2(0.7f, 0.8f),
        vec2(0.1f, -0.8f), vec2(0.5f, 0.0f), vec2(0.9f, 0.0f));

const vec3 kVertexColors[6] =
vec3[6](vec3(1.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f),
        vec3(1.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 0.f, 1.f));


layout (location = 0) out vec3 v2fColor;

void main() {
    const vec2 xy = kVertexPositions[gl_VertexIndex];
    gl_Position = vec4(xy, 0.5f, 1.0f);
    v2fColor = kVertexColors[gl_VertexIndex];
}