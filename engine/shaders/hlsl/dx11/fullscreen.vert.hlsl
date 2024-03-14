
// 使用一个三角形覆盖NDC空间
// (-1, 2)|\
//        |  \
// (-1, 1)|----\(1, 1)
//        |    | \
// (-1,-1)|____|___ (2, -1)
//          (1, -1)
float4 fullscreen_vert_main(uint vertexID : SV_VertexID) : SV_POSITION {
  float2 uv = float2((vertexID << 1) & 2, vertexID & 2);
  return float4(uv * 2.0f - 1.0f, 0.0f, 1.0f);
}