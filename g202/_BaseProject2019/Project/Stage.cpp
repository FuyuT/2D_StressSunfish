#include "Stage.h"

Stage::Stage() :
	texture(),
	scrollValueX(0.0f),
	scrollValueY(0.0f),
	enemyStart(NULL),
	enemyCount(0),
	enemyTexture(),
	enemyNo(0) {
}

Stage::~Stage() {
}

bool Stage::Load() {
	//追加
	if (texture.Load("SeaTexture.png")) 
	{
		return false;
	}

	if (!enemyTexture.Load("ウミガメ 清書.png")) {
		return false;
	}
	if (!enemyTexture.Load("ウミガメ ラフ.png")) {
		return false;
	}
	return true;
}

void Stage::Initialize(/*ENEMYSTART* pSt, int cnt*/) {
	//	scroll = 0;

	/*
	enemyNo = 0;
	enemyStart = pSt;
	enemyCount = cnt;
	*/
	Load();
}

void Stage::Update(Enemy* ene, /*int ecnt*/CPlayer& pl) {

	//追加
	//スクロール
	CRectangle prec = pl.GetRect();
	//スクリーン幅
	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	//ステージの幅四割の境界線
	float hsw = sw * 0.7f;
	float hsh = sh * 0.4f;
	//ステージ全体の幅 とりあえず画像の幅で
	//float stgw = texture.GetWidth();
	float stgh = texture.GetHeight();

	//左
	if (prec.Left - scrollValueX < hsw)
	{
		//境界線hswより進んだ値を、scrolValueに入れる
		scrollValueX -= hsw - (prec.Left - scrollValueX);
		if (scrollValueX <= 0)
		{
			scrollValueX = 0;
		}
	}
	//右
	if (prec.Right - scrollValueX > sw - hsw)
	{
		scrollValueX += (prec.Right - scrollValueX) - (sw - hsw);
		/*
		if (scrollValueX >= 99999 - sw)
		{
			scrollValueX = 99999 - sw;
		}
		*/
	}
	//上
	if (prec.Top - scrollValueY < hsh)
	{
		scrollValueY -= hsh - (prec.Top - scrollValueY);
		if (scrollValueY <= 0)
		{
			scrollValueY = 0;
		}
	}
	//下
	if (prec.Bottom - scrollValueY > sh - hsh)
	{
		scrollValueY += (prec.Bottom - scrollValueY) - (sh - hsh);
		if (scrollValueY >= stgh - sh)
		{
			scrollValueY = stgh - sh;
		}
	}

	if (g_pInput->IsKeyPush(MOFKEY_U))
	{
		ene[0].SetTexture(&enemyTexture);
		ene[0].Start(g_pGraphics->GetTargetWidth() + scrollValueX, 1000, 3);
	}

	//if (enemyNo < enemyCount && scroll >= enemyStart[enemyNo].scroll) {
	//	for (int i = 0; i < ecnt; i++) {
	//		if (ene[i].GetShow()) {
	//			continue;
	//		}
	//		ene[i].SetTexture(&enemyTexture);
	//		ene[i].Start(enemyStart[enemyNo].posX, 0, enemyStart[enemyNo].type);
	//		break;
	//	}
	//	enemyNo++;
	//}
}

void Stage::Render() {

	//追加
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	//texture.Render(-scrollValueX, -scrollValueY);

	int w = texture.GetWidth();
	int h = texture.GetHeight();
	//int sch = g_pGraphics->GetTargetWidth();
	for (float y = ((int)-scrollValueY % h) - h; y < sch; y += h)
	{
		for (float x = ((int)-scrollValueX % w) - w; x < scw; x += w)
		{
			texture.Render(x, y);
		}
	}

	/*
	for (float x = ((int)scrollValueX % w) + w; x > sch; x -= w) {
		texture.Render(-scrollValueX - x, -scrollValueY);
	}
	*/
}

void Stage::Release() {
	texture.Release();
	enemyTexture.Release();
}
