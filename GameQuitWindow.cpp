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
	popUpTexture.Load("Pop_up���t2.png");
	buttonYesTexture.Load("PopUpButton_YES.png");
	buttonNoTexture.Load("PopUpButton_NO.png");
	finishTextTexture.Load("PopUpFinishGame.png");
	font.Create(32, "MS�@����");
	endFlg = false;
}
void CGameQuitWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) && !endFlg)
	{
		PostQuitMessage(0);
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY) && !endFlg)
	{
		Release();
		endFlg = true;
	}
}
void CGameQuitWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	buttonYesTexture.Render(buttonYesPosX,buttonYesPosY);
	buttonNoTexture.Render(buttonNoPosX, buttonNoPosY);
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
		@brief			�e�{�^���̋�`�̎擾
		@param			0...�͂��{�^���̋�`���擾
						1...�������{�^���̋�`���擾


		@return			�����ɑΉ������{�^���̋�`
*//**************************************************************************/
CRectangle CGameQuitWindow::GetRect(int i)
{
	if (i == 0)
		return CRectangle(buttonYesPosX, buttonYesPosY, buttonYesPosX + buttonYesTexture.GetWidth(), buttonYesPosY + buttonYesTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonNoPosX, buttonNoPosY, buttonNoPosX + buttonNoTexture.GetWidth(), buttonNoPosY + buttonNoTexture.GetHeight());
}