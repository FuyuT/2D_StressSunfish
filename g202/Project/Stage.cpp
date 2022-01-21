#include "Stage.h"
#include "Utility.h"
Stage::Stage() :
	cloudTex(),
	skyTex(),
	scrollValueX(0.0f),
	scrollValueY(0.0f),
	enemyCount(0),
	enemyTexture(),
	enemyNo(0) {
}

Stage::~Stage() {
}

bool Stage::Load() {
	//背景画像
	for (int n = 0; n < 3; n++)
	{
		if (!cFishShadow[n].Load())return false;
	}
	if (!skyTex.Load("BackGround\\BackGround_0.png")) return false;
	if (!cloudTex.Load("BackGround\\BackGround_1.png")) return false;
	if (!backWaveTex.Load("BackGround\\BackGround_2.png")) return false;
	if (!frontWaveTex.Load("BackGround\\BackGround_3.png")) return false;
	if (!distantBackGroundTex.Load("BackGround\\BackGround_4.png"))	return false;
	if (!insideBackGroundTex.Load("BackGround\\BackGround_5.png")) return false;
	if (!closeBackGroundTex.Load("BackGround\\BackGround_6.png")) return false;
	//こんぶ
	//オブジェクトの数を取得して、数分メモリ確保
	CUtility::GetEditObjectData("Text\\gameObject_0.txt", kelp.tex, kelp.objectTotalNo, kelp.pos);
	objectKelp = new CBackObjectKelp[kelp.objectTotalNo];
	for (int n = 0; n < kelp.objectTotalNo; n++)
	{
		objectKelp[n].Load(kelp.tex, kelp.objectTotalNo, kelp.pos[n], -1, 3, 4);
	}
	return true;
}

void Stage::Initialize(/*ENEMYSTART* pSt, int cnt*/) {	
	scrollValueX = 0;
	backWavePos.x = 0;
	backWavePos.y = 0;
	backWaveSpeed.x = 0;
	backWaveSpeed.y = 0;
	backWaveScrollValueX = 0;
	backWaveTurnFlg = false;
	frontWavePos.x = 0;
	frontWavePos.y = 0;
	frontWaveScrollValueX = 0;
	for (int n = 0; n < 3; n++) {
		cFishShadow[n].Initialize();
	}

}

void Stage::WaveUpdate(const CRectangle& rec, const float& hsw)
{
	//波を動かす
	//後景の波
	//右移動
	backWaveScrollValueX += BACK_WAVE_SPEED;

	//上下移動
	if (!backWaveTurnFlg && backWavePos.y > -100)
	{
		backWaveSpeed.y = -3;
	}
	else if (backWavePos.y < 0)
	{
		backWaveSpeed.y = 0;
		backWaveTurnFlg = true;
	}

	if (backWaveTurnFlg && backWavePos.y < 0)
	{
		backWaveSpeed.y = 3;
	}
	else if (backWavePos.y > 100)
	{
		backWaveTurnFlg = false;
	}
	backWavePos.y += backWaveSpeed.y;

	//前面の波
	//左移動
	frontWaveScrollValueX += FRONT_WAVE_SPEED;
	if (rec.Right - scrollValueX > hsw)
	{
		frontWaveScrollValueX += ((rec.Right - scrollValueX) - hsw) * FRONT_WAVE_ADJUSTMENT_SPEED;
	}
}

void Stage::FishShadowUpdate(int distance) 
{
	//魚影
	if (distance % 10 == 0 && distance != 0)
	{
		for (int n = 0; n < 3; n++)
		{
			if (!cFishShadow[n].GetShow())
			{
				if (!FishShadowPercentage(25))
				{
					return;
				}
				cFishShadow[n].SetShow(true);
				//魚影のランダム決定
				int no = fishShadowNoRandom.Random(SARDINESHADOW, TUNASHADOW + 1);
				cFishShadow[n].SetFishShadowNo(no);
				//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

				cFishShadow[n].SetPosx(scrollValueX + g_pGraphics->GetTargetWidth());
				PosYRandom();
				cFishShadow[n].SetPosy(posY);
				switch (n)
				{
				case 0:
					cFishShadow[n].SetSpeed(4.0f);
					break;
				case 1:
					cFishShadow[n].SetSpeed(7.0f);
					break;
				case 2:
					cFishShadow[n].SetSpeed(10.0f);
					break;
				default:
					break;
				}
				return;
			}
			cFishShadow[n].Update(scrollValueX, scrollValueY);
		}
	}
}

void Stage::Update(/*Enemy* ene, int ecnt*/CPlayer& pl) {

	//追加
	//スクロール
	CRectangle prec = pl.GetRect();
	//スクリーン幅
	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	//ステージの幅四割の境界線
	float hsw = sw * 0.3f;
	float hsh = sh * 0.4f;
	//ステージ全体の幅 とりあえず画像の幅で
	float stgh = cloudTex.GetHeight();
	
	WaveUpdate(prec,hsw);

	//右
	if (prec.Right - scrollValueX > hsw)
	{
		scrollValueX += (prec.Right - scrollValueX) - hsw;
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

	//背景のオブジェクト
	//こんぶ
	for (int n = 0; n < kelp.objectTotalNo; n++)
	{
		objectKelp[n].Update(closeBackGroundTex.GetWidth(), scrollValueX);
	}

	FishShadowUpdate(pl.GetPosX());
}

void Stage::Scroll(CTexture tex, float scrollSpeedX, float scrollSpeedY)
{
	//ScrollSpeedは大きいほどスクロールが遅くなる
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int w = tex.GetWidth();
	int h = tex.GetHeight();
	for (float y = ((int)(-scrollValueY * scrollSpeedY) % h) - h; y < sch; y += h)
	{
		for (float x = ((int)(-scrollValueX * scrollSpeedX) % w) - w; x < scw; x += w)
		{
			tex.Render(x, y);
		}
	}
}

void Stage::WaveRender()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int w = backWaveTex.GetWidth();
	int h = backWaveTex.GetHeight();
	////上と右に動く波　後景
	for (float x = ((int)-backWaveScrollValueX % w) - w; x < scw; x += w)
	{
		backWaveTex.Render(x, backWavePos.y - scrollValueY);
	}
	//左に動く波 前景
	w = frontWaveTex.GetWidth();
	h = frontWaveTex.GetHeight();
	for (float x = ((int)-frontWaveScrollValueX % w) - w; x < scw; x += w)
	{
		frontWaveTex.Render(x, frontWavePos.y - scrollValueY);
	}

}

void Stage::BackGroundRender() {
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	skyTex.Render(0, 0);

	int w = cloudTex.GetWidth();
	int h = cloudTex.GetHeight();
	Scroll(cloudTex, 1, 1);
	WaveRender(); //動く波
	Scroll(distantBackGroundTex, 0.25, 1);
	FishShadowRender();
	Scroll(insideBackGroundTex, 0.5, 1);
}

void Stage::ForeGroundRender()
{
	Scroll(closeBackGroundTex, 1, 1);
}



void Stage::Render() {
	BackGroundRender();
	//背景のオブジェクト
	//こんぶ
	for (int n = 0; n < kelp.objectTotalNo; n++)
	{
		objectKelp[n].Render(closeBackGroundTex.GetWidth(), scrollValueX, scrollValueY, 1);
	}
	//CGraphicsUtilities::RenderString(100, 0, MOF_COLOR_BLACK,"scrollx:%1.0f y:%1.0f", scrollValueX, scrollValueY );
	//Vector2 mousePos;
	//g_pInput->GetMousePos(mousePos);
	//CGraphicsUtilities::RenderString(100, 200, MOF_COLOR_BLACK, "mousex:%1.0f y:%1.0f", mousePos.x, mousePos.y);
	//kelp.tex.Render(mousePos.x, mousePos.y);
}

void Stage::FishShadowRender()
{

	for (int n = 0; n < 3; n++) 
	{
 		cFishShadow[n].Render(scrollValueX, scrollValueY);
	}

}


void Stage::Release() {
	skyTex.Release();
	cloudTex.Release();
	
	backWaveTex.Release();
	frontWaveTex.Release();
	distantBackGroundTex.Release();
	insideBackGroundTex.Release();
	closeBackGroundTex.Release();
	enemyTexture.Release();
	for (int n = 0; n < 3; n++) {
		cFishShadow[n].Release();
	}

	delete kelp.pos;
	for (int n = 0; n < kelp.objectTotalNo; n++)
	{
		objectKelp[n].Release();
	}
	delete[] objectKelp;
}

int Stage::PosYRandom()
{

		posYNum = posYRandom.Random(1, 3);

	switch (posYNum)
	{
	case 1:
		posY = 1470;
		break;
	case 2:
		posY = 1815;
		break;
	case 3:
		posY = 2160;
		break;
	}
	return posYNum;

}