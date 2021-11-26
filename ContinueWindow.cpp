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
	endFlg = false;
}
void CContinueWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		buttonContinueScale = scaleController.ScaleControll(buttonContinueScale,scaleMax,scaleMini,scaleSpeed);
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			Release();
			//�R���e�B�j���[�{�^���������ꂽ�ۂ̏���
			endFlg = true;
			//�Q�[����ʂ�Initialise
			buttonResult = 1;
			nextPopUp = NULL;
		}
	}
	else
	{
		buttonContinueScale = scaleMini;
	}
	if (GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		buttonMenuScale = scaleController.ScaleControll(buttonMenuScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			Release();
			//���j���[��ʃ{�^���������ꂽ�Ƃ��̏���
			endFlg = true;
			//���j���[��ʂ֑J��
			buttonResult = 2;

			nextPopUp = NULL;
		}
	}
	else
	{
		buttonMenuScale = scaleMini;
	}
	if (GetRect(2).CollisionPoint(mousePosX, mousePosY))
	{
		buttonTitleScale = scaleController.ScaleControll(buttonTitleScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			Release();
			//�^�C�g����ʃ{�^���������ꂽ�ۂ̏���
			endFlg = true;
			//�^�C�g����ʂ֑J��
			buttonResult = 3;

			nextPopUp = NULL;
		}
	}
	else
	{
		buttonTitleScale = scaleMini;
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