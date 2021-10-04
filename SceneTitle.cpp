#include "SceneTitle.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Initialize()
{
	gamePrayButtonTexture.Load("ButtonStart.png");
	gameFinishButtonTexture.Load("ButtonFinish.png");
	gamePrayButtonPosX = 800;
	gamePrayButtonPosY = 700;
	gameFinishButtonPosX = 800;
	gameFinishButtonPosY = 800;
}

void CSceneTitle::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneTitle::Release();
	}
	//�Q�[���I�����������Ƃ��̏���
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
	}
}

void CSceneTitle::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "�^�C�g�����");
	gamePrayButtonTexture.Render(gamePrayButtonPosX, gamePrayButtonPosY);
	gameFinishButtonTexture.Render(gameFinishButtonPosX, gameFinishButtonPosY);
}

void CSceneTitle::Release()
{
	gamePrayButtonTexture.Release();
}

CRectangle CSceneTitle::GetRect(int i)
{
	if(i == 0)
		return CRectangle(gamePrayButtonPosX, gamePrayButtonPosY, gamePrayButtonPosX + gamePrayButtonTexture.GetWidth(), gamePrayButtonPosY + gamePrayButtonTexture.GetHeight());
	else if(i == 1)
		return CRectangle(gameFinishButtonPosX, gameFinishButtonPosY, gameFinishButtonPosX + gameFinishButtonTexture.GetWidth(), gameFinishButtonPosY + gameFinishButtonTexture.GetHeight());
}
