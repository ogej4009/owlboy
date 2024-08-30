struct Vtx3D_In
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
};

struct Vtx3D_Out
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
};

Vtx3D_Out VS_OutLineDraw(Vtx3D_In _In)
{
    Vtx3D_Out Out = (Vtx3D_In) 0;
    Out.Pos = _In.Pos;
    Out.Uv = _In.Uv;
    return Out;
}

cbuffer Distance : register(b1)
{
    float4 DisArr[4];
}

cbuffer OUTLINEDATA : register(b0)
{
    float4 PixelUv[4];
    float4 LineColor;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_OutLineDraw(Vtx3D_Out _In) : SV_Target0
{
    float limit = DisArr[0];
    float4 TexColor;
    TexColor = Tex.Sample(Smp, _In.Uv.xy);
	
    if (0 != TexColor.x)
    {
        clip(-1);
    }

    TexColor = Tex.Sample(Smp, (_In.Uv.xy + PixelUv[0].xy / limit));
    
    if (0 != TexColor.x)
    {
        TexColor = LineColor;
        return TexColor;
    }
    
    TexColor = Tex.Sample(Smp, (_In.Uv.xy + PixelUv[1].xy / limit));
    
    if (0 != TexColor.x)
    {
        TexColor = LineColor;
        return TexColor;
    }
    
    TexColor = Tex.Sample(Smp, (_In.Uv.xy + PixelUv[2].xy / limit));
    
    if (0 != TexColor.x)
    {
        TexColor = LineColor;
        return TexColor;
    }
    
    TexColor = Tex.Sample(Smp, (_In.Uv.xy + PixelUv[3].xy / limit));
    
    if (0 != TexColor.x)
    {
        TexColor = LineColor;
        return TexColor;
    }

    clip(-1);

    TexColor = LineColor;
    return TexColor;
}
