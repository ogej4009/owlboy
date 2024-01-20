
// 유령을 만들려했으나 실패하였다

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
    float2 Time;
}


VTX2DIMAGE_OUT VS2DIMAGEG(VTX2DIMAGE_IN _In)
{
    VTX2DIMAGE_OUT Out = (VTX2DIMAGE_OUT) 0;

    Out.Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;

    return Out;
}


Texture2D Tex : register(t0);
Texture2D Tex1 : register(t1);

SamplerState Smp : register(s0);



float4 PS2DIMAGEG(VTX2DIMAGE_OUT _In) : SV_Target0
{
    
    float4 Return = Tex.Sample(Smp, _In.Uv.xy + float2(0, -Time.y));
    float4 Return1 = Tex1.Sample(Smp, _In.Uv.xy + Return.r * 0.25f);
    return Return1;
    
}


/* 
half4 frag(Varyings IN) : SV_Target
  {
  half4 color2 = SAMPLE_TEXTURE2D(_BaseMap2, sampler_BaseMap2, TRANSFORM_TEX(IN.uv, _BaseMap2));
  //두 번째 텍스쳐의 r 채널을 UV에 더해서 UV를 구겨줍니다.
  half4 color = SAMPLE_TEXTURE2D(_BaseMap, sampler_BaseMap, TRANSFORM_TEX(IN.uv, _BaseMap) + color2.r * 0.25) ;

  return color;
  }


  VS2DIMAGEG



  half4 frag(Varyings IN) : SV_Target
  {
  //노이즈를 흘러가게 해 줍니다.
  half4 color2 = SAMPLE_TEXTURE2D(_BaseMap2, sampler_BaseMap2, TRANSFORM_TEX(IN.uv, _BaseMap2) + float2(0, -_Time.y));
  //두 번째 텍스쳐의 r 채널을 UV에 더해서 UV를 구겨줍니다.
  half4 color = SAMPLE_TEXTURE2D(_BaseMap, sampler_BaseMap, TRANSFORM_TEX(IN.uv, _BaseMap) + color2.r * 0.25) ;

  return color;
  }







  1. half4 color = SAMPLE_TEXTURE2D(_BaseMap, sampler_BaseMap, TRANSFORM_TEX(IN.uv, _BaseMap) + (color2.r - 0.5) * 0.25);
이런 식으로 노이즈의 값에 -0.5을 해서 범위를 (-0.5 ~ 0.5)로 변환시켰습니다. ( 전 블로그글의 답을 보고 해봤습니다. )
2. 노이즈 값을 가져올때 노이즈 텍스쳐의 값을 이용할려고 하는 거기 때문에 텍스쳐 설정 값에 sRGB 체크를 꺼야 합니다.

좋은 강의 감사합니다.





저는 saturate 를 이용해서 변환된 uv 값의 범위를 0~1로 제한해보았습니다.

half4 color = SAMPLE_TEXTURE2D(_BaseMap, sampler_BaseMap, saturate(TRANSFORM_TEX(IN.uv, _BaseMap) + color2.r * 0.25));



*/