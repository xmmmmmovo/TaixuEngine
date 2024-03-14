#include "rendering.hlsli"

// 像素着色器
float4 forward_frag_main(VertexOut pIn) : SV_Target { return pIn.color; }
