#include "CauseOfDeathWindow.h"

CCauseOfDeathWindow::CCauseOfDeathWindow()
{

}
CCauseOfDeathWindow::~CCauseOfDeathWindow()
{

}

void CCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonNextTexture.Load("ButtonNext.png");
	//死因テクスチャ読み込み
	switch (dethResult)
	{
	case CASE_INCREASEDBODYTEMPERATURE:
		//死因：体温上昇画像を読み込む
		caseOfDethTexture.Load("マンボウ 体温上昇.png");
		break;
	case CASE_LOWERBODYTEMPERATURE:
		//死因：体温低下画像を読み込む
		caseOfDethTexture.Load("マンボウ 体温低下.png");
		break;
	case CASE_STARVATION:
		//死因：餓死画像を読み込む
		caseOfDethTexture.Load("マンボウ 空腹2.png");
		break;
	case CASE_CLOGGEDTHROAT:
		//死因：喉つまり画像を読み込む
		caseOfDethTexture.Load("マンボウ　喉つまり.png");
		break;
	case CASE_OBESITY:
		//死因：肥満画像を読み込む
		caseOfDethTexture.Load("肥満マンボウ2.png");
		break;
	case CASE_IMPACT:
		//死因：衝突画像を読み込む
		caseOfDethTexture.Load("障害物にあたって死亡.png");
		break;
	case CASE_PARASITE:
		//死因：寄生虫画像を読み込む
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_JUMP:
		//死因：ジャンプ画像を読み込む
		caseOfDethTexture.Load("水面にたたきつけられ死亡.png");
		break;
	case CASE_BUBBLE:
		//死因：泡画像を読み込む
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_TURTLE:
		//死因：ウミガメ画像を読み込む
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_WATERFLOW:
		//死因：水流アイコンを読み込む
		caseOfDethTexture.Load("加速死.png");
		break;
	}
	font.Create(64, "MS　明朝");
	endFlg = false;
}
void CCauseOfDeathWindow::Update()
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
void CCauseOfDeathWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	switch (dethResult)
	{
	case CASE_INCREASEDBODYTEMPERATURE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:熱中症");
		break;
	case CASE_LOWERBODYTEMPERATURE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:体温低下");
		break;
	case CASE_STARVATION:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:餓死");
		break;
	case CASE_CLOGGEDTHROAT:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:喉詰まり");
		break;
	case CASE_OBESITY:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:肥満");
		break;
	case CASE_IMPACT:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:障害物と衝突");
		break;
	case CASE_PARASITE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:寄生虫");
		break;
	case CASE_JUMP:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:ジャンプ");
		break;
	case CASE_BUBBLE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:泡");
		break;
	case CASE_TURTLE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:ウミガメ");
		break;
	case CASE_WATERFLOW:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "死因:水流");
		break;
	}
	if (newGetDethFlg)
	{
		font.RenderString(350, 250, MOF_XRGB(0, 0, 0), "NEW");
	}
	caseOfDethTexture.Render(715,350);
	buttonNextTexture.Render(buttonNextPosX, buttonNextPosY);
}
void CCauseOfDeathWindow::Release()
{
	caseOfDethTexture.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}