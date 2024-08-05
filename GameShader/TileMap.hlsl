#include "RenderBase.hlsli"

struct VtxIn
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

struct VtxOut
{
    float4 WVP_Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
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


cbuffer SrcTexIdx : register(b2)
{
    float4 CalSrcTexUv;
};


VtxOut VS_TileMap(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    
  //  Out.W_Pos = mul(_In.Pos, WWORLD);
    Out.WVP_Pos = mul(_In.Pos, WVP);
    Out.Uv = CalSrcTexUv;
    Out.Color = _In.Color;    

    return Out;
    
}


struct DeferredOut
{
    float4 DifColor : SV_Target0;
    float4 PosColor : SV_Target1;
    float4 NorColor : SV_Target2;
    float4 DepColor : SV_Target3;
};


Texture2D SrcTex : register(t0);
SamplerState SrcSmp : register(s0);

DeferredOut PS_TileMap(VtxOut _Out) : SV_Target0
{  
    DeferredOut Out = (DeferredOut) 0;

    Out.DifColor = _Out.Color;
    Out.DifColor = SrcTex.Sample(SrcSmp, _Out.Uv.xy);
    Out.PosColor.x = 0.5f;
    Out.PosColor.y = 0.5f;
    Out.PosColor.z = 0.5f;

    Out.NorColor.x = 0.5f;
    Out.NorColor.y = 0.5f;
    Out.NorColor.z = 0.5f;

    Out.DepColor.x = 0.5f;
    Out.DepColor.y = 0.5f;
    Out.DepColor.z = 0.5f;
    
    return Out;
    
}
