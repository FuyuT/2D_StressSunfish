#include "CauseOfDeathWindow.h"

CCauseOfDeathWindow::CCauseOfDeathWindow()
{

}
CCauseOfDeathWindow::~CCauseOfDeathWindow()
{
	Release();
}

void CCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonNextTexture.Load("ButtonNext.png");
	deathTextTexture.Load("PopUpCaseOfDeath.png");
	newGetTexture.Load("NEW.png");
	//死因テクスチャ読み込み
	switch (deathResult)
	{
	case CAUSE_Hyperthermia:
		//死因：体温上昇画像を読み込む
		caseOfDethTexture.Load("マンボウ 体温上昇.png");
		break;
	case CAUSE_Frozen:
		//死因：体温低下画像を読み込む
		caseOfDethTexture.Load("マンボウ 体温低下.png");
		break;
	case CAUSE_Starvation:
		//死因：餓死画像を読み込む
		caseOfDethTexture.Load("マンボウ 空腹2.png");
		break;
	case CAUSE_ChokeOnShell:
		//死因：喉つまり画像を読み込む
		caseOfDethTexture.Load("マンボウ　喉つまり.png");
		break;
	case CAUSE_Obesity:
		//死因：肥満画像を読み込む
		caseOfDethTexture.Load("肥満マンボウ2.png");
		break;
	case CAUSE_Obstacle:
		//死因：衝突画像を読み込む
		caseOfDethTexture.Load("障害物にあたって死亡.png");
		break;
	case CAUSE_Parasite:
		//死因：寄生虫画像を読み込む
		caseOfDethTexture.Load("マンボウ寄生虫ストレス.png");
		break;
	case CAUSE_Jump:
		//死因：ジャンプ画像を読み込む
		caseOfDethTexture.Load("水面にたたきつけられ死亡.png");
		break;
	case CAUSE_Bubble:
		//死因：泡画像を読み込む
		caseOfDethTexture.Load("マンボウ泡.png");
		break;
	case CAUSE_SeaTurtle:
		//死因：ウミガメ画像を読み込む
		caseOfDethTexture.Load("マンボウ亀予感.png");
		break;
	case CAUSE_WaterFlow:
		//死因：水流アイコンを読み込む
		caseOfDethTexture.Load("加速死.png");
		break;
	case CAUSE_ShoalFish:
		//死因：水流アイコンを読み込む
		caseOfDethTexture.Load("マンボウ　魚群衝突死 .png");
		break;
	}
	buttonSelect = 1;
	endFlg = false;
	buttonNextScaleFlg = false;

	//フォント
	font.Load(fontAdd, fontName);
	font.Create(118, fontName);
}
void CCauseOfDeathWindow::Update()
{
	popUpScale = scaleController.ScaleShrinkControll(popUpScale, scaleMini, causeOfDeathScaleSpeed);
	if (!buttonNextScaleFlg)
	{
		buttonNextScale = scaleController.ScaleShrinkControll(buttonNextScale, scaleMini, causeOfDeathScaleSpeed);
		if (buttonNextScale = scaleMini)
			buttonNextScaleFlg = true;
	}
	causeOfDeathTextureScale = scaleController.ScaleShrinkControll(causeOfDeathTextureScale, 0.7, causeOfDeathScaleSpeed);
	deathTextScale = scaleController.ScaleShrinkControll(deathTextScale, scaleMini, causeOfDeathScaleSpeed);
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (GetRect().CollisionPoint(mousePosX, mousePosY) && buttonSelect != 1)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 1;
	}

	if (buttonSelect == 1)
	{
		if (buttonNextScaleFlg)
			buttonNextScale = scaleController.ScaleControll(buttonNextScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_RESULT;
		}
	}
}
void CCauseOfDeathWindow::Render()
{
	//popUpTexture.Render(popUpPosX, popUpPosY);
	scaleController.ScaleRender(&popUpTexture, popUpPosX, popUpPosY, popUpScale);
	switch (deathResult)
	{
	case CAUSE_Hyperthermia:
		font.RenderString(660, 750, MOF_XRGB(0, 0, 0), "水面下は熱い！");
		break;

	case CAUSE_Frozen:
		font.RenderString(660, 750, MOF_XRGB(0, 0, 0), "深海は寒すぎた");
		break;

	case CAUSE_Starvation:
		font.RenderString(570, 750, MOF_XRGB(0, 0, 0), "ご飯が食べたかった...");
		break;

	case CAUSE_ChokeOnShell:
		font.RenderString(750, 750, MOF_XRGB(0, 0, 0), "骨が喉に！");
		break;

	case CAUSE_Obesity:
		font.RenderString(580, 780, MOF_XRGB(0, 0, 0), "食べ過ぎも悪かった。");
		break;

	case CAUSE_Obstacle:
		font.RenderString(640, 750, MOF_XRGB(0, 0, 0), "ゴミはゴミ箱へ。");
		break;

	case CAUSE_Parasite:
		font.RenderString(640, 750, MOF_XRGB(0, 0, 0), "痒くてたまらん！");
		break;

	case CAUSE_Jump:
		font.RenderString(690, 750, MOF_XRGB(0, 0, 0), "結構痛かった。");
		break;

	case CAUSE_Bubble:
		font.RenderString(720, 750, MOF_XRGB(0, 0, 0), "目がアアア！");
		break;

	case CAUSE_SeaTurtle:
		font.RenderString(450, 750, MOF_XRGB(0, 0, 0), "ウミガメに当たると思った...");
		break;

	case CAUSE_WaterFlow:
		font.RenderString(490, 750, MOF_XRGB(0, 0, 0), "マイペースで行きたいよね。");
		break;

	case CAUSE_ShoalFish:
		font.RenderString(680, 750, MOF_XRGB(0, 0, 0), "前から魚群が！");
		break;

	}
	scaleController.ScaleRender(&caseOfDethTexture, causeOfDeathTexturePosX, causeOfDeathTexturePosY, causeOfDeathTextureScale);
	if (newGetDeathFlg)
	{
		newGetTexture.Render(350, 250);
	}
	scaleController.ScaleRender(&buttonNextTexture, buttonNextPosX, buttonNextPosY, buttonNextScale);
	scaleController.ScaleRender(&deathTextTexture, deathTextPosX, deathTextPosY, deathTextScale);
}
void CCauseOfDeathWindow::Release()
{
	newGetTexture.Release();
	deathTextTexture.Release();
	caseOfDethTexture.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}

void CCauseOfDeathWindow::MouseCollision(int posX, int posY)
{
}
