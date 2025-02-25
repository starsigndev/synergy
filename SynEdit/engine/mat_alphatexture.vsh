cbuffer Constants
{
    float4x4 g_MVP;
    float4 scc;

};

struct VSInput
{
     float3 Pos   : ATTRIB0;
    float4 Color : ATTRIB1;
    float3 Uv : ATTRIB2;
    float3 Norm : ATTRIB3;
    float3 BiNorm : ATTRIB4;
    float3 Tang : ATTRIB5;
    float4 m_BoneIds : ATTRIB6;
    float4 m_Weights : ATTRIB7;

};

struct PSInput 
{ 
 float4 Pos   : SV_POSITION;
 float3 Uv : TEX_COORD;
 float4 v_Color : COLOR2;
 float4 v_Scissor : POSITION1;
 float4 v_Fx : POSITION2;

};

void main(in  VSInput VSIn,
          out PSInput PSIn) 
{

   PSIn.Pos = mul(float4(VSIn.Pos, 1.0), g_MVP);
   PSIn.Uv = VSIn.Uv; 
   PSIn.v_Color = VSIn.Color;
   PSIn.v_Scissor = VSIn.m_Weights;
   PSIn.v_Fx = float4(VSIn.m_BoneIds.x,VSIn.m_BoneIds.y,0,0);
 
}
