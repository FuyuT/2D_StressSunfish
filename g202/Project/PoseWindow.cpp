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

	buttonSelect = 1;
	endFlg = false;
}
void CPoseWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (buttonSelect == 1)
	{
		MouseCollision(mousePosX, mousePosY);
		buttonRetryScale = buttonScaleMini;
		buttonTitleScale = buttonScaleMini;
		buttonReturnGameScale = scaleController.ScaleControll(buttonReturnGameScale, buttonScaleMax, buttonScaleMini, scaleSpeed);
		buttonConfigScale = buttonScaleMini;

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(3).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			//ゲームに戻るボタンが押された際の処理
			Release();
			endFlg = true;
			nextPopUp = NULL;
			buttonResult = 5;
		}
	}
	else if (buttonSelect == 2)
	{
		MouseCollision(mousePosX, mousePosY);
		buttonConfigScale = buttonScaleMini;
		buttonTitleScale = buttonScaleMini;
		buttonReturnGameScale = buttonScaleMini;
		buttonRetryScale = scaleController.ScaleControll(buttonRetryScale, buttonScaleMax, buttonScaleMini, scaleSpeed);
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
			//リトライボタンが押されたときの処理
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_RETRY;
		}
	}
	else if (buttonSelect == 3)
	{
		MouseCollision(mousePosX, mousePosY);
		buttonConfigScale = scaleController.ScaleControll(buttonConfigScale, buttonScaleMax, buttonScaleMini, scaleSpeed);
		buttonRetryScale = buttonScaleMini;
		buttonTitleScale = buttonScaleMini;
		buttonReturnGameScale = buttonScaleMini;
		

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			//設定画面に行ってもPoseWindowが消去されないようにしている↓　藤原
			//Release();
			//設定の処理
			//endFlg = true;
			//nextPopUp = NULL;
			//設定画面への遷移
			buttonResult = 4;
		}
		
	}
	else if (buttonSelect == 4)
	{
		MouseCollision(mousePosX, mousePosY);
		buttonConfigScale = buttonScaleMini;
		buttonRetryScale = buttonScaleMini;
		buttonReturnGameScale = buttonScaleMini;
		buttonTitleScale = scaleController.ScaleControll(buttonTitleScale, buttonScaleMax, buttonScaleMini, scaleSpeed);

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(2).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			//タイトルに戻るボタンが押されたときの処理
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_BACKTOTITLE;
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

void CPoseWindow::MouseCollision(int posX, int posY)
{
	if (GetRect(3).CollisionPoint(posX,posY) && buttonSelect != 1)
	{
		buttonSelect = 1;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(1).CollisionPoint(posX, posY) && buttonSelect != 2)
	{
		buttonSelect = 2;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(0).CollisionPoint(posX, posY) && buttonSelect != 3)
	{
		buttonSelect = 3;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(2).CollisionPoint(posX, posY) && buttonSelect != 4)
	{
		buttonSelect = 4;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
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
		return CRectangle(buttonPosX, buttonConfigPosY, buttonPosX + buttonConfigTexture.GetWidth(), buttonConfigPosY + buttonConfigTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonPosX, buttonRetryPosY, buttonPosX + buttonRetryTexture.GetWidth(), buttonRetryPosY + buttonRetryTexture.GetHeight());
	else if (i == 2)
		return CRectangle(buttonPosX, buttonTitlePosY, buttonPosX + buttonTitleTexture.GetWidth(), buttonTitlePosY + buttonTitleTexture.GetHeight());
	else if (i == 3)
		return CRectangle(buttonPosX, buttonReturnGamePosY, buttonPosX + buttonReturnGameTexture.GetWidth(), buttonReturnGamePosY + buttonReturnGameTexture.GetHeight());
}
