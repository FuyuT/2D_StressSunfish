#include "RetryWindow.h"

CRetryWindow::CRetryWindow()
{

}
CRetryWindow::~CRetryWindow()
{

}

void CRetryWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	buttonYesTexture.Load("PopUpButton_YES.png");
	buttonNoTexture.Load("PopUpButton_NO.png");
	font.Create(32, "MS�@����");
	endFlg = false;
}
void CRetryWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		//�Q�[����ʂ�������
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		endFlg = true;
		Release();
	}
}
void CRetryWindow::Render()
{
	popUpTexture.Render(200, 50);
	font.RenderString(750, 400, MOF_XRGB(0, 0, 0), "���g���C���܂���?");
	buttonYesTexture.Render(buttonYesPosX, buttonYesPosY);
	buttonNoTexture.Render(buttonNoPosX, buttonNoPosY);
}
void CRetryWindow::Release()
{
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
CRectangle CRetryWindow::GetRect(int i)
{
	if (i == 0)
		return CRectangle(buttonYesPosX, buttonYesPosY, buttonYesPosX + buttonYesTexture.GetWidth(), buttonYesPosY + buttonYesTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonNoPosX, buttonNoPosY, buttonNoPosX + buttonNoTexture.GetWidth(), buttonNoPosY + buttonNoTexture.GetHeight());
}