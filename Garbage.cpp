#include "Garbage.h"
CGarbage::CGarbage()
{
}

CGarbage::~CGarbage()
{
}

bool CGarbage::Load()
{
	if (!garbageShoes.Load("Obstacle\\Garbage1.png"))return false;
	if (!garbageTire.Load("Obstacle\\Garbage2.png"))return false;
	if (!garbageBag.Load("Obstacle\\Garbage3.png"))return false;

	return true;
}

void CGarbage::Initialize()
{
	initPos.y = 1700;
	pos.x = 2000;
	pos.y = 1700;
	moveSpeed.x = 3.0f;
	moveSpeed.y = MAX_MOVE_SPEED;
	showFlg = true;
	moveUpFlg = true;
	garbageNo = 2;
}

void CGarbage::Update(float wx, float wy)
{
	if (!showFlg)return;
	//移動
	//idousokudo tyousei
	if (moveSpeed.y > MAX_MOVE_SPEED)
	{
		moveSpeed.y = MAX_MOVE_SPEED;
		moveUpFlg = false;
	}
	else if (moveSpeed.y < -MAX_MOVE_SPEED)
	{
		moveSpeed.y = -MAX_MOVE_SPEED;
		moveUpFlg = true;
	}

	if (moveUpFlg == true) {
		moveSpeed.y += DECELERATE_SPEED;
	}
	else
	{
		moveSpeed.y -= DECELERATE_SPEED;
	}


	//zissainiidou
	pos.x -= moveSpeed.x;
	pos.y -= moveSpeed.y;

	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CGarbage::Render(float wx, float wy)
{
	if (!showFlg)return;
	switch (garbageNo)
	{
	case GarbageShoes:
		garbageShoes.Render(pos.x - wx, pos.y - wy);
		break;
	case GarbageTire:
		garbageTire.Render(pos.x - wx, pos.y - wy);
		break;
	case GarbageBag:
		garbageBag.Render(pos.x - wx, pos.y - wy);
		break;
	default:
		break;
	}
}

void CGarbage::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CGarbage::Release()
{
	garbageShoes.Release();
	garbageTire.Release();
	garbageBag.Release();
}
