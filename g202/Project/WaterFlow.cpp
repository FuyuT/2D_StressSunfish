#include "WaterFlow.h"
CWaterFlow::CWaterFlow()
{
}

CWaterFlow::~CWaterFlow()
{
}

bool CWaterFlow::Load()
{
    if (!Texture.Load("Obstacle\\Ocean_current.png"))return false;


    return true;
}

void CWaterFlow::Initialize()
{
    //pos.x = 2500;
    //pos.y = 1000;
    moveSpeed.x = 0.0f;
    showFlg = true;

    SpriteAnimationCreate anim = {
    "流れ",
    0,0,
    677,322,
    TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},
          {4,0,1},{4,1,1},{4,2,1},{4,3,1},
          {4,0,2},{4,1,2},{4,2,2},{4,3,2},
          {4,0,3},{4,1,3},{4,2,3},{4,3,3},
          {4,0,4},{4,1,4},{4,2,4},{4,3,4},
          {4,0,5},{4,1,5},{4,2,5},{4,3,5}}
    };
    motion.Create(anim);

}

void CWaterFlow::Update(float wx, float wy)
{
    if (!showFlg)return;
    //移動
    pos.x -= moveSpeed.x;
    //スクリーンから出たらshowFlgをfalse
    if (pos.x + Texture.GetWidth() <= wx)showFlg = false;

    motion.AddTimer(CUtilities::GetFrameSecond());
}

void CWaterFlow::Render(float wx, float wy)
{
    if (!showFlg)return;
    Texture.RenderScale(pos.x - wx, pos.y - wy,0.8f,motion.GetSrcRect());
}

void CWaterFlow::RenderDebug(float wx, float wy)
{
    if (!showFlg)return;
    CRectangle rect = GetRect();
    CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CWaterFlow::Release()
{
    Texture.Release();
    motion.Release();
}