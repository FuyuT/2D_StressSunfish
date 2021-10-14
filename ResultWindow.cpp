#include "ResultWindow.h"

CResultWindow::CResultWindow()
{

}
CResultWindow::~CResultWindow()
{

}

void CResultWindow::Initialize()
{
	popUpTexture.Load("Pop_upƒ‰ƒt2.png");
	buttonNextTexture.Load("ButtonNext.png");

	font.Create(64, "MS@–¾’©");
	endFlg = false;
}
void CResultWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		endFlg = true;
		nextPopUp = POPUPNO_CONTINUE;
	}
}
void CResultWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "Œ‹‰Ê");
	buttonNextTexture.Render(buttonNextPosX, buttonNextPosY);
}
void CResultWindow::Release()
{
	popUpTexture.Release();
	buttonNextTexture.Release();
}