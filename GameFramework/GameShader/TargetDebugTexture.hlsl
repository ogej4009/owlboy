

struct VtxIn
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
};

struct VtxOut
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
};

cbuffer WVP_Matrix : register(b0)
{
    matrix WVP;
}

VtxOut VS_TargetDebug(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    return Out;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_TargetDebug(VtxOut _In) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _In.Uv.xy);
    return Color;
}

