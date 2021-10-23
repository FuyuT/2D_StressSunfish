#include "Flow.h"
CFlow::CFlow()
{
}

CFlow::~CFlow()
{
}

bool CFlow::Load()
{
    if (!Texture.Load("Obstacle\\waterFlow.png"))return false;

    return true;
}

void CFlow::Initialize()
{
    pos.x = 2500;
    pos.y = 1000;
    moveSpeed.x = 0.0f;
    showFlg = true;
}

void CFlow::Update(float wx, float wy)
{
    if (!showFlg)return;
    //移動
    pos.x -= moveSpeed.x;
    //スクリーンから出たらshowFlgをfalse
    if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CFlow::Render(float wx, float wy)
{
    if (!showFlg)return;
    Texture.Render(pos.x - wx, pos.y - wy);
}

void CFlow::RenderDebug(float wx, float wy)
{
    if (!showFlg)return;
    CRectangle rect = GetRect();
    CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CFlow::Release()
{
    Texture.Release();
}