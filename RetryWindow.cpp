#include "RetryWindow.h"

CRetryWindow::CRetryWindow()
{

}
CRetryWindow::~CRetryWindow()
{
	Release();
}

void CRetryWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	textTexture.Load("PopUpRetry.png");
	buttonYesTexture.Load("PopUpButton_YES.png");
	buttonNoTexture.Load("PopUpButton_NO.png");
	buttonSelect = 1;
	endFlg = false;
}
void CRetryWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = 1;
	}
	else if (GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = 2;
	}
	

	if (buttonSelect == 1)
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

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			Release();
			endFlg = true;
			//ゲーム画面を初期化
			buttonResult = 1;
			nextPopUp = NULL;
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

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_POSE;
		}
	}
}
void CRetryWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	textTexture.Render(textPosX,textPosY);
	scaleController.ScaleRender(&buttonYesTexture, buttonYesPosX, buttonPosY, buttonYesScale);
	scaleController.ScaleRender(&buttonNoTexture, buttonNoPosX, buttonPosY, buttonNoScale);
}
void CRetryWindow::Release()
{
	popUpTexture.Release();
	textTexture.Release();
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
		return CRectangle(buttonYesPosX, buttonPosY, buttonYesPosX + buttonYesTexture.GetWidth(), buttonPosY + buttonYesTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonNoPosX, buttonPosY, buttonNoPosX + buttonNoTexture.GetWidth(), buttonPosY + buttonNoTexture.GetHeight());
}