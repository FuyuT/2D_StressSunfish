#include "ContinueWindow.h"


CContinueWindow::CContinueWindow()
{

}
CContinueWindow::~CContinueWindow()
{
	Release();
}

void CContinueWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	buttonContinueTexture.Load("ButtonContine.png");
	buttonMenuTexture.Load("ButtonMenu.png");
	buttonTitleTexture.Load("ButtonTitle.png");
	textTexture.Load("PopUpCountinue.png");
	buttonSelect = 1;
	endFlg = false;
}
void CContinueWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	MouseCollision(mousePosX,mousePosY);
	if (buttonSelect == 1)
	{
		buttonMenuScale = scaleMini;
		buttonTitleScale = scaleMini;
		buttonContinueScale = scaleController.ScaleControll(buttonContinueScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			Release();
			//�R���e�B�j���[�{�^���������ꂽ�ۂ̏���
			endFlg = true;
			//�Q�[����ʂ�Initialise
			buttonResult = 1;
			nextPopUp = NULL;
		}
	}
	else if (buttonSelect == 2)
	{
		buttonContinueScale = scaleMini;
		buttonTitleScale = scaleMini;
		buttonMenuScale = scaleController.ScaleControll(buttonMenuScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			Release();
			//���j���[��ʃ{�^���������ꂽ�Ƃ��̏���
			endFlg = true;
			//���j���[��ʂ֑J��
			buttonResult = 2;

			nextPopUp = NULL;
		}
	}
	else if (buttonSelect == 3)
	{
		buttonContinueScale = scaleMini;
		buttonMenuScale = scaleMini;
		buttonTitleScale = scaleController.ScaleControll(buttonTitleScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(2).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			Release();
			//�^�C�g����ʃ{�^���������ꂽ�ۂ̏���
			endFlg = true;
			//�^�C�g����ʂ֑J��
			buttonResult = 3;

			nextPopUp = NULL;
		}
	}
}
void CContinueWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	textTexture.Render(textPosX,textPosY);
	scaleController.ScaleRender(&buttonContinueTexture,buttonPosX,buttonContinuePosY,buttonContinueScale);
	scaleController.ScaleRender(&buttonMenuTexture,buttonPosX,buttonMenuPosY,buttonMenuScale);
	scaleController.ScaleRender(&buttonTitleTexture,buttonPosX,buttonTitlePosY,buttonTitleScale);
}
void CContinueWindow::Release()
{
	popUpTexture.Release();
	textTexture.Release();
	buttonContinueTexture.Release();
	buttonMenuTexture.Release();
	buttonTitleTexture.Release();
}

void CContinueWindow::MouseCollision(int posX, int posY)
{
	if (GetRect(0).CollisionPoint(posX,posY) && buttonSelect != 1)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 1;
	}
	else if (GetRect(1).CollisionPoint(posX, posY) && buttonSelect != 2)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 2;
	}
	else if (GetRect(2).CollisionPoint(posX, posY) && buttonSelect != 3)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 3;
	}

}

/*************************************************************************//*!
		@brief			�e�{�^���̋�`�̎擾
		@param			0...�R���e�B�j���[�{�^���̋�`���擾
						1...���j���[�{�^���̋�`���擾
						2...�^�C�g���{�^���̋�`���擾

		@return			�����ɑΉ������{�^���̋�`
*//**************************************************************************/
CRectangle CContinueWindow::GetRect(int i)
{
	if (i == 0)
		return CRectangle(buttonPosX, buttonContinuePosY, buttonPosX + buttonContinueTexture.GetWidth(), buttonContinuePosY + buttonContinueTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonPosX, buttonMenuPosY, buttonPosX + buttonMenuTexture.GetWidth(), buttonMenuPosY + buttonMenuTexture.GetHeight());
	else if (i == 2)
		return CRectangle(buttonPosX, buttonTitlePosY, buttonPosX + buttonTitleTexture.GetWidth(), buttonTitlePosY + buttonTitleTexture.GetHeight());
}