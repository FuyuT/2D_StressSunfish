#include "Stage.h"

Stage::Stage() :
	BackGroundTex1(),
	scrollValueX(0.0f),
	scrollValueY(0.0f),
	enemyCount(0),
	enemyTexture(),
	enemyNo(0) {
}

Stage::~Stage() {
}

bool Stage::Load() {
	//追加
	if (!BackGroundTex1.Load("BackGround\\BackGround_1.png")) 
	{
		return false;
	}
	if (!BackGroundTex2.Load("BackGround\\BackGround_2.png"))
	{
		return false;
	}
	if (!BackGroundTex3.Load("BackGround\\BackGround_3.png"))
	{
		return false;
	}
	if (!BackGroundTex4.Load("BackGround\\BackGround_4.png"))
	{
		return false;
	}
	if (!BackGroundTex5.Load("BackGround\\BackGround_5.png"))
	{
		return false;
	}
	if (!BackGroundTex6.Load("BackGround\\BackGround_6.png"))
	{
		return false;
	}

	return true;
}

void Stage::Initialize(/*ENEMYSTART* pSt, int cnt*/) {	
	WavePos.x = 0; WavePos.y = 0;
	WaveSpeed = 0;
	turnFlg = false;
}

void Stage::Update(/*Enemy* ene, int ecnt*/CPlayer& pl) {

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
	float stgh = BackGroundTex1.GetHeight();

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

	/*if (g_pInput->IsKeyPush(MOFKEY_U))
	{
		ene[0].SetTexture(&enemyTexture);
		ene[0].Start(g_pGraphics->GetTargetWidth() + scrollValueX, 1000, 3);
	}*/

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

	//波を動かす
	if (!turnFlg && WavePos.y > -100)
	{
		WaveSpeed = -3;
	}
	else if (WavePos.y < 0)
	{
		WaveSpeed = 0;
		turnFlg = true;
	}

	if (turnFlg && WavePos.y < 0)
	{
		WaveSpeed = 3;
	}
	else if (WavePos.y > 100)
	{
		turnFlg = false;
	}
	WavePos.y += WaveSpeed;
}

void Stage::Scroll(CTexture tex, int scrollSpeedX, int scrollSpeedY)
{
	//ScrollSpeedは大きいほどスクロールが遅くなる
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int w = tex.GetWidth();
	int h = tex.GetHeight();
	for (float y = ((int)-scrollValueY / scrollSpeedY % h) - h; y < sch; y += h)
	{
		for (float x = ((int)-scrollValueX / scrollSpeedX % w) - w; x < scw; x += w)
		{
			tex.Render(x, y);
		}
	}
}

void Stage::WaveRender()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int w = BackGroundTex2.GetWidth();
	int h = BackGroundTex2.GetHeight();
	for (float x = ((int)-scrollValueX / 2 % w) - w; x < scw; x += w)
	{
		BackGroundTex2.Render(x, WavePos.y - scrollValueY);
	}
}

void Stage::BackGroundRender() {
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();

	int w = BackGroundTex1.GetWidth();
	int h = BackGroundTex1.GetHeight();
	Scroll(BackGroundTex1, 1, 1);
	////動く波
	WaveRender();
	Scroll(BackGroundTex3, 1, 1);
	Scroll(BackGroundTex4, 4, 1);
	Scroll(BackGroundTex5, 3, 1);


}

void Stage::ForGroundRender()
{
	Scroll(BackGroundTex6, 1, 1);
}

void Stage::Render() {
	BackGroundRender();
}


void Stage::Release() {
	BackGroundTex1.Release();
	BackGroundTex2.Release();
	BackGroundTex3.Release();
	BackGroundTex4.Release();
	BackGroundTex5.Release();
	BackGroundTex6.Release();

	enemyTexture.Release();
}
