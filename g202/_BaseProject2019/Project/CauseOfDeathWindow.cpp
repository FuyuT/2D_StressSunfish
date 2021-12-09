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
	font.Create(64, "MS　明朝");
	buttonSelect = 1;
	endFlg = false;
}
void CCauseOfDeathWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = 1;
	}
	
	if (buttonSelect == 1)
	{
		buttonNextScale = scaleController.ScaleControll(buttonNextScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_RESULT;
		}
	}
}
void CCauseOfDeathWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	/*switch (deathResult)
	{
	case CAUSE_Hyperthermia:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:熱中症");
		break;
	case CAUSE_Frozen:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:体温低下");
		break;
	case CAUSE_Starvation:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:餓死");
		break;
	case CAUSE_ChokeOnShell:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:喉詰まり");
		break;
	case CAUSE_Obesity:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:肥満");
		break;
	case CAUSE_Obstacle:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:障害物と衝突");
		break;
	case CAUSE_Parasite:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:寄生虫");
		break;
	case CAUSE_Jump:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:ジャンプ");
		break;
	case CAUSE_Bubble:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:泡");
		break;
	case CAUSE_SeaTurtle:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:ウミガメ");
		break;
	case CAUSE_WaterFlow:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:水流");
		break;
	}*/
	if (newGetDeathFlg)
	{
		newGetTexture.Render(350, 250);
	}
	caseOfDethTexture.Render(causeOfDeathTexturePosX,causeOfDeathTexturePosY);
	scaleController.ScaleRender(&buttonNextTexture,buttonNextPosX,buttonNextPosY,buttonNextScale);
	deathTextTexture.Render(deathTextPosX, deathTextPosY);
}
void CCauseOfDeathWindow::Release()
{
	newGetTexture.Release();
	deathTextTexture.Release();
	caseOfDethTexture.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}