#include "PoseWindow.h"

CPoseWindow::CPoseWindow()
{

}
CPoseWindow::~CPoseWindow()
{
	Release();
}

void CPoseWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	textTexture.Load("PopUpPose.png");
	buttonConfigTexture.Load("ButtonConfig.png");
	buttonRetryTexture.Load("ButtonRetry.png");
	buttonTitleTexture.Load("ButtonTitle.png");
	buttonReturnGameTexture.Load("ButtonReturnGame.png");

	endFlg = false;
}
void CPoseWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		//�ݒ��ʂɍs���Ă�PoseWindow����������Ȃ��悤�ɂ��Ă��遫�@����
		//Release();
		//�ݒ�̏���
		//endFlg = true;
		//nextPopUp = NULL;
		//�ݒ��ʂւ̑J��
		buttonResult = 4;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		//���g���C�{�^���������ꂽ�Ƃ��̏���
		Release();
		endFlg = true;
		nextPopUp = POPUPNO_RETRY;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(2).CollisionPoint(mousePosX, mousePosY))
	{
		//�^�C�g����ʃ{�^���������ꂽ�ۂ̏���
		Release();
		endFlg = true;
		nextPopUp = NULL;
		nextPopUp = POPUPNO_BACKTOTITLE;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(3).CollisionPoint(mousePosX, mousePosY))
	{
		//�Q�[���ɖ߂�{�^���������ꂽ�ۂ̏���
		Release();
		endFlg = true;
		nextPopUp = NULL;
		buttonResult = 5;
	}
}
void CPoseWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	textTexture.Render(textPosX,textPosY);
	buttonConfigTexture.Render(buttonConfigPosX, buttonConfigPosY);
	buttonRetryTexture.Render(buttonRetryPosX, buttonRetryPosY);
	buttonTitleTexture.Render(buttonTitlePosX, buttonTitlePosY);
	buttonReturnGameTexture.Render(buttonReturnGamePosX, buttonReturnGamePosY);
}
void CPoseWindow::Release()
{
	popUpTexture.Release();
	textTexture.Release();
	buttonConfigTexture.Release();
	buttonRetryTexture.Release();
	buttonTitleTexture.Release();
	buttonReturnGameTexture.Release();
}

/*************************************************************************//*!
		@brief			�e�{�^���̋�`�̎擾
		@param			0...�R���e�B�j���[�{�^���̋�`���擾
						1...���j���[�{�^���̋�`���擾
						2...�^�C�g���{�^���̋�`���擾

		@return			�����ɑΉ������{�^���̋�`
*//**************************************************************************/
CRectangle CPoseWindow::GetRect(int i)
{
	if (i == 0)
		return CRectangle(buttonConfigPosX, buttonConfigPosY, buttonConfigPosX + buttonConfigTexture.GetWidth(), buttonConfigPosY + buttonConfigTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonRetryPosX, buttonRetryPosY, buttonRetryPosX + buttonRetryTexture.GetWidth(), buttonRetryPosY + buttonRetryTexture.GetHeight());
	else if (i == 2)
		return CRectangle(buttonTitlePosX, buttonTitlePosY, buttonTitlePosX + buttonTitleTexture.GetWidth(), buttonTitlePosY + buttonTitleTexture.GetHeight());
	else if (i == 3)
		return CRectangle(buttonReturnGamePosX, buttonReturnGamePosY, buttonReturnGamePosX + buttonReturnGameTexture.GetWidth(), buttonReturnGamePosY + buttonReturnGameTexture.GetHeight());
}
