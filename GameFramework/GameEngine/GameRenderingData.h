#pragma once
#include <GameMath.h>

struct LightData
{
    float4 DifColor;
    float4 SpcColor;
    float4 AmbColor;
    float4 LightPower;
    float4 SpecPow;
    float4 LightDir;
    float4 LightDirInv; // 이게 L빛의 역방향 
    float4 LightPos; // 포인트 라이트
    float4 LightRange;
    float4 ShadowOption;
    float4 CamPos; // 이게 L빛의 역방향
    float4 OnOff; // 이게 L빛의 역방향
    float4 m_ShadowRange; // 그림자를 볼수있는 범위 
    CMatrix m_View;
    CMatrix m_Proj;
    CMatrix m_ViewProj;
    CMatrix m_CamViewInverse;

    LightData()
        : SpecPow(10000.0f, 0.0f, 0.0f, 0.0f) // 30.0f, 0.0f, 0.0f, 0.0f
        , LightPower(1.0f, 1.0f, 1.0f, 1.0f)
    {
    }

};

struct ObjectLightData
{
    int LightCount[4];
    LightData ArrLightData[128];
};

struct DebugOption
{

    bool IsTexture0;
    bool IsTexture1;
    bool IsTexture2;
    bool IsTexture3;

public:
    float Dumy1;
    float Dumy2;
    float Dumy3;
    float4 DebugDrawColor;

public:
    DebugOption()
    {
        memset(this, 0, sizeof(DebugOption));
    }
};
