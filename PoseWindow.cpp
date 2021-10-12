#include "PoseWindow.h"

CPoseWindow::CPoseWindow()
{

}
CPoseWindow::~CPoseWindow()
{

}

void CPoseWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonConfigTexture.Load("ButtonConfig.png");
	buttonRetryTexture.Load("ButtonRetry.png");
	buttonTitleTexture.Load("ButtonTitle.png");
	buttonReturnGameTexture.Load("ButtonReturnGame.png");

	font.Create(64, "MS　明朝");
	endFlg = false;
}
void CPoseWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		//設定の処理
		endFlg = true;
		nextPopUp = NULL;
		//設定画面への遷移

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
		Release();
		nextPopUp = POPUPNO_BACKTOTITLE;
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(3).CollisionPoint(mousePosX, mousePosY))
	{
		//ゲームに戻るボタンが押された際の処理
		Release();
		endFlg = true;
		nextPopUp = NULL;
	}
}
void CPoseWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "ポーズ");
	buttonConfigTexture.Render(buttonConfigPosX, buttonConfigPosY);
	buttonRetryTexture.Render(buttonRetryPosX, buttonRetryPosY);
	buttonTitleTexture.Render(buttonTitlePosX, buttonTitlePosY);
	buttonReturnGameTexture.Render(buttonReturnGamePosX, buttonReturnGamePosY);
}
void CPoseWindow::Release()
{
	popUpTexture.Release();
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