#include "CauseOfDeathWindow.h"

CCauseOfDeathWindow::CCauseOfDeathWindow()
{

}
CCauseOfDeathWindow::~CCauseOfDeathWindow()
{

}

void CCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_upt2.png");
	buttonNextTexture.Load("ButtonNext.png");
	//öeNX`ÇÝÝ
	switch (dethResult)
	{
	case CASE_INCREASEDBODYTEMPERATURE:
		//öFÌ·ã¸æðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_LOWERBODYTEMPERATURE:
		//öFÌ·áºæðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_STARVATION:
		//öFìæðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_CLOGGEDTHROAT:
		//öFAÂÜèæðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_OBESITY:
		//öFìæðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_IMPACT:
		//öFÕËæðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_PARASITE:
		//öFñ¶æðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_JUMP:
		//öFWvæðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_BUBBLE:
		//öFAæðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_TURTLE:
		//öFE~KæðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_WATERFLOW:
		//öF¬ACRðÇÝÞ
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	}
	font.Create(64, "MS@¾©");
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
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:MÇ");
		break;
	case CASE_LOWERBODYTEMPERATURE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:Ì·áº");
		break;
	case CASE_STARVATION:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:ì");
		break;
	case CASE_CLOGGEDTHROAT:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:AlÜè");
		break;
	case CASE_OBESITY:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:ì");
		break;
	case CASE_IMPACT:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:áQ¨ÆÕË");
		break;
	case CASE_PARASITE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:ñ¶");
		break;
	case CASE_JUMP:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:Wv");
		break;
	case CASE_BUBBLE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:A");
		break;
	case CASE_TURTLE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:E~K");
		break;
	case CASE_WATERFLOW:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "ö:¬");
		break;
	}
	if (newGetDethFlg)
	{
		font.RenderString(350, 250, MOF_XRGB(0, 0, 0), "NEW");
	}
	caseOfDethTexture.Render(300,500);
	buttonNextTexture.Render(buttonNextPosX, buttonNextPosY);
}
void CCauseOfDeathWindow::Release()
{
	caseOfDethTexture.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}