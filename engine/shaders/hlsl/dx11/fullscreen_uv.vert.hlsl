// 使用一个三角形覆盖NDC空间
// (-1, 2)|\
//        |  \
// (-1, 1)|----\(1, 1)
//        |    | \
// (-1,-1)|____|___ (2, -1)
//          (1, -1)
void fullscreen_uv_vert_main(uint vertexID
                             : SV_VertexID, out float4 posH
                             : SV_POSITION, out float2 texcoord
                             : TEXCOORD0) {
  float2 uv = float2((vertexID << 1) & 2, vertexID & 2);
  texcoord = uv * float2(1.0f, 1.0f);
  posH = float4(uv * 2.0f - 1.0f, 0.0f, 1.0f);
}