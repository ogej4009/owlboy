#include "RenderBase.hlsli"

struct VtxIn
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

struct VtxOut
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

cbuffer TransData : register(b0)
{
    TransData TD;
}

cbuffer RenderOptionData : register(b7)
{
    RenderOption RO;
}

cbuffer CutData : register(b1)
{
    CutData CD;
};

VtxOut VS_Distortion(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, TD.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    Out.Pos.x += CD.Data.y * sin(CD.Data.x * Out.Pos.y + CD.Data.z * CD.Data.w);
    return Out;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_Distortion(VtxOut _Out) : SV_Target0
{
    float4 Return = Tex.Sample(Smp, _Out.Uv.xy);
    return Return; 
}
