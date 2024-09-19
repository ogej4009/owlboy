#include "BumpBase.hlsli"
#include "RenderBase.hlsli"


struct VtxIn
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
    float4 Normal : NORMAL;
    float4 BiNormal : BINORMAL;
    float4 Tangent : TANGENT;
    float4 Weight : BLENDWEIGHT;
    int4 Index : BLENDINDICES;
};

struct VtxOut
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;  
    float4 ViewPos : POSITION;
    float4 ViewNormal : NORMAL;
    float4 ViewBiNormal : BINORMAL;
    float4 ViewTangent : TANGENT;
};

cbuffer TransData : register(b0)
{
    TransData TD;
}

VtxOut VS_Sky(VtxIn _In)
{
    _In.Normal.w = 0.0f;
   
    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, TD.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    
    _In.Pos.w = 1.0f;
    Out.ViewPos = mul(_In.Pos, TD.WV);
      
    _In.Normal.w = 0.0f;
    Out.ViewNormal = mul(_In.Normal, TD.WV);

    _In.BiNormal.w = 0.0f;
    Out.ViewBiNormal = mul(_In.BiNormal, TD.WV);

    _In.Tangent.w = 0.0f;
    Out.ViewTangent = mul(_In.Tangent, TD.WV);

    return Out;
}

struct ForwardOut
{
    float4 ForwardColor : SV_Target0;
};

cbuffer RenderOptionData : register(b8)
{
    RenderOption RO;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

ForwardOut PS_Sky(VtxOut _In)
{
    ForwardOut Out = (ForwardOut) 0;
    
    if (RO.IsDifTexture != 0)
    {
        Out.ForwardColor = Tex.Sample(Smp, _In.Uv.xy);
    }
    else
    {
        Out.ForwardColor = RO.BasicColor;
    }
    
    return Out;
}

