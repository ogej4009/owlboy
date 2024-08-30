struct Vtx3D_In
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
    float4 Normal : NORMAL;
};

struct Vtx3D_Out
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
    float4 Normal : NORMAL;
};

Vtx3D_Out VS_MotionBlurDraw(Vtx3D_In In)
{
    Vtx3D_Out Out = (Vtx3D_In) 0;
    Out.Pos = In.Pos;
    Out.Uv = In.Uv;
    Out.Color = In.Color;
    Out.Normal = In.Normal;
    return Out;
}

cbuffer Motion_Blur_Data : register(b1)
{
    matrix Prev_WVP;
    matrix WVP2;
    float4 Prev_Pos;
    float4 Pos;
    float4 null;
    float4 null1;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_MotionBlurDraw(Vtx3D_Out Out) : SV_Target0
{
    int Blur = 30;
    float4 CurP = mul(Pos, WVP2);
    float4 PrevP = mul(Prev_Pos, Prev_WVP);
    CurP.xyz /= CurP.w;
    PrevP.xyz /= PrevP.w;
    float4 Velocity = (CurP - PrevP);
    Velocity.x *= 0.5f;
    Velocity.y *= -0.5f;
    float4 RealColor;
    RealColor = Tex.Sample(Smp, Out.Uv.xy);
    
    if (1 == RealColor.x && 0 == RealColor.y && 0 == RealColor.z)
    {
        clip(-1);
    }

    if (0 == RealColor.x && 0 == RealColor.y && 0 == RealColor.z)
    {
        clip(-1);
    }

    if (0 == Velocity.x && 0 == Velocity.y && 0 == Velocity.z)
    {
        clip(-1);
    }

    int cnt = 1;
    float4 BColor;

    for (int i = cnt; i < Blur; i++)
    {

        BColor = Tex.Sample(Smp, Out.Uv.xy + Velocity.xy * (float) i * 10);

        if (Velocity.a < BColor.a + 0.04f)
        {
            cnt++;
            RealColor += BColor / (Blur * 2);
        }
    }
	
    RealColor.xyz -= 0.08f;
    RealColor.w = 1.0f;

    if (1 == RealColor.x)
    {
        clip(-1);
    }
	
    return RealColor;
}