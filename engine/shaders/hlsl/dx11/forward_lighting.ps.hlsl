#include "lighting.hlsli"

// 像素着色器
float4 forward_lighting_ps_main(VertexOut pIn) : SV_Target
{
    return pIn.color;
}

