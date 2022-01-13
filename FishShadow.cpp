#include "FishShadow.h"

CFishShadow::CFishShadow()
{
}

CFishShadow::~CFishShadow()
{
}

bool CFishShadow::Load()
{
	if (!SardineShadow.Load("BackGround\\iwasi kage.png"))return false;
	if (!SwordFishShadow.Load("BackGround\\カジキ 影.png"))return false;
	if (!TunaShadow.Load("BackGround\\マグロ 影.png"))return false;
	return false;
}

void CFishShadow::Initialize()
{
	initPos.y = 1700;
	moveSpeed.x = 3.0;
	moveSpeed.y = MAX_MOVE_SPEED;
	showFlg = false;
	fishShadowNo = FISHSHADOW_NOT_SHOW;
}

void CFishShadow::Update(float wx, float wy)
{
	if (!showFlg)return;
	//移動調整
	if (moveSpeed.y > MAX_MOVE_SPEED) {
		moveSpeed.y = MAX_MOVE_SPEED;
	}
	else {
		moveSpeed.y -= MAX_MOVE_SPEED;
	}

	//移動
	pos.y -= moveSpeed.y;

	//スクリーンから出たらshowFlgをfalse
	if (pos.x + SardineShadow.GetWidth() <= wx)showFlg = false;
}

void CFishShadow::Render(float wx, float wy)
{
	if (!showFlg)return;
	switch (fishShadowNo)
	{
	case SARDINESHADOW:
		SardineShadow.Render(pos.x - wx, pos.y - wy);
		break;
	case SWORDFISHSHADOW:
		SwordFishShadow.Render(pos.x - wx, pos.y - wy);
		break;
	case TUNASHADOW:
		TunaShadow.Render(pos.x - wx, pos.y - wy);
		break;
	default:
		break;
	}
}

void CFishShadow::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
}

void CFishShadow::Release()
{
	SardineShadow.Release();
	SwordFishShadow.Release();
	TunaShadow.Release();
}
