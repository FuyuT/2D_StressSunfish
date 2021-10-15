#include "FoodShrimp.h"

CFoodShrimp::CFoodShrimp()
{
}

CFoodShrimp::~CFoodShrimp()
{
}

bool CFoodShrimp::Load()
{
	if (!Texture.Load("Shrimp.png"))return false;

	return true;
}

void CFoodShrimp::Initialize()
{
	pos.x = 1000;
	pos.y = 1000;
	moveSpeed.x = 2.0f;
	showFlg = true;
}

void CFoodShrimp::Update(float wx, float wy)
{
	if (!showFlg)return;
	//移動
	pos.x -= moveSpeed.x;
	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CFoodShrimp::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.Render(pos.x - wx, pos.y - wy);
}

void CFoodShrimp::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CFoodShrimp::Release()
{
	Texture.Release();
}
