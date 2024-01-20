
//  uniform texture _pTex_Distortion
//  디스토션

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

cbuffer CUTDATA : register(b1)
{
    float k;
    float a;
    float f;
    float time;
}

/* 

    position.x += a * sin(k * position.y + f * time);

    여기서 a, k, f는 조정할 수 있는 상수입니다(하드 코딩하거나 상수 버퍼에 넣을 수 있음).

    그러면 수직 위치(position.y)와 현재 시간에 따라 각 정점이 수평으로 이동합니다(position.x 조정).

    화면 공간이 아닌 월드 공간에 왜곡을 적용하려는 경우 WVP 행렬을 곱하기 전에 수행해야 합니다.



    struct constant_buffer {
        DirectX::XMMATRIX  WVP;
        // this value starts in 0 and increases by 1 each frame until 359 degrees
        float time;
    };

    constant_buffer cbuffer;

*/


VTX2DIMAGE_OUT VS2DIMAGED(VTX2DIMAGE_IN _In)
{
    VTX2DIMAGE_OUT Out = (VTX2DIMAGE_OUT) 0;

    Out.Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    
    Out.Pos.x += a * sin(k * Out.Pos.y + f * time);

    return Out;
}

//cbuffer SHA_DRAWCOLOR : register(b0)
//{
//    float4 RENDERCOLOR;
//}
//
//cbuffer RENDEROPTION : register(b1)
//{
//    int4 OPTION;
//}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

/* 
    in_pshader vshader(float4 position : POSITION, float4 color : COLOR)
    {
        in_pshader output;

        output.position = mul(position, WVP);
        output.color = color;

        return output;
    }


    float4 pshader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
    {
        return color;
    }

*/


float4 PS2DIMAGED(VTX2DIMAGE_OUT _In) : SV_Target0
{
    float4 Return = Tex.Sample(Smp, _In.Uv.xy);

    return Return;
    
}


/* 

    position.x += a * sin(k * position.y + f * time);
    
    여기서 a, k, f는 조정할 수 있는 상수입니다(하드 코딩하거나 상수 버퍼에 넣을 수 있음). 
    
    그러면 수직 위치(position.y)와 현재 시간에 따라 각 정점이 수평으로 이동합니다(position.x 조정).
    
    화면 공간이 아닌 월드 공간에 왜곡을 적용하려는 경우 WVP 행렬을 곱하기 전에 수행해야 합니다.
    
    
    
    struct constant_buffer {
        DirectX::XMMATRIX  WVP;
        // this value starts in 0 and increases by 1 each frame until 359 degrees
        float time; 
    };
    
    constant_buffer cbuffer;
    
    
    struct in_pshader
    {
        float4 position : SV_POSITION;
        float4 color : COLOR;
    };
    
    cbuffer constant_buffer
    {
        float4x4 WVP;
        float time;
    };
    
    
    in_pshader vshader(float4 position : POSITION, float4 color : COLOR)
    {
        in_pshader output;
    
        output.position = mul(position, WVP);
        output.color = color;
    
        return output;
    }
    
    
    float4 pshader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
    {
        return color;
    }

*/

// ================================================== > 


/* 
PS_OUTPUT_SINGLE FX_Distortion(VS_OUTPUT_TEX input)
{
        PS_OUTPUT_SINGLE output = (PS_OUTPUT_SINGLE)0;


	float4 vFX_tex = g_EffectTex1.Sample(g_LinearSmp, input.vUV);
	float4	vColor = (float4)0.f;
	float fWeight = vFX_tex.r * 0.5f;

	if (g_iAnimation2DEnable == 0)
	{
		vColor = g_DiffuseTex.Sample(g_LinearSmp, input.vUV + fWeight);
	}
	else
	{
		if (g_iAnim2DType == AT_ATLAS)
			vColor = g_DiffuseTex.Sample(g_LinearSmp, input.vUV + fWeight);
		else
			vColor = g_ArrayTex.Sample(g_LinearSmp,float3(input.vUV + fWeight, g_iAnim2DFrame));
	}

	output.vColor = vColor;
	return output;
}
 

*/