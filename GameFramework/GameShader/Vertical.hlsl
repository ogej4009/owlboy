// #include "Header.hlsl"
// 쉐이더 컴파일 인터프리터 
// 컴파일의 방식은 이론적으로 개념적으로 정해진 것이 아닌 에디터 회사에서 정한것이다. 고정관념을 갖지 말자 
// 쉐이더는 기본적으로 그냥 코드다. 
// HLSL 확장자는 개념적으로는 큰 의미가 없다. 에디터 편하게 쓰기 위해 최적화된 느낌이라고 생각하자 
// CPP, TXT는 빌드가 가능한 컴퓨터적으로 같은 파일이다. 확장자는 의미가 없다.  그 안의 내용이 유효한 문자인지 논리인지가 중요하다. 

    // POSITION0, 1, 2, 3, ... 이런식으로 시멘틱에 인덱스가 있는데, 이는 layout 에 SemanticIndex의 번호를 의미함
    // (숫자가 없을 경우에는 SemanticIndex 이 0 이란 의미) 

// 버텍스쉐이더 ------전달(_IN, _OUT의 값 그리고 연산)------> 픽셀쉐이더     
// void GAMEDEVICE::SHADERINIT()
// 여기서 


struct VTX2DIMAGE_IN
{
    // 시맨틱 문법 : 내부 맴버변수의 용도를 명시한 정보  

    float4 Pos : SHA_INIT_POSITION;
    float4 Uv : SHA_INIT_TEXCOORD;
    float4 Color : SHA_INIT_COLOR;
};

struct VTX2DIMAGE_OUT
{
    //대소문자 가립니다.
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

// 내가 CPU에게 잡아놓은 값이 쉐이더에 적용되길 원할 때
// 상수버퍼는 선언부터 해야 한다.
// 쉐이더에서 b로 인식되는데 무슨말이냐면?
// 이 데이터는 cpu에서 날아올거다.
// 버텍스 쉐이더 -- 0번슬롯   
// 픽셀 쉐이더   -- 0번슬롯

// 위에서 버텍스 쉐이더에 사용할 상수버퍼의 Register 0번 슬롯을 사용하고 있기 때문에 
// 슬롯을 중복하지 않기 위해 1번 슬롯을 사용한다.(단, 다른 쉐이더간에 슬롯 번호는 중복되도 상관없음)


// 매번 수정된 데이터를 업데이트 해주는 것 
cbuffer SHA_TRANSDATA : register(b0) // <- 0번슬롯 
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
    // 상수버퍼는 외부에서 세팅된 값이다. 
    // 그래서 이미지를 짤라서 화면에 렌더링 할 수 있다. 
    // 랜더러에서 세팅한다. 스프라이트 렌더러에서 세팅한다. 
}

// UV 조절에 사용할 정보
cbuffer CUTDATA : register(b1)
{
    float4 CUT_VECTOR;
}



VTX2DIMAGE_OUT VS2DIMAGEC(VTX2DIMAGE_IN _In)
{
    VTX2DIMAGE_OUT Out = (VTX2DIMAGE_OUT) 0;
    // Out.Pos = mul(_In.Pos, WVP);
    
        // 이걸 한번 곱해줌으로 해서
    // 공간이 몇번 변한건가요? 
    // 인풋레이아웃 // -0.5f 0.5f, 0.0f, 1.0f // 0.5f 0.5f, 0.0f, 1.0f

                    // -0.5f 0.5f, 0.0f, 1.0f // 0.5f 0.5f, 0.0f, 1.0f
    // 로컬스페이스

    //  5.7, 8.8, 6.6, 1 -> 프로젝션 행렬만 곱했다면
    //                      w의 값은?


    Out.Pos = mul(_In.Pos, WVP);
    // Out.Pos = _In.Pos;
    
    Out.Uv = _In.Uv;
    //Out.Pos.x += 0.1f;
    //Out.Pos.y += 0.1f;
    //Out.Pos.z = 0.6f;
    
        // Out.Pos.x /= Out.Pos.w;

    Out.Color = _In.Color;
    

    // (0 * 1 / 21.0f) + 1 / 21.0f,0 , (0 * 1 / 21.0f) + 1 / 21.0f,0
    // (0 * 1 / 21.0f) + 1 / 21.0f,1 , (0 * 1 / 21.0f) + 1 / 21.0f,1 
        // 버텍스 쉐이더는 4번 돈다(정점 4개)
    // float 4개로 스프라이트를 컨트롤 하기위한 변수
    float XSize = CUT_VECTOR.z;
    float YSize = CUT_VECTOR.w;
    float XStart = CUT_VECTOR.x;
    float YStart = CUT_VECTOR.y;
    // 21개니깐 1/21 의 크기로 자르고,
    // 처음 위치를 0,1,2,3,... 으로 정해주면 원하는 이미지만 추출할 수 있음
    Out.Uv.x = Out.Uv.x;

    Out.Uv.y = Out.Uv.y * CUT_VECTOR.x - CUT_VECTOR.y;

    return Out;
}

// 픽셀 쉐이더에 사용할 상수 버퍼(위에서 사용하는 쉐이더가 다르기 때문에 슬롯 번호 중복 가능)
cbuffer SHA_DRAWCOLOR : register(b0) // 매칭이 안된 변수 이름은 상관없다. 
{
    float4 RENDERCOLOR; // 이 안의 변수는 코드와 관련있다. 
}

cbuffer RENDEROPTION : register(b1)
{
    int4 OPTION;
}
// 텍스처를 사용하겠다고 한것. png
Texture2D Tex : register(t0);
SamplerState Smp : register(s0);


// 인풋레이아웃 // -0.5f 0.5f, 0.0f, 1.0f // 0.5f 0.5f, 0.0f, 1.0f

                // -0.5f 0.5f, 0.0f, 1.0f // 0.5f 0.5f, 0.0f, 1.0f

// 버텍스쉐이더
// 레스터라이저
// 픽셀쉐이더
// 아웃풋머저
// 모니터


    // 여기서 텍스처를 알아야죠?
    // 여기에서 처리되서 화면에 픽세링 보이는거죠?
    // 클립은 OM단계 전에 OM으로 넘기지 않는다는 것이다. 
    // 넘기지 않으면 깊이버퍼도 안찍는다. 
    // 픽셀로도 찍었는데 안찍음 
    // 빛연산 그림자연산 
    // 픽셀쉐이더에서 하는 일이란 결국 무슨색을 출력할 것인가 정도이다.
float4 PS2DIMAGEC(VTX2DIMAGE_OUT _In) : SV_Target0
{
    float4 ReturnColor = Tex.Sample(Smp, _In.Uv.xy) /*COLOR*/;
    
    // 0을 넣으면 결과물이 달라지나 ? 
    // 흰색 * 레드 = 레드 
    // 색을 변하게 한다. 색을 바꿀 수 있다. 원하는대로 플레이어가 맞으면.. 변색한다. 깜박인다. 
    // 1, 1, 1 * 1, 0, 0 == □, □, □  곱을 통해 내가 원하는 대로 화면에 나오게 연산을 한다. 
    if (OPTION.x == 0)
    {
        ReturnColor.xyz *= RENDERCOLOR.xyz;
        ReturnColor.a *= RENDERCOLOR.a;
    }
    else
    {
        if (ReturnColor.x != 0 || ReturnColor.y != 0 || ReturnColor.z != 0)
        {
            // 넘어오는 값이 1, 1, 1, 1이면 투명값을 확인해서 투명값이 1인지점, 0인지점을 판단 
            ReturnColor.xyz = RENDERCOLOR.xyz;
            ReturnColor.a = RENDERCOLOR.a;
        }
    }
    // ReturnColor.a = RENDERCOLOR.a;
    // _In : 버텍스 연결
    // RENDERCOLOR : 상수버퍼 연결  
    /* 
    상수버퍼에서 넘어온값이 이 색깔이면 컬러를 바꿔준다. 
    */
    //if (RENDERCOLOR.x == 0.0f && RENDERCOLOR.y == 0.0f && RENDERCOLOR.z == 0.0f)
    //{
    //    ReturnColor.a = 0.0f;
    //    return ReturnColor;
    //}


    //if (320.0f < _In.Pos.y)
    //{
    //    return float4(0.0f, 0.0f, 0.0f, 1.0f);
    //}

    //if (RENDERCOLOR.a == 0.0f)
    //{
    //    ReturnColor.a = 0.1f;
    //}


    return ReturnColor;
    
}
