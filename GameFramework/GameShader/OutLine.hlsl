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

struct OutColorData
{
    float4 OutColor : SV_Target7;
};

Texture2D FrameAniTex : register(t0);

cbuffer TransData : register(b0)
{
    TransData TD;
}

VtxOut VS_OutLine(VtxIn _In)
{
    SkinningPos(_In.Pos, _In.Weight, _In.Index, FrameAniTex);
    
    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, TD.WVP);
    return Out;
}

OutColorData PS_OutLine(VtxOut _In)
{
    OutColorData Out = (OutColorData) 0.0f;
    Out.OutColor.xw = 1.0f;
    return Out;
}
