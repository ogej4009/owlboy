#include "BumpBase.hlsli"

struct Vtx3D_In
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

struct Vtx3D_Out
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
    matrix POS;
    matrix SCALE;
    matrix ROT;
    matrix REVOL;
    matrix PARENT;
    matrix LWORLD;
    matrix WWORLD;
    matrix VIEW;
    matrix PROJ;
    matrix WV;
    matrix VP;
    matrix WVP;
}

Vtx3D_Out VS_StaticDeferredTexturePaperBurn(Vtx3D_In _In)
{
    _In.Normal.w = 0.0f;
    
    Vtx3D_Out Out = (Vtx3D_Out) 0;
    Out.Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    
    _In.Pos.w = 1.0f;
    Out.ViewPos = mul(_In.Pos, WV);
       
    _In.Normal.w = 0.0f;
    Out.ViewNormal = mul(_In.Normal, WV);

    _In.BiNormal.w = 0.0f;
    Out.ViewBiNormal = mul(_In.BiNormal, WV);

    _In.Tangent.w = 0.0f;
    Out.ViewTangent = mul(_In.Tangent, WV);

    return Out;
}

struct DeferredOut
{
    float4 DifColor : SV_Target0;
    float4 PosColor : SV_Target1;
    float4 NorColor : SV_Target2;
    float4 DepColor : SV_Target3;
};

cbuffer RenderOption : register(b8)
{
    int IsDifTexture;
    int IsNormalTexture;
    int IsShadow;
    int IsAni;
    int IsDummy0;
    int IsDummy1;
    int IsDummy2;
    int IsDummy3;
    float4 BasicColor;
}

cbuffer PaperBurn : register(b9)
{
    float4 PaperBurnSrc;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

DeferredOut PS_StaticDeferredTexturePaperBurn(Vtx3D_Out _In)
{
    DeferredOut Out = (DeferredOut) 0;
    
    if (IsDifTexture != 0)
    {
        Out.DifColor = Tex.Sample(Smp, _In.Uv.xy);
    }
    else
    {
        Out.DifColor = BasicColor;
    }
  
    Out.NorColor = _In.ViewNormal;
    Out.PosColor = _In.ViewPos;
    Out.DepColor.x = _In.ViewPos.z;
    
    if (Out.DifColor.b <= PaperBurnSrc.a)
    {
        Out.DifColor.a = 1;
    }
    else
    {
        Out.DifColor.a = 0;
    }
    
    Out.DepColor.w = Out.PosColor.w = Out.NorColor.w = 1.0f;
    return Out;
    
}