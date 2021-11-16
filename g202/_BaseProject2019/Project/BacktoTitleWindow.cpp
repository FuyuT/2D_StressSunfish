#include "BackToTitleWindow.h"

CBackToTitleWindow::CBackToTitleWindow()
{

}
CBackToTitleWindow::~CBackToTitleWindow()
{
	Release();
}

void CBackToTitleWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	textTexture.Load("PopUpBackToTitle.png");
	buttonYesTexture.Load("PopUpButton_YES.png");
	buttonNoTexture.Load("PopUpButton_NO.png");
	endFlg = false;
}
void CBackToTitleWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		endFlg = true;
		//�^�C�g����ʂɑJ��
		buttonResult = 3;
		nextPopUp = NULL;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		endFlg = true;
		nextPopUp = POPUPNO_POSE;
	}
}
void CBackToTitleWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	textTexture.Render(textPosX,textPosY);
	buttonYesTexture.Render(buttonYesPosX, buttonYesPosY);
	buttonNoTexture.Render(buttonNoPosX, buttonNoPosY);
}
void CBackToTitleWindow::Release()
{
	textTexture.Release();
	popUpTexture.Release();
	buttonYesTexture.Release();
	buttonNoTexture.Release();
}
/*************************************************************************//*!
		@brief			�e�{�^���̋�`�̎擾
		@param			0...�͂��{�^���̋�`���擾
						1...�������{�^���̋�`���擾


		@return			�����ɑΉ������{�^���̋�`
*//**************************************************************************/
CRectangle CBackToTitleWindow::GetRect(int i)
{
	if (i == 0)
		return CRectangle(buttonYesPosX, buttonYesPosY, buttonYesPosX + buttonYesTexture.GetWidth(), buttonYesPosY + buttonYesTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonNoPosX, buttonNoPosY, buttonNoPosX + buttonNoTexture.GetWidth(), buttonNoPosY + buttonNoTexture.GetHeight());
}