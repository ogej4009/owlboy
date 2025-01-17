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
};

VtxOut VS_Fog(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    Out.Pos = _In.Pos;
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    return Out;
}

cbuffer CamPos : register(b4)
{
    float4 CPos;
}

Texture2D DTex : register(t0);
Texture2D PTex : register(t1);
SamplerState Smp : register(s0);


float4 PS_Fog(VtxOut _In) : SV_Target0
{
    float4 DIFCOLOR;
    float4 POSCOLOR;
    float4 FOGCOLOR;
    float4 FINALCOLOR;

    DIFCOLOR = DTex.Sample(Smp, _In.Uv.xy);
    POSCOLOR = PTex.Sample(Smp, _In.Uv.xy);
    FOGCOLOR = float4(1.0f, 1.0f, 1.0f, 1.0f);

    float Len = CPos.z - POSCOLOR.z;
    float Ratio = Len / 100.0f;

    if (1 <= Ratio)
    {
        Ratio = 1.0f;
    }
    
    return DIFCOLOR * Ratio * FOGCOLOR;

}
