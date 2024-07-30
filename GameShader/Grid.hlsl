struct VtxGrid_In
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

struct VtxGrid_Out
{
    float4 Pos : SV_Position;
    float4 WPos : POSITION; 
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

cbuffer TransData : register(b0)
{
    matrix POS;
    matrix SCALE;
    matrix ROT;
    matrix REVOL;
    matrix PARENT;
    matrix LWORLD;
    matrix WWORLD;
    matrix VIEW;
    matrix PROJ;
    matrix WV;
    matrix VP;
    matrix WVP;
}

cbuffer GridTransData : register(b0)
{
    float4 GRID_POS;
    float GRID_DIVIDE;
    float GRID_AREA;
    float GRID_MIN_ALPHA;
    float GRID_LINE_THICKNESS;
}

VtxGrid_Out VS_Grid(VtxGrid_In _In)
{
    VtxGrid_Out Out = (VtxGrid_Out) 0;
    Out.Pos = mul(_In.Pos, WVP);
    Out.WPos = mul(_In.Pos, WWORLD);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    return Out;
}

float4 PS_Grid(VtxGrid_Out _In) : SV_Target0
{
    float Color = _In.Color;
    float4 Pos = _In.WPos;

    Pos.y = 0.0f;

    float Len = length(Pos - GRID_POS);

    Color.r = GRID_AREA / Len;
   
    if (0.05f > Color.r)
    {
        clip(-1);
    }

    float ModX = _In.WPos.x % GRID_DIVIDE;
    float ModZ = _In.WPos.z % GRID_DIVIDE;

    ModX = abs(ModX);
    ModZ = abs(ModZ);

    if (GRID_LINE_THICKNESS > ModX || GRID_DIVIDE - GRID_LINE_THICKNESS < ModX)
    {
        return Color;
    }
    
    if (GRID_LINE_THICKNESS > ModZ || GRID_DIVIDE - GRID_LINE_THICKNESS < ModZ)
    {
        return Color;
    }

    clip(-1);
    return _In.Color;
}
