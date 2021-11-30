#include "GameQuitWindow.h"

CGameQuitWindow::CGameQuitWindow()
{

}
CGameQuitWindow::~CGameQuitWindow()
{
	Release();
}

void CGameQuitWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonYesTexture.Load("PopUpButton_YES.png");
	buttonNoTexture.Load("PopUpButton_NO.png");
	finishTextTexture.Load("PopUpFinishGame.png");
	buttonSelect = 0;
	font.Create(32, "MS　明朝");
	endFlg = false;
}
void CGameQuitWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		keyModeFlg = false;
		buttonSelect = 1;
	}
	else if (GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		keyModeFlg = false;
		buttonSelect = 2;
	}
	else
	{
		if (!keyModeFlg)
		{
			buttonSelect = 0;
		}
	}

	if (buttonSelect == 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_LEFT) || g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			keyModeFlg = true;
			buttonSelect = 1;
		}
		buttonYesScale = scaleMini;
		buttonNoScale = scaleMini;
	}
	else if (buttonSelect == 1)
	{
		buttonNoScale = scaleMini;

		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			buttonSelect = 2;
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			buttonSelect = 2;
		}
		buttonYesScale = scaleController.ScaleControll(buttonYesScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			PostQuitMessage(0);
		}
	}
	else if (buttonSelect == 2)
	{
		buttonYesScale = scaleMini;
		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			buttonSelect = 1;
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			buttonSelect = 1;
		}
		buttonNoScale = scaleController.ScaleControll(buttonNoScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			Release();
			endFlg = true;
		}
	}
}
void CGameQuitWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	scaleController.ScaleRender(&buttonYesTexture, buttonYesPosX, buttonPosY, buttonYesScale);
	scaleController.ScaleRender(&buttonNoTexture, buttonNoPosX, buttonPosY, buttonNoScale);
	finishTextTexture.Render(finishTextPosX,finishTextPosY);
}
void CGameQuitWindow::Release()
{
	popUpTexture.Release();
	buttonYesTexture.Release();
	buttonNoTexture.Release();
	finishTextTexture.Release();
}
/*************************************************************************//*!
		@brief			各ボタンの矩形の取得
		@param			0...はいボタンの矩形を取得
						1...いいえボタンの矩形を取得


		@return			引数に対応したボタンの矩形
*//**************************************************************************/
CRectangle CGameQuitWindow::GetRect(int i)
{
	if (i == 0)
		return CRectangle(buttonYesPosX, buttonPosY, buttonYesPosX + buttonYesTexture.GetWidth(), buttonPosY + buttonYesTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonNoPosX, buttonPosY, buttonNoPosX + buttonNoTexture.GetWidth(), buttonPosY + buttonNoTexture.GetHeight());
}