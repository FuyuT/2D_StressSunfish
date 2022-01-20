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
	buttonSelect = 1;
	font.Create(32, "MS　明朝");
	endFlg = false;
}
void CGameQuitWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	MouseCollision(mousePosX, mousePosY);
	

	if (buttonSelect == 1)
	{
		buttonNoScale = scaleMini;

		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		buttonYesScale = scaleController.ScaleControll(buttonYesScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_OK);
			PostQuitMessage(0);
		}
	}
	else if (buttonSelect == 2)
	{
		buttonYesScale = scaleMini;
		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		buttonNoScale = scaleController.ScaleControll(buttonNoScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_CANCEL);
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
void CGameQuitWindow::MouseCollision(int posX, int posY)
{
	if (GetRect(0).CollisionPoint(posX, posY) && buttonSelect != 1)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 1;
	}
	else if (GetRect(1).CollisionPoint(posX, posY) && buttonSelect != 2)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 2;
	}
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