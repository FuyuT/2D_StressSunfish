#include "RetryWindow.h"

CRetryWindow::CRetryWindow()
{

}
CRetryWindow::~CRetryWindow()
{

}

void CRetryWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonYesTexture.Load("PopUpButton_YES.png");
	buttonNoTexture.Load("PopUpButton_NO.png");
	font.Create(32, "MS　明朝");
	endFlg = false;
}
void CRetryWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		//ゲーム画面を初期化
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		endFlg = true;
		Release();
	}
}
void CRetryWindow::Render()
{
	popUpTexture.Render(200, 50);
	font.RenderString(750, 400, MOF_XRGB(0, 0, 0), "リトライしますか?");
	buttonYesTexture.Render(buttonYesPosX, buttonYesPosY);
	buttonNoTexture.Render(buttonNoPosX, buttonNoPosY);
}
void CRetryWindow::Release()
{
	popUpTexture.Release();
	buttonYesTexture.Release();
	buttonNoTexture.Release();
}
/*************************************************************************//*!
		@brief			各ボタンの矩形の取得
		@param			0...はいボタンの矩形を取得
						1...いいえボタンの矩形を取得


		@return			引数に対応したボタンの矩形
*//**************************************************************************/
CRectangle CRetryWindow::GetRect(int i)
{
	if (i == 0)
		return CRectangle(buttonYesPosX, buttonYesPosY, buttonYesPosX + buttonYesTexture.GetWidth(), buttonYesPosY + buttonYesTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonNoPosX, buttonNoPosY, buttonNoPosX + buttonNoTexture.GetWidth(), buttonNoPosY + buttonNoTexture.GetHeight());
}