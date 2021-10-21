#include "Garbage.h"

CGarbage::CGarbage()
{
}

CGarbage::~CGarbage()
{
}

bool CGarbage::Load()
{
	if (!Texture.Load("Obstacle\\Garbage1.png"))return false;

	return true;
}

void CGarbage::Initialize()
{
	initPos.y = 1700;
	pos.x = 2000;
	pos.y = 1700;
	moveSpeed.x = 1.0f;
	moveSpeed.y = 2.0f;
	showFlg = true;
	turnFlg = false;
}

void CGarbage::Update(float wx, float wy)
{
	if (!showFlg)return;
	//移動
	pos.x -= moveSpeed.x;

	if (initPos.y - 200 < pos.y && !turnFlg)
	{
		pos.y -= moveSpeed.y;
		if (initPos.y - 200 >= pos.y)
		{
			turnFlg = true;
		}
	}

	if (initPos.y + 200 > pos.y && turnFlg)
	{
		pos.y += moveSpeed.y;
		if (initPos.y + 200 <= pos.y)
		{
			turnFlg = false;
		}
	}

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
