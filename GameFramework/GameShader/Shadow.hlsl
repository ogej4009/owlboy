#include "LightBase.hlsli"
#include "RenderBase.hlsli"
#include "AnimationBase.hlsli"

struct VtxShadow_In
{
    float4 vPOSITION : POSITION;
    float4 vUV : TEXCOORD;
    float4 vCOLOR : COLOR;
    float4 vNORMAL : NORMAL;
    float4 vBINORMAL : BINORMAL;
    float4 vTANGENT : TANGENT;
    float4 vWEIGHT : BLENDWEIGHT;
    int4 vINDEX : BLENDINDICES;
};

struct VtxShadow_Out
{
    float4 vPos : SV_Position;
    float4 vPorjPos : POSITION;
};

cbuffer RenderOptionData : register(b7)
{
    RenderOption RO;
}

cbuffer TransData : register(b0)
{
    TransData TD;
}

Texture2D FrameAniTex : register(t0);

VtxShadow_Out VS_Shadow(VtxShadow_In _In)
{
    _In.vPOSITION.w = 1.0f;

    if (0 != RO.IsAni)
    {
        SkinningPos(_In.vPOSITION, _In.vWEIGHT, _In.vINDEX, FrameAniTex);
    }

    VtxShadow_Out Out = (VtxShadow_Out) 0.0f;
    Out.vPos = mul(_In.vPOSITION, TD.WVP);
    Out.vPorjPos = Out.vPos;
    return Out;
}

float4 PS_Shadow(VtxShadow_Out _In) : SV_Target
{
    return float4(_In.vPorjPos.z / _In.vPorjPos.w, 0.0, 0.0f, 1.0f);
}
