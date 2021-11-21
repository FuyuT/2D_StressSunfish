#include "RottenCrab.h"

CRottenCrab::CRottenCrab()
{
}

CRottenCrab::~CRottenCrab()
{
}

bool CRottenCrab::Load()
{
	if (!Texture.Load("obstacle\\staleCrab.png"))return false;

	return true;
}

void CRottenCrab::Initialize()
{
	rotateNum = 0;
}

void CRottenCrab::Update(float wx, float wy)
{
	if (!showFlg)return;
	DegreeUpdate();
	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CRottenCrab::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.RenderRotate(pos.x - wx, pos.y - wy,MOF_ToRadian(rotateNum),TEXALIGN_CENTERCENTER);
}

void CRottenCrab::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CRottenCrab::Release()
{
	Texture.Release();
}
