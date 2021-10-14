#include "ContinueWindow.h"


CContinueWindow::CContinueWindow()
{

}
CContinueWindow::~CContinueWindow()
{

}

void CContinueWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonContinueTexture.Load("ButtonContine.png");
	buttonMenuTexture.Load("ButtonMenu.png");
	buttonTitleTexture.Load("ButtonTitle.png");

	font.Create(64, "MS　明朝");
	endFlg = false;
}
void CContinueWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		//コンティニューボタンが押された際の処理
		endFlg = true;
		nextPopUp = NULL;
		Release();
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		//メニュー画面ボタンが押されたときの処理
		endFlg = true;
		nextPopUp = NULL;
		Release();
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(2).CollisionPoint(mousePosX, mousePosY))
	{
		//タイトル画面ボタンが押された際の処理
		endFlg = true;
		nextPopUp = NULL;
		Release();
	}
}
void CContinueWindow::Render()
{
	popUpTexture.Render(200, 50);
	font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "コンティニュー？");
	buttonContinueTexture.Render(buttonContinuePosX, buttonContinuePosY);
	buttonMenuTexture.Render(buttonMenuPosX, buttonMenuPosY);
	buttonTitleTexture.Render(buttonTitlePosX, buttonTitlePosY);
}
void CContinueWindow::Release()
{
	popUpTexture.Release();
	buttonContinueTexture.Release();
	buttonMenuTexture.Release();
	buttonTitleTexture.Release();
}

/*************************************************************************//*!
		@brief			各ボタンの矩形の取得
		@param			0...コンティニューボタンの矩形を取得
						1...メニューボタンの矩形を取得
						2...タイトルボタンの矩形を取得

		@return			引数に対応したボタンの矩形
*//**************************************************************************/
CRectangle CContinueWindow::GetRect(int i)
{
	if (i == 0)
		return CRectangle(buttonContinuePosX, buttonContinuePosY, buttonContinuePosX + buttonContinueTexture.GetWidth(), buttonContinuePosY + buttonContinueTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonMenuPosX, buttonMenuPosY, buttonMenuPosX + buttonMenuTexture.GetWidth(), buttonMenuPosY + buttonMenuTexture.GetHeight());
	else if (i == 2)
		return CRectangle(buttonTitlePosX, buttonTitlePosY, buttonTitlePosX + buttonTitleTexture.GetWidth(), buttonTitlePosY + buttonTitleTexture.GetHeight());
}