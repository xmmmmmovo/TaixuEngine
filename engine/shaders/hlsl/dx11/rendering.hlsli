
#ifndef RENDERING_HLSLI_9D19F36D256A4F4FBF5B88EEFFEE4778
#define RENDERING_HLSLI_9D19F36D256A4F4FBF5B88EEFFEE4778

cbuffer cbPerObject : register(b0) {
  float4x4 gWorld;
  float4x4 gWorldInvTranspose;
  float4x4 gWorldViewProj;
};

struct VertexIn {
  float3 pos : POSITION;
  float4 color : COLOR;
};

struct VertexOut {
  float4 posH : SV_POSITION;
  float4 color : COLOR;
};

#endif // RENDERING_HLSLI_9D19F36D256A4F4FBF5B88EEFFEE4778