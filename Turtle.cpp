#include "Turtle.h"

CTurtle::CTurtle()
{
}

CTurtle::~CTurtle()
{
}

bool CTurtle::Load()
{
    if (!Texture.Load("Obstacle\\Turtle.png"))return false;

    return true;
}

void CTurtle::Initialize()
{
    pos.x = 2000;
    pos.y = 1000;
    moveSpeed.x = 2.0f;
    showFlg = true;
}

void CTurtle::Update(float wx, float wy)
{
    if (!showFlg)return;
    //移動
    pos.x -= moveSpeed.x;
    //スクリーンから出たらshowFlgをfalse
    if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CTurtle::Render(float wx, float wy)
{
    if (!showFlg)return;
    Texture.Render(pos.x - wx, pos.y - wy);
}

void CTurtle::RenderDebug(float wx, float wy)
{
    if (!showFlg)return;
    CRectangle rect = GetRect();
    CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CTurtle::Release()
{
    Texture.Release();
}
