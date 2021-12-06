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

	buttonSelect = 1;
	endFlg = false;
}
void CPoseWindow::Update()
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
	else if (GetRect(2).CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = 3;
	}
	else if (GetRect(3).CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = 4;
	}
	
	if (buttonSelect == 1)
	{
		buttonRetryScale = buttonScaleMini;
		buttonTitleScale = buttonScaleMini;
		buttonReturnGameScale = buttonScaleMini;
		buttonConfigScale = scaleController.ScaleControll(buttonConfigScale, buttonScaleMax, buttonScaleMini, scaleSpeed);

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 2;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 4;
		}
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//�ݒ��ʂɍs���Ă�PoseWindow����������Ȃ��悤�ɂ��Ă��遫�@����
			//Release();
			//�ݒ�̏���
			//endFlg = true;
			//nextPopUp = NULL;
			//�ݒ��ʂւ̑J��
			buttonResult = 4;
		}
	}
	else if (buttonSelect == 2)
	{
		buttonConfigScale = buttonScaleMini;
		buttonTitleScale = buttonScaleMini;
		buttonReturnGameScale = buttonScaleMini;
		buttonRetryScale = scaleController.ScaleControll(buttonRetryScale, buttonScaleMax, buttonScaleMini, scaleSpeed);
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 3;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 1;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//���g���C�{�^���������ꂽ�Ƃ��̏���
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_RETRY;
		}
	}
	else if (buttonSelect == 3)
	{
		buttonConfigScale = buttonScaleMini;
		buttonRetryScale = buttonScaleMini;
		buttonReturnGameScale = buttonScaleMini;
		buttonTitleScale = scaleController.ScaleControll(buttonTitleScale, buttonScaleMax, buttonScaleMini, scaleSpeed);

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 4;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 2;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(2).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//�^�C�g���ɖ߂�{�^���������ꂽ�Ƃ��̏���
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_BACKTOTITLE;
		}
	}
	else if (buttonSelect == 4)
	{
		buttonConfigScale = buttonScaleMini;
		buttonRetryScale = buttonScaleMini;
		buttonTitleScale = buttonScaleMini;
		buttonReturnGameScale = scaleController.ScaleControll(buttonReturnGameScale, buttonScaleMax, buttonScaleMini, scaleSpeed);

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 1;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 3;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(3).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//�Q�[���ɖ߂�{�^���������ꂽ�ۂ̏���
			Release();
			endFlg = true;
			nextPopUp = NULL;
			buttonResult = 5;
		}
	}
}
void CPoseWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	textTexture.Render(textPosX,textPosY);
	scaleController.ScaleRender(&buttonConfigTexture,buttonPosX,buttonConfigPosY,buttonConfigScale);
	scaleController.ScaleRender(&buttonRetryTexture,buttonPosX,buttonRetryPosY,buttonRetryScale);
	scaleController.ScaleRender(&buttonTitleTexture,buttonPosX,buttonTitlePosY,buttonTitleScale);
	scaleController.ScaleRender(&buttonReturnGameTexture,buttonPosX,buttonReturnGamePosY,buttonReturnGameScale);
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
		return CRectangle(buttonPosX, buttonConfigPosY, buttonPosX + buttonConfigTexture.GetWidth(), buttonConfigPosY + buttonConfigTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonPosX, buttonRetryPosY, buttonPosX + buttonRetryTexture.GetWidth(), buttonRetryPosY + buttonRetryTexture.GetHeight());
	else if (i == 2)
		return CRectangle(buttonPosX, buttonTitlePosY, buttonPosX + buttonTitleTexture.GetWidth(), buttonTitlePosY + buttonTitleTexture.GetHeight());
	else if (i == 3)
		return CRectangle(buttonPosX, buttonReturnGamePosY, buttonPosX + buttonReturnGameTexture.GetWidth(), buttonReturnGamePosY + buttonReturnGameTexture.GetHeight());
}
