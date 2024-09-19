#include "LightBase.hlsli"
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
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
    float4 ViewPos : POSITION;
    float4 ViewNormal : NORMAL;
};

cbuffer TransData : register(b0)
{
    TransData MatrixData;
}

cbuffer RenderOptionData : register(b7)
{
    RenderOption RO;
}

Texture2D FrameAniTex : register(t0);

VtxOut VS_Deferred(VtxIn _In)
{
    _In.Pos.w = 1.0F;
    _In.Normal.w = 0.0f;
    
    if (0 != RO.IsAni)
    {
        SkinningTex(_In.Pos, _In.Normal, _In.Weight, _In.Index, FrameAniTex);
    }

    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, MatrixData.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    _In.Pos.w = 1.0f;
    Out.ViewPos = mul(_In.Pos, MatrixData.WV);
    Out.ViewNormal = normalize(mul(_In.Normal, MatrixData.WV));
    _In.Normal.w = 0.0f;
    return Out;
}

struct DeferredOut
{
    float4 DifColor : SV_Target0;
    float4 PosColor : SV_Target1;
    float4 NorColor : SV_Target2;
    float4 DepColor : SV_Target3;
};

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

DeferredOut PS_Deferred(VtxOut _In)
{
    DeferredOut Out = (DeferredOut) 0;

    if (0 != RO.IsDifTexture)
    {
        Out.DifColor = Tex.Sample(Smp, _In.Uv.xy);
    }
    else
    {
        Out.DifColor = RO.BasicColor;
    }

    Out.NorColor = _In.ViewNormal;
    Out.PosColor = _In.ViewPos;
    Out.DepColor.x = _In.ViewPos.z;
    Out.DifColor.w = 1.0f;
    Out.DepColor.w = Out.PosColor.w = Out.NorColor.w = 1.0f;
    return Out;
}

