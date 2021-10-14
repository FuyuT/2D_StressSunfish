#include "CheckCauseOfDeathWindow.h"
CCheckCauseOfDeathWindow::CCheckCauseOfDeathWindow()
{

}
CCheckCauseOfDeathWindow::~CCheckCauseOfDeathWindow()
{

}

void CCheckCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_upƒ‰ƒt2.png");
	buttonBackTexture.Load("ButtonBack.png");

	font.Create(64, "MS@–¾’©");
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
	font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "Ž€ˆö");
	buttonBackTexture.Render(buttonBackPosX, buttonBackPosY);
}
void CCheckCauseOfDeathWindow::Release()
{
	popUpTexture.Release();
	buttonBackTexture.Release();
}