#include "TrophyWindow.h"
CTrophyWindow::CTrophyWindow()
{

}
CTrophyWindow::~CTrophyWindow()
{

}

void CTrophyWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	buttonBackTexture.Load("ButtonBack.png");

	font.Create(64, "MS�@����");
	endFlg = false;
}
void CTrophyWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		endFlg = true;
	}
}
void CTrophyWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "�g���t�B�[");
	buttonBackTexture.Render(buttonBackPosX, buttonBackPosY);
}
void CTrophyWindow::Release()
{
	popUpTexture.Release();
	buttonBackTexture.Release();
}