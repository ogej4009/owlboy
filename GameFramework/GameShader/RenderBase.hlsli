
struct TransData
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
};

struct RenderOption
{
    int IsDifTexture;
    int IsNormalTexture;
    int IsShadow;
    int IsAni;
    int IsDummy0;
    int IsDummy1;
    int IsDummy2;
    int IsDummy3;
    float4 BasicColor;
};

struct CutData
{
    float4 Data;
};