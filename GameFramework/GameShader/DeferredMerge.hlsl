

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

VtxOut VS_DeferredMerge(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    Out.Pos = _In.Pos;
    Out.Uv = _In.Uv;
    return Out;
}

struct DeferredOut
{
    float4 DeferredColor : SV_Target0;
};

Texture2D DifColor : register(t0);
Texture2D LightColor : register(t1);
SamplerState Smp : register(s0);

DeferredOut PS_DeferredMerge(VtxOut _In)
{
    float4 DifOut = DifColor.Sample(Smp, _In.Uv.xy);

    if (0 >= DifOut.a)
    {
        clip(-1);
    }

    float4 DifLightOut = LightColor.Sample(Smp, _In.Uv.xy);

    DeferredOut Out = (DeferredOut) 0;
    Out.DeferredColor = DifOut;
    Out.DeferredColor.xyz *= DifLightOut.xyz;

    if (1 <= Out.DeferredColor.a)
    {
        Out.DeferredColor.a = 1.0f;
    }
    
    return Out;
}
