#include "Turtle.h"

CTurtle::CTurtle()
{
}

CTurtle::~CTurtle()
{
}

bool CTurtle::Load()
{
    if (!Texture.Load("Obstacle\\Turtleanim.png"))return false;

    return true;
}

void CTurtle::Initialize()
{
    //pos.x = 2000;
    //pos.y = 1000;
    moveSpeed.x = 2.0f;
    showFlg = false;

    SpriteAnimationCreate anim = {
        "泳ぐ",
        0,0,
        166,166,
        TRUE,{{7,0,0},{7,1,0},{7,2,0},{7,3,0},{7,4,0},{7,5,0},
              {7,0,1},{7,1,1},{7,2,1},{7,3,1},{7,4,1},{7,5,1},
              {7,0,2},{7,1,2},{7,2,2},{7,3,2},{7,4,2},{7,5,2},
              {7,0,3},{7,1,3},{7,2,3},{7,3,3},{7,4,3},{7,5,3},
              {7,0,4},{7,1,4},{7,2,4},{7,3,4},{7,4,4},{7,5,4}}

    };
    motion.Create(anim);
}


void CTurtle::Update(float wx, float wy)
{
    if (!showFlg)return;
    //移動
    pos.x -= moveSpeed.x;
    //スクリーンから出たらshowFlgをfalse
    if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
    motion.AddTimer(CUtilities::GetFrameSecond());
}

void CTurtle::Render(float wx, float wy)
{
    if (!showFlg)return;
    Texture.RenderScale(pos.x - wx, pos.y - wy,3.0f,motion.GetSrcRect());

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
    motion.Release();
}
