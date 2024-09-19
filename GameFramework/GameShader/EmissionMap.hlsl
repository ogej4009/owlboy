#include "AnimationBase.hlsli"
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
};

struct DeferredOut
{
    float4 OutColor : SV_Target5;
};

cbuffer RenderOptionData : register(b7)
{
    RenderOption RO;
}

Texture2D FrameAniTex : register(t0);

cbuffer TransData : register(b0)
{
    TransData TD;
}

VtxOut VS_EmissionMap(VtxIn _In)
{
    if (0 != RO.IsAni)
    {
        SkinningPos(_In.Pos, _In.Weight, _In.Index, FrameAniTex);
    }
    
    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, TD.WVP);
    
    return Out;
}

DeferredOut PS_EmissionMap(VtxOut _In)
{
    DeferredOut Out = (DeferredOut) 0.0f;
    Out.OutColor.xw = 1.0f;
    
    return Out;
}