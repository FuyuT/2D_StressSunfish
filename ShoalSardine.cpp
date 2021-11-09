#include "ShoalSardine.h"

CShoalSardine::CShoalSardine()
{
}

CShoalSardine::~CShoalSardine()
{
}

bool CShoalSardine::Load()
{
	if (!Texture.Load("Obstacle\\mure.png"))return false;

	return true;
}

void CShoalSardine::Initialize()
{
	pos.x = 1000;
	pos.y = 1500;
	//showFlg = true;
	moveSpeed.x = 5.0f;
}

void CShoalSardine::Update(float wx, float wy)
{
	if (!showFlg)return;
	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CShoalSardine::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.Render(pos.x - wx, pos.y - wy);
}

void CShoalSardine::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CShoalSardine::Release()
{
	Texture.Release();
}