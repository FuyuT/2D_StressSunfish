#include "Bubble.h"

CBubble::CBubble()
{
}

CBubble::~CBubble()
{
}
bool CBubble::Load()
{
	if (!Texture.Load("Obstacle\\Bubble.png"))return false;

	return true;
}

void CBubble::Initialize()
{
	//pos.x = 1000;
	//pos.y = 2160;
	moveSpeed.y = 2.0f;
	showFlg = false;
}

void CBubble::Update(float wx, float wy)
{
	if (!showFlg)return;
	//移動
	pos.y -= moveSpeed.y;
	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CBubble::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.Render(pos.x - wx, pos.y - wy);
}

void CBubble::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CBubble::Release()
{
	Texture.Release();
}
