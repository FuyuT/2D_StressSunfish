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
	endFlg = false;
}
void CRetryWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		buttonYesScale = scaleController.ScaleControll(buttonYesScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			Release();
			endFlg = true;
			//ゲーム画面を初期化
			buttonResult = 1;
			nextPopUp = NULL;
		}
	}
	else
	{
		buttonYesScale = scaleMini;
	}
	if ( GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		buttonNoScale = scaleController.ScaleControll(buttonNoScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_POSE;
		}
	}
	else
	{
		buttonNoScale = scaleMini;
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