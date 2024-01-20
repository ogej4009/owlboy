
struct VTX2DIMAGE_IN
{
    float4 Pos : SHA_INIT_POSITION;
    float4 Uv : SHA_INIT_TEXCOORD;
    float4 Color : SHA_INIT_COLOR;
};

struct VTX2DIMAGE_OUT
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

cbuffer SHA_TRANSDATA : register(b0) 
{
    matrix POS;
    matrix SCALE;
    matrix ROT;
    matrix REVO;
    matrix PARENT;
    matrix LWORLD;
    matrix WWORLD;
    matrix VIEW;
    matrix PROJ;
    matrix WV;
    matrix VP;
    matrix WVP;
}

// UV 조절에 사용할 정보
cbuffer CUTDATA : register(b1)
{
    float4 CUT_VECTOR;
}

VTX2DIMAGE_OUT VS_TILEMAP(VTX2DIMAGE_IN _In)
{
    VTX2DIMAGE_OUT Out = (VTX2DIMAGE_OUT) 0;
    
    Out.Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    
    float XSize = CUT_VECTOR.z;
    float YSize = CUT_VECTOR.w;
    float XStart = CUT_VECTOR.x;
    float YStart = CUT_VECTOR.y;
    
    Out.Uv.x = (Out.Uv.x * XSize) + XStart;
    Out.Uv.y = (Out.Uv.y * YSize) + YStart;
    
    return Out;
}

cbuffer SHA_DRAWCOLOR : register(b0) 
{
    float4 RENDERCOLOR; 
}

cbuffer RENDEROPTION : register(b1)
{
    int4 OPTION;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_TILEMAP(VTX2DIMAGE_OUT _In) : SV_Target0
{
    float4 ReturnColor = Tex.Sample(Smp, _In.Uv.xy);
    
    if (OPTION.x == 0)
    {
        ReturnColor.xyz *= RENDERCOLOR.xyz;
        ReturnColor.a *= RENDERCOLOR.a;
    }
    else
    {
        if (ReturnColor.x != 0 || ReturnColor.y != 0 || ReturnColor.z != 0)
        {
            ReturnColor.xyz = RENDERCOLOR.xyz;
            ReturnColor.a = RENDERCOLOR.a;
        }
    }
    
    return ReturnColor;
    
}