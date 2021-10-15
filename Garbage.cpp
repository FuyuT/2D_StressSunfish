#include "Garbage.h"

CGarbage::CGarbage()
{
}

CGarbage::~CGarbage()
{
}

bool CGarbage::Load()
{
	if (!Texture.Load("Garbage1.png"))return false;

	return true;
}

void CGarbage::Initialize()
{
	pos.x = 1000;
	pos.y = 500;
	moveSpeed.x = 2.0f;
	showFlg = true;
}

void CGarbage::Update(float wx, float wy)
{
	if (!showFlg)return;
	//移動
	pos.x -= moveSpeed.x;
	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CGarbage::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.Render(pos.x - wx, pos.y - wy);
}

void CGarbage::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CGarbage::Release()
{
	Texture.Release();
}
