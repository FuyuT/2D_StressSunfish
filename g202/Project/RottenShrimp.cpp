#include "RottenShrimp.h"

CRottenShrimp::CRottenShrimp()
{
}

CRottenShrimp::~CRottenShrimp()
{
}

bool CRottenShrimp::Load()
{
	if (!Texture.Load("Obstacle\\staleShrimp.png"))return false;

	return true;
}

void CRottenShrimp::Initialize()
{
	rotateNum = 0;
}

void CRottenShrimp::Update(float wx, float wy)
{
	if (!showFlg)return;
	DegreeUpdate();
	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CRottenShrimp::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.RenderRotate(pos.x - wx, pos.y - wy,MOF_ToRadian(rotateNum),TEXALIGN_CENTERCENTER);
}

void CRottenShrimp::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CRottenShrimp::Release()
{
	Texture.Release();
}
