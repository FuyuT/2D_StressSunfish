#include "CauseOfDeathWindow.h"

CCauseOfDeathWindow::CCauseOfDeathWindow()
{

}
CCauseOfDeathWindow::~CCauseOfDeathWindow()
{

}

void CCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_upƒ‰ƒt2.png");
	buttonNextTexture.Load("ButtonNext.png");

	font.Create(64, "MS@–¾’©");
	endFlg = false;
}
void CCauseOfDeathWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		endFlg = true;
		Release();
	}
}
void CCauseOfDeathWindow::Render()
{
	popUpTexture.Render(200, 50);
	font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "Ž€ˆö");
	buttonNextTexture.Render(buttonNextPosX, buttonNextPosY);
}
void CCauseOfDeathWindow::Release()
{
	popUpTexture.Release();
	buttonNextTexture.Release();
}