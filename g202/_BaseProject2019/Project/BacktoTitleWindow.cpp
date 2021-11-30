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
	if (GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		buttonYesScale = scaleController.ScaleControll(buttonYesScale,scaleMax,scaleMini,scaleSpeed);
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			Release();
			endFlg = true;
			//�^�C�g����ʂɑJ��
			buttonResult = 3;
			nextPopUp = NULL;
		}
	}
	else
	{
		buttonYesScale = scaleMini;
	}
	if (GetRect(1).CollisionPoint(mousePosX, mousePosY))
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
void CBackToTitleWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	textTexture.Render(textPosX,textPosY);
	scaleController.ScaleRender(&buttonYesTexture,buttonYesPosX,buttonPosY,buttonYesScale);
	scaleController.ScaleRender(&buttonNoTexture,buttonNoPosX,buttonPosY,buttonNoScale);
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
		return CRectangle(buttonYesPosX, buttonPosY, buttonYesPosX + buttonYesTexture.GetWidth(), buttonPosY + buttonYesTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonNoPosX, buttonPosY, buttonNoPosX + buttonNoTexture.GetWidth(), buttonPosY + buttonNoTexture.GetHeight());
}