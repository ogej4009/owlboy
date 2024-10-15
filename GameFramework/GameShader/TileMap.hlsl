#include "RenderBase.hlsli"


struct VtxIn
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

struct VtxOut
{
    //float4 VIEWPOS : POSITION;
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

cbuffer CutData : register(b1)
{
    CutData CD;
}

///////////////////////// ¼öÁ¤ 

Texture2D SrcTex : register(t0);
SamplerState SrcSmp : register(s0);

VtxOut VS_TileMap(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;    
    Out.Pos = mul(_In.Pos, TD.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    //Out.VIEWPOS = mul(_In.Pos, WV);
    
    if (RO.IsDifTexture.x != 0)// true false
    {
        float XSize = CD.Data.z;
        float YSize = CD.Data.w;
        float XStart = CD.Data.x;
        float YStart = CD.Data.y;
        
        Out.Uv.x = (Out.Uv.x * XSize) + XStart;
        Out.Uv.y = (Out.Uv.y * YSize) + YStart;
        
        float4 TileColor = SrcTex.SampleLevel(SrcSmp, Out.Uv.xy, 0);
        
        Out.Color = TileColor;

    }
     
    return Out;
    
    //Out.Uv.x = (Out.Uv.x * XSize) + XStart;
    //Out.Uv.y = (Out.Uv.y * YSize) + YStart;
}


struct DeferredOut
{
    float4 DifColor : SV_Target0;
    //float4 PosColor : SV_Target1;
    //float4 NorColor : SV_Target2;
    //float4 DepColor : SV_Target3;
};

Texture2D ErrorTile : register(t1);
SamplerState Smp : register(s1);

DeferredOut PS_TileMap(VtxOut _Out) : SV_Target0
{  
    DeferredOut Out = (DeferredOut) 0;
   
    if (RO.IsDifTexture.x == 0) // true false
    {
         Out.DifColor = ErrorTile.Sample(Smp, _Out.Uv.xy);
    }
    else
    {
         Out.DifColor = _Out.Color;
    }

    //Out.PosColor.x = 0.5f;
    //Out.PosColor.y = 0.5f;
    //Out.PosColor.z = 0.5f;

    //Out.NorColor.x = 0.5f;
    //Out.NorColor.y = 0.5f;
    //Out.NorColor.z = 0.5f;

    //Out.DepColor.x = 0.5f;
    //Out.DepColor.y = 0.5f;
    //Out.DepColor.z = 0.5f;
    
    return Out;
    
}

