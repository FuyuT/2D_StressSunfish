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
	popUpTexture.Load("Pop_upラフ2.png");
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
		//設定画面に行ってもPoseWindowが消去されないようにしている↓　藤原
		//Release();
		//設定の処理
		//endFlg = true;
		//nextPopUp = NULL;
		//設定画面への遷移
		buttonResult = 4;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		//リトライボタンが押されたときの処理
		Release();
		endFlg = true;
		nextPopUp = POPUPNO_RETRY;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(2).CollisionPoint(mousePosX, mousePosY))
	{
		//タイトル画面ボタンが押された際の処理
		Release();
		endFlg = true;
		nextPopUp = NULL;
		nextPopUp = POPUPNO_BACKTOTITLE;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(3).CollisionPoint(mousePosX, mousePosY))
	{
		//ゲームに戻るボタンが押された際の処理
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
		@brief			各ボタンの矩形の取得
		@param			0...コンティニューボタンの矩形を取得
						1...メニューボタンの矩形を取得
						2...タイトルボタンの矩形を取得

		@return			引数に対応したボタンの矩形
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
