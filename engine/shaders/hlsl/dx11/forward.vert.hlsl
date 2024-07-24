#include "rendering.hlsli"

// 顶点着色器
VertexOut forward_vert_main(VertexIn vIn) {
  VertexOut vOut;
  // vOut.posH = mul(float4(vIn.pos, 1.0f), gWorldViewProj);
  vOut.posH = float4(vIn.pos, 1.0f);
  vOut.color = vIn.color; // 这里alpha通道的值默认为1.0
  return vOut;
}
