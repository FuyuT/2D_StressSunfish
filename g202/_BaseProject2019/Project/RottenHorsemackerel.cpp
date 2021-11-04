#include "RottenHorsemackerel.h"

CRottenHorsemackerel::CRottenHorsemackerel()
{
}

CRottenHorsemackerel::~CRottenHorsemackerel()
{
}

bool CRottenHorsemackerel::Load()
{
	if (!Texture.Load("Obstacle\\staleFish.png"))return false;

	return true;
}

void CRottenHorsemackerel::Initialize()
{
	//pos.x = 1000;
	//pos.y = 1500;
	//showFlg = true;
}

void CRottenHorsemackerel::Update(float wx, float wy)
{
	if (!showFlg)return;
	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CRottenHorsemackerel::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.Render(pos.x - wx, pos.y - wy);
}

void CRottenHorsemackerel::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CRottenHorsemackerel::Release()
{
	Texture.Release();
}