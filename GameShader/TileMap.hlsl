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

cbuffer SrcCutData : register(b1)
{
    float4 fCutData;
};

Texture2D SrcTex : register(t0);
SamplerState SrcSmp : register(s0);


VtxOut VS_TileMap(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;    
    Out.Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    // Out.Color = _In.Color;
    
    float XSize = fCutData.z;
    float YSize = fCutData.w;
    float XStart = fCutData.x;
    float YStart = fCutData.y;
        
    Out.Uv.x = (Out.Uv.x * XSize) + XStart;
    Out.Uv.y = (Out.Uv.y * YSize) + YStart;
    
    Out.Color = SrcTex.SampleLevel(SrcSmp, _In.Uv.xy, 0);


    return Out;
    
    //Out.Uv.x = (Out.Uv.x * XSize) + XStart;
    //Out.Uv.y = (Out.Uv.y * YSize) + YStart;
}


struct DeferredOut
{
    float4 DifColor : SV_Target0;
    float4 PosColor : SV_Target1;
    float4 NorColor : SV_Target2;
    float4 DepColor : SV_Target3;
};


DeferredOut PS_TileMap(VtxOut _Out) : SV_Target0
{  
    DeferredOut Out = (DeferredOut) 0;

    Out.DifColor = _Out.Color;
       
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
