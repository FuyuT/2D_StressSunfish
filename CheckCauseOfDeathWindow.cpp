#include "CheckCauseOfDeathWindow.h"
#include "SceneStressCollection.h"
CCheckCauseOfDeathWindow::CCheckCauseOfDeathWindow()
{

}
CCheckCauseOfDeathWindow::~CCheckCauseOfDeathWindow()
{

}

void CCheckCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonBackTexture.Load("ButtonBack.png");

	if (buttonResult == CASE_INCREASEDBODYTEMPERATURE)
		causeOfDeathTexture.Load("マンボウ 体温上昇.png");

	if (buttonResult == CASE_LOWERBODYTEMPERATURE)
		causeOfDeathTexture.Load("マンボウ 体温低下.png");

	if (buttonResult == CASE_STARVATION)
		causeOfDeathTexture.Load("マンボウ 空腹2.png");	
	
	if (buttonResult == CASE_CLOGGEDTHROAT)
		causeOfDeathTexture.Load("マンボウ　喉つまり.png");

	if (buttonResult == CASE_OBESITY)
		causeOfDeathTexture.Load("肥満マンボウ2.png");

	if (buttonResult == CASE_IMPACT)
		causeOfDeathTexture.Load("障害物にあたって死亡.png");

	if (buttonResult == CASE_PARASITE)
		causeOfDeathTexture.Load("siin_aikon.png");

	if (buttonResult == CASE_JUMP)
		causeOfDeathTexture.Load("水面にたたきつけられ死亡.png");

	if (buttonResult == CASE_BUBBLE)
		causeOfDeathTexture.Load("siin_aikon.png");

	if (buttonResult == CASE_TURTLE)
		causeOfDeathTexture.Load("siin_aikon.png");

	if (buttonResult == CASE_WATERFLOW)
		causeOfDeathTexture.Load("加速死.png");

	font.Create(64, "MS　明朝");

	endFlg = false;
}
void CCheckCauseOfDeathWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		endFlg = true;
		nextPopUp = POPUPNO_RESULT;
	}
}
void CCheckCauseOfDeathWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	causeOfDeathTexture.Render(causeOfDeathTextureTexturePosX, causeOfDeathTextureTexturePosY);
	if (buttonResult == CASE_INCREASEDBODYTEMPERATURE)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "体温上昇しすぎて熱中症になり死亡");
	
	if (buttonResult == CASE_LOWERBODYTEMPERATURE)
		font.RenderString(440, 250, MOF_XRGB(0, 0, 0), "深海に潜りすぎて体温が下がりすぎて死亡");

	if (buttonResult == CASE_STARVATION)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "ご飯を食べなさすぎて餓死してしまった");

	if (buttonResult == CASE_CLOGGEDTHROAT)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "骨や殻が喉に刺さったストレスで死亡");
	
	if (buttonResult == CASE_OBESITY)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "食べ過ぎて肥満になったストレスで死亡");
	
	if (buttonResult == CASE_IMPACT)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "障害物にぶつかった衝撃で死亡");
	
	if (buttonResult == CASE_PARASITE)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "寄生虫が体に付きすぎたストレスで死亡");
	
	if (buttonResult == CASE_JUMP)
	{
		font.RenderString(450, 225, MOF_XRGB(0, 0, 0), "寄生虫を体から落とす為にジャンプして");
		font.RenderString(400, 280, MOF_XRGB(0, 0, 0), "水面に叩きつけた結果衝撃が強すぎて死亡");
	}

	if (buttonResult == CASE_BUBBLE)
		font.RenderString(550, 250, MOF_XRGB(0, 0, 0), "泡が目に入ったストレスで死亡");
	
	if (buttonResult == CASE_TURTLE)
	{
		font.RenderString(450, 225, MOF_XRGB(0, 0, 0), "目の前のウミガメにぶつかりそうな");
		font.RenderString(575, 275, MOF_XRGB(0, 0, 0), "予感のストレスで死亡");
	}

	if (buttonResult == CASE_WATERFLOW)
		font.RenderString(475, 250, MOF_XRGB(0, 0, 0), "急に加速させられたストレスで死亡");
	
	buttonBackTexture.Render(buttonBackPosX, buttonBackPosY);
}
void CCheckCauseOfDeathWindow::Release()
{
	popUpTexture.Release();
	buttonBackTexture.Release();
	causeOfDeathTexture.Release();
}