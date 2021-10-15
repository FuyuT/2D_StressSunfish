#include "ContinueWindow.h"


CContinueWindow::CContinueWindow()
{

}
CContinueWindow::~CContinueWindow()
{

}

void CContinueWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	buttonContinueTexture.Load("ButtonContine.png");
	buttonMenuTexture.Load("ButtonMenu.png");
	buttonTitleTexture.Load("ButtonTitle.png");

	font.Create(64, "MS�@����");
	endFlg = false;
}
void CContinueWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		//�R���e�B�j���[�{�^���������ꂽ�ۂ̏���
		endFlg = true;
		//�Q�[����ʂ�Initialise
<<<<<<< HEAD
		buttonResult = 1;
=======

>>>>>>> 9c61559dc03cccaa61a1b8e2cccfd8f49851171b
		nextPopUp = NULL;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		//���j���[��ʃ{�^���������ꂽ�Ƃ��̏���
		endFlg = true;
		//���j���[��ʂ֑J��
<<<<<<< HEAD
		buttonResult = 2;
=======

>>>>>>> 9c61559dc03cccaa61a1b8e2cccfd8f49851171b
		nextPopUp = NULL;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(2).CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		//�^�C�g����ʃ{�^���������ꂽ�ۂ̏���
		endFlg = true;
		//�^�C�g����ʂ֑J��
<<<<<<< HEAD
		buttonResult = 3;
=======

>>>>>>> 9c61559dc03cccaa61a1b8e2cccfd8f49851171b
		nextPopUp = NULL;
	}
}
void CContinueWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "�R���e�B�j���[�H");
	buttonContinueTexture.Render(buttonContinuePosX, buttonContinuePosY);
	buttonMenuTexture.Render(buttonMenuPosX, buttonMenuPosY);
	buttonTitleTexture.Render(buttonTitlePosX, buttonTitlePosY);
}
void CContinueWindow::Release()
{
	popUpTexture.Release();
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
		return CRectangle(buttonContinuePosX, buttonContinuePosY, buttonContinuePosX + buttonContinueTexture.GetWidth(), buttonContinuePosY + buttonContinueTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonMenuPosX, buttonMenuPosY, buttonMenuPosX + buttonMenuTexture.GetWidth(), buttonMenuPosY + buttonMenuTexture.GetHeight());
	else if (i == 2)
		return CRectangle(buttonTitlePosX, buttonTitlePosY, buttonTitlePosX + buttonTitleTexture.GetWidth(), buttonTitlePosY + buttonTitleTexture.GetHeight());
}