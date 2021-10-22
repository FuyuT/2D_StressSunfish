#include "TrophyWindow.h"
CTrophyWindow::CTrophyWindow()
{

}
CTrophyWindow::~CTrophyWindow()
{

}

void CTrophyWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonBackTexture.Load("ButtonBack.png");

	font.Create(64, "MS　明朝");
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
	font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "トロフィー");
	buttonBackTexture.Render(buttonBackPosX, buttonBackPosY);
}
void CTrophyWindow::Release()
{
	popUpTexture.Release();
	buttonBackTexture.Release();
}