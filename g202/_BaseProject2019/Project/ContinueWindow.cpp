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
	popUpTexture.Load("Pop_upラフ2.png");
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
			//コンティニューボタンが押された際の処理
			endFlg = true;
			//ゲーム画面をInitialise
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
			//メニュー画面ボタンが押されたときの処理
			endFlg = true;
			//メニュー画面へ遷移
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
			//タイトル画面ボタンが押された際の処理
			endFlg = true;
			//タイトル画面へ遷移
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
		@brief			各ボタンの矩形の取得
		@param			0...コンティニューボタンの矩形を取得
						1...メニューボタンの矩形を取得
						2...タイトルボタンの矩形を取得

		@return			引数に対応したボタンの矩形
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