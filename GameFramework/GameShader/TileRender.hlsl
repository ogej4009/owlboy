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
    //float4 VIEWPOS : POSITION;
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
};





VtxOut VS_TileRender(VtxIn _In)
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
        

        
        Out.Color = _In.Color; //TileColor;

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


Texture2D BaseTex : register(t0);
SamplerState BaseSmp : register(s0);


DeferredOut PS_TileRender(VtxOut _Out) : SV_Target0
{
    DeferredOut Out = (DeferredOut) 0;
   
       
    //if (0.0f >= Out.DifColor.a)
    //{
    //    clip(-1.0f);
    //}
    Out.DifColor = BaseTex.Sample(BaseSmp, _Out.Uv.xy);
    //if (RO.IsDifTexture.x == 0) // true false
    //{

    //}
    //else
    //{
    //    Out.DifColor = _Out.Color;
    //}
    

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





//float4 Pos : POSITION;
//float4 Uv : TEXCOORD;
//float4 Color : COLOR;
//float4 Normal : NORMAL;
//float4 BiNormal : BINORMAL;
//float4 Tangent : TANGENT;
//float4 Weight : BLENDWEIGHT;
//int4 Index : BLENDINDICES;