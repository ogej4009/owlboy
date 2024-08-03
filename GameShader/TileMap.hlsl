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
    float4 W_Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

cbuffer TileTransData : register(b0)
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

cbuffer TileRenderOption : register(b7)
{
    RenderOptionBase Option;
}
 
cbuffer CutData : register(b1)
{
    float4 TCutData;
};

VtxOut VS_TileMap(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    
    Out.W_Pos = mul(_In.Pos, WWORLD);
    Out.WVP_Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    
    float XSize = TCutData.z;
    float YSize = TCutData.w;
    float XStart = TCutData.x;
    float YStart = TCutData.y;
    
    Out.Uv.x = (Out.Uv.x * XSize) + XStart;
    Out.Uv.y = (Out.Uv.y * YSize) + YStart;
    
    return Out;
    
}

cbuffer TileColor : register(b0) 
{
    float4 Color; 
}

struct DeferredOut
{
    float4 DifColor : SV_Target0;
    float4 PosColor : SV_Target1;
    float4 NorColor : SV_Target2;
    float4 DepColor : SV_Target3;
};

Texture2D TileTex : register(t0);
SamplerState TileSmp : register(s0);

DeferredOut PS_TileMap(VtxOut _Out) : SV_Target0
{  
    DeferredOut Out = (DeferredOut) 0;

    Out.DifColor = TileTex.Sample(TileSmp, _Out.Uv.xy);

    Out.PosColor.x = 0.5f;
    Out.PosColor.y = 0.5f;
    Out.PosColor.z = 0.5f;

    Out.NorColor.x = 0.5f;
    Out.NorColor.y = 0.5f;
    Out.NorColor.z = 0.5f;

    Out.DepColor.x = 0.5f;
    Out.DepColor.y = 0.5f;
    Out.DepColor.z = 0.5f;
    
    // 1, 1, 1 * 1, 0, 0 == 1, 1, 1
    Out.DifColor.xyz *= Color.xyz;
    
    if (0 != Out.DifColor.a)
    {
        Out.DifColor.a = Color.a;
    }

    return Out;
   
    /* 
    DeferredOut Out = (DeferredOut) 0;
    Out.DifColor = BaseTex.Sample(Smp, _In.Uv.xy);
    Out.NorColor = _In.ViewNormal;
    Out.PosColor = _In.ViewPos;
    Out.DepColor.x = _In.ViewPos.z;
    Out.DepColor.w = Out.PosColor.w = Out.NorColor.w = 1.0f;
    return Out;
    */
    
}
