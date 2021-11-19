#include "RottenFish.h"

CRottenFish::CRottenFish()
{
}

CRottenFish::~CRottenFish()
{
}

bool CRottenFish::Load()
{
	if (!Texture.Load("Obstacle\\staleFish.png"))return false;

	return true;
}

void CRottenFish::Initialize()
{
	//pos.x = 1000;
	//pos.y = 1500;
	//showFlg = true;
	rotateNum = 0;
}

void CRottenFish::Update(float wx, float wy)
{
	if (!showFlg)return;
	DegreeUpdate();
	//�X�N���[������o����showFlg��false
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CRottenFish::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.RenderRotate(pos.x - wx, pos.y - wy,MOF_ToRadian(rotateNum),TEXALIGN_CENTERCENTER);
}

void CRottenFish::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CRottenFish::Release()
{
	Texture.Release();
}