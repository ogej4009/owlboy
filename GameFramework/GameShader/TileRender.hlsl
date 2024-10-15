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
    TransData TD;
}

cbuffer RenderOptionData : register(b7)
{
    RenderOption RO;
}

cbuffer SprCutData : register(b1)
{
    CutData CD;
}

Texture2D BaseTex : register(t1);
SamplerState BaseSmp : register(s1);

VtxOut VS_TileRender(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    
    Out.Pos = mul(_In.Pos, TD.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    
    if (RO.IsDifTexture.x != 0)
    {   
       float XSize = CD.Data.z;
       float YSize = CD.Data.w;
       float XStart = CD.Data.x;
       float YStart = CD.Data.y;
    
       Out.Uv.x = (Out.Uv.x * XSize) + XStart;
       Out.Uv.y = (Out.Uv.y * YSize) + YStart;
    
       float4 TileColor = BaseTex.SampleLevel(BaseSmp, Out.Uv.xy, 0);
    
       Out.Color = TileColor;
       
    }
    
    return Out;
    
}


struct DeferredOut
{
    float4 DifColor : SV_Target0;
    //float4 PosColor : SV_Target1;
    //float4 NorColor : SV_Target2;
    //float4 DepColor : SV_Target3;
};


Texture2D Tex : register(t1);
SamplerState Smp : register(s1);

DeferredOut PS_TileRender(VtxOut _Out) : SV_Target0
{
    DeferredOut Out = (DeferredOut) 0;
   
    if (RO.IsDifTexture.x == 0) 
    {
        Out.DifColor = Tex.Sample(Smp, _Out.Uv.xy);
    }
    else
    {
        Out.DifColor = _Out.Color;
    }

    return Out;
    
}

