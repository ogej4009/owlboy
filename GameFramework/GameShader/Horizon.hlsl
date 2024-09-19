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

cbuffer CutData : register(b1)
{
    CutData CD;
};

VtxOut VS_Horizon(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    
    Out.Pos = mul(_In.Pos, TD.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    
    float XSize = CD.Data.z;
    float YSize = CD.Data.w;
    float XStart = CD.Data.x;
    float YStart = CD.Data.y;
    
    Out.Uv.y = Out.Uv.y;
    Out.Uv.x = Out.Uv.x * CD.Data.y - CD.Data.x;
    
    return Out;
}

cbuffer DrawColor : register(b0) 
{
    float4 Color; 
}

cbuffer RenderOption : register(b1)
{
    int4 Option;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_Horizon(VtxOut _In) : SV_Target0
{
    float4 ReturnColor = Tex.Sample(Smp, _In.Uv.xy);
    
    if (Option.x == 0)
    {
        ReturnColor.xyz *= Color.xyz;
        ReturnColor.a *= Color.a;
    }
    else
    {
        if (ReturnColor.x != 0 || ReturnColor.y != 0 || ReturnColor.z != 0)
        {
            
            ReturnColor.xyz = Color.xyz;
            ReturnColor.a = Color.a;
        }
    }
    
    return ReturnColor;
    
}
