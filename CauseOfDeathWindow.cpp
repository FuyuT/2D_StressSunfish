#include "CauseOfDeathWindow.h"

CCauseOfDeathWindow::CCauseOfDeathWindow()
{

}
CCauseOfDeathWindow::~CCauseOfDeathWindow()
{

}

void CCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	buttonNextTexture.Load("ButtonNext.png");

	font.Create(64, "MS�@����");
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
	font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "����");
	buttonNextTexture.Render(buttonNextPosX, buttonNextPosY);
}
void CCauseOfDeathWindow::Release()
{
	popUpTexture.Release();
	buttonNextTexture.Release();
}