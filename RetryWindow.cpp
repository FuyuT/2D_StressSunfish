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
	popUpTexture.Load("Pop_up���t2.png");
	textTexture.Load("PopUpRetry.png");
	buttonYesTexture.Load("PopUpButton_YES.png");
	buttonNoTexture.Load("PopUpButton_NO.png");
	endFlg = false;
}
void CRetryWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		endFlg = true;
		//�Q�[����ʂ�������
		buttonResult = 1;
		nextPopUp = NULL;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		endFlg = true;
		nextPopUp = POPUPNO_POSE;
	}
}
void CRetryWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	textTexture.Render(textPosX,textPosY);
	buttonYesTexture.Render(buttonYesPosX, buttonYesPosY);
	buttonNoTexture.Render(buttonNoPosX, buttonNoPosY);
}
void CRetryWindow::Release()
{
	popUpTexture.Release();
	textTexture.Release();
	buttonYesTexture.Release();
	buttonNoTexture.Release();
}
/*************************************************************************//*!
		@brief			�e�{�^���̋�`�̎擾
		@param			0...�͂��{�^���̋�`���擾
						1...�������{�^���̋�`���擾


		@return			�����ɑΉ������{�^���̋�`
*//**************************************************************************/
CRectangle CRetryWindow::GetRect(int i)
{
	if (i == 0)
		return CRectangle(buttonYesPosX, buttonYesPosY, buttonYesPosX + buttonYesTexture.GetWidth(), buttonYesPosY + buttonYesTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonNoPosX, buttonNoPosY, buttonNoPosX + buttonNoTexture.GetWidth(), buttonNoPosY + buttonNoTexture.GetHeight());
}