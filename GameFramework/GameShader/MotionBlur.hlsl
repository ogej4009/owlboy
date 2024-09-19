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

struct  VtxOut
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

struct OutColorData
{
    float4 OutColor : SV_Target7;
};

Texture2D FrameAniTex : register(t0);

cbuffer TransData : register(b0)
{
    TransData TD;
}

cbuffer RenderOptionData : register(b7)
{
    RenderOption RO;
}

VtxOut VS_MotionBlur(VtxIn _In)
{
    _In.Pos.w = 1.0F;
    _In.Normal.w = 0.0f;
    SkinningPos(_In.Pos, _In.Weight, _In.Index, FrameAniTex);
    
    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, TD.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    Out.Color.w = 1.0f;
    return Out;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

OutColorData PS_MotionBlur(VtxOut _In)
{
    OutColorData Out = (OutColorData) 0.0f;

    if (0 != RO.IsDifTexture)
    {
        Out.OutColor = Tex.Sample(Smp, _In.Uv.xy);
    }
    else
    {
        Out.OutColor = RO.BasicColor;
    }
   
    Out.OutColor.w = 1.0f;
    return Out;
}

