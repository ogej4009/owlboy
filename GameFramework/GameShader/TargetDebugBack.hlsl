

struct VtxIn
{
    float4 Pos : POSITION;
};

struct VtxOut
{
    float4 Pos : SV_Position;
};

cbuffer WVP_Matrix : register(b0)
{
    matrix WVP;
}

VtxOut VS_TargetDebugBack(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, WVP);
    return Out;
}

cbuffer BackColor : register(b8)
{
    float4 Color;
}

float4 PS_TargetDebugBack(VtxOut _In) : SV_Target0
{
    float4 Result;
    Result = Color;
    return Result;
}

