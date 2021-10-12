#include "ResultWindow.h"

CResultWindow::CResultWindow()
{

}
CResultWindow::~CResultWindow()
{

}

void CResultWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonNextTexture.Load("ButtonNext.png");

	font.Create(64, "MS　明朝");
	endFlg = false;
}
void CResultWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		endFlg = true;
		Release();
	}
}
void CResultWindow::Render()
{
	popUpTexture.Render(200, 50);
	font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "結果");
	buttonNextTexture.Render(buttonNextPosX, buttonNextPosY);
}
void CResultWindow::Release()
{
	popUpTexture.Release();
	buttonNextTexture.Release();
}