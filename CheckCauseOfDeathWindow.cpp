#include "CheckCauseOfDeathWindow.h"
CCheckCauseOfDeathWindow::CCheckCauseOfDeathWindow()
{

}
CCheckCauseOfDeathWindow::~CCheckCauseOfDeathWindow()
{
	Release();
}

void CCheckCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonBackTexture.Load("ButtonBack.png");

	//フォント
	font.Load(fontAdd, fontName);
	font.Create(90, fontName);

	if (buttonResult == CAUSE_Hyperthermia)
		causeOfDeathTexture.Load("マンボウ 体温上昇.png");

	if (buttonResult == CAUSE_Frozen)
		causeOfDeathTexture.Load("マンボウ 体温低下.png");

	if (buttonResult == CAUSE_Starvation)
		causeOfDeathTexture.Load("マンボウ 空腹2.png");

	if (buttonResult == CAUSE_ChokeOnShell)
		causeOfDeathTexture.Load("マンボウ　喉つまり.png");

	if (buttonResult == CAUSE_Obesity)
		causeOfDeathTexture.Load("肥満マンボウ2.png");

	if (buttonResult == CAUSE_Obstacle)
		causeOfDeathTexture.Load("障害物にあたって死亡.png");

	if (buttonResult == CAUSE_Parasite)
		causeOfDeathTexture.Load("マンボウ寄生虫ストレス.png");

	if (buttonResult == CAUSE_Jump)
		causeOfDeathTexture.Load("水面にたたきつけられ死亡.png");

	if (buttonResult == CAUSE_Bubble)
		causeOfDeathTexture.Load("マンボウ泡.png");

	if (buttonResult == CAUSE_SeaTurtle)
		causeOfDeathTexture.Load("マンボウ亀予感.png");

	if (buttonResult == CAUSE_WaterFlow)
		causeOfDeathTexture.Load("加速死.png");

	if (buttonResult == CAUSE_ShoalFish)
		causeOfDeathTexture.Load("マンボウ　魚群衝突死 .png");

	buttonSelect = 1;
	endFlg = false;
}
void CCheckCauseOfDeathWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect().CollisionPoint(mousePosX, mousePosY) && buttonSelect != 1)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 1;
	}

	if (buttonSelect == 1)
	{
		buttonBackScale = scaleController.ScaleControll(buttonBackScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			Release();
			endFlg = true;
		}
	}
}
void CCheckCauseOfDeathWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	causeOfDeathTexture.RenderScale(causeOfDeathTexturePosX, causeOfDeathTexturePosY, 0.8);
	if (buttonResult == CAUSE_Hyperthermia)
	{
		font.RenderString(450, 760, MOF_XRGB(0, 0, 0), "体温上昇しすぎて熱中症になり死亡");
	}

	if (buttonResult == CAUSE_Frozen)
	{
		font.RenderString(365, 760, MOF_XRGB(0, 0, 0), "深海に潜りすぎて体温が下がりすぎて死亡");
	}

	if (buttonResult == CAUSE_Starvation)
	{
		font.RenderString(400, 760, MOF_XRGB(0, 0, 0), "ご飯を食べなさすぎて餓死してしまった");
	}

	if (buttonResult == CAUSE_ChokeOnShell)
	{
		font.RenderString(440, 760, MOF_XRGB(0, 0, 0), "骨や殻が喉に刺さったストレスで死亡");
	}

	if (buttonResult == CAUSE_Obesity)
	{
		font.RenderString(400, 760, MOF_XRGB(0, 0, 0), "食べ過ぎて肥満になったストレスで死亡");
	}

	if (buttonResult == CAUSE_Obstacle)
	{
		font.RenderString(550, 760, MOF_XRGB(0, 0, 0), "障害物にぶつかった衝撃で死亡");
	}

	if (buttonResult == CAUSE_Parasite)
	{
		font.RenderString(400, 760, MOF_XRGB(0, 0, 0), "寄生虫が体に付きすぎたストレスで死亡");
	}

	if (buttonResult == CAUSE_Jump)
	{
		font.RenderString(390, 735, MOF_XRGB(0, 0, 0), "寄生虫を体から落とす為にジャンプして");
		font.RenderString(360, 800, MOF_XRGB(0, 0, 0), "水面に叩きつけた結果衝撃が強すぎて死亡");
	}

	if (buttonResult == CAUSE_Bubble)
	{
		font.RenderString(530, 760, MOF_XRGB(0, 0, 0), "泡が目に入ったストレスで死亡");
	}

	if (buttonResult == CAUSE_SeaTurtle)
	{
		font.RenderString(450, 735, MOF_XRGB(0, 0, 0), "目の前のウミガメにぶつかりそうな");
		font.RenderString(640, 800, MOF_XRGB(0, 0, 0), "予感のストレスで死亡");
	}

	if (buttonResult == CAUSE_WaterFlow)
	{
		font.RenderString(475, 760, MOF_XRGB(0, 0, 0), "急に加速させられたストレスで死亡");
	}

	if (buttonResult == CAUSE_ShoalFish)
	{
		font.RenderString(525, 760, MOF_XRGB(0, 0, 0), "魚群に衝突したストレスで死亡");
	}

	scaleController.ScaleRender(&buttonBackTexture, buttonBackPosX, buttonBackPosY, buttonBackScale);
}
void CCheckCauseOfDeathWindow::Release()
{
	popUpTexture.Release();
	buttonBackTexture.Release();
	causeOfDeathTexture.Release();
}

void CCheckCauseOfDeathWindow::MouseCollision(int posX, int posY)
{
}
