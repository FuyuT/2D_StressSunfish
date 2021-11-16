#include "FoodCrab.h"

CFoodCrab::CFoodCrab()
{
}

CFoodCrab::~CFoodCrab()
{
}

bool CFoodCrab::Load()
{
	if (!Texture.Load("Obstacle\\Crab.png"))return false;

	return true;
}

void CFoodCrab::Initialize()
{
	//pos.x = 1000;
	//pos.y = 1500;
	//showFlg = true;
}

void CFoodCrab::Update(float wx, float wy)
{
	if (!showFlg)return;
	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CFoodCrab::Render(float wx, float wy)
{
	if (!showFlg)return;
	for (int i = 0; i <= 30; i++) {
		Texture.RenderRotate(pos.x - wx, pos.y - wy, MOF_ToRadian(i));
	}
}

void CFoodCrab::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CFoodCrab::Release()
{
	Texture.Release();
}
