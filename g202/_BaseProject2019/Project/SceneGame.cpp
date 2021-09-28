#include "SceneGame.h"
#define	PLAYER_SPEED 10
CSceneGame::CSceneGame():
scrollValueX(0),
scrollValueY(0)
{
}

CSceneGame::~CSceneGame()
{
	Release();
}

void CSceneGame::Initialize()
{
	//stressGauge.Load("gauge.png");
	backGroundTexture.Load("SeaTexture.png");
	playerTexture.Load("Player.png");
}

void CSceneGame::Update()
{
	//��ʑJ��
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_TITLE;
	}

	//�X�N���[��
	CRectangle prec = GetRect();
	//�X�N���[����
	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	//�X�e�[�W�̕��l���̋��E��
	float hsw = sw * 0.4f;
	float hsh = sh * 0.4f;
	//�X�e�[�W�S�̂̕� �Ƃ肠�����摜�̕���
	float stgw = backGroundTexture.GetWidth();
	float stgh = backGroundTexture.GetHeight();
	//��
	if (prec.Left - scrollValueX < hsw)
	{
		//���E��hsw���i�񂾒l���AscrolValue�ɓ����
		scrollValueX -= hsw - (prec.Left - scrollValueX);
		if (scrollValueX <= 0)
		{
			scrollValueX = 0;
		}
	}
	//�E
	if (prec.Right - scrollValueX > sw - hsw)
	{
		scrollValueX += (prec.Right - scrollValueX) - (sw - hsw);
		if (scrollValueX >= stgw - sw)
		{
			scrollValueX = stgw - sw;
		}
	}
	//��
	if (prec.Top - scrollValueY < hsh)
	{
		scrollValueY -= hsh - (prec.Top - scrollValueY);
		if (scrollValueY <= 0)
		{
			scrollValueY = 0;
		}
	}
	//��
	if (prec.Bottom - scrollValueY > sh - hsh)
	{
		scrollValueY += (prec.Bottom - scrollValueY) - (sh - hsh);
		if (scrollValueY >= stgh - sh)
		{
			scrollValueY = stgh - sh;
		}
	}
	
	//�ړ�
	//�������i���Ȃ��Ɖ�������̂�
	moveSpeed.x = 0; moveSpeed.y = 0;
	if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		moveSpeed.x += PLAYER_SPEED;
		distancePlayer += 10.0f;
	}
	else if(g_pInput->IsKeyHold(MOFKEY_A))
	{
		moveSpeed.x -= PLAYER_SPEED;
	}
	if (g_pInput->IsKeyHold(MOFKEY_W))
	{
		moveSpeed.y -= PLAYER_SPEED;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		moveSpeed.y += PLAYER_SPEED;
	}
	//�ړ�����
	//���E
	if (prec.Left < 0)
	{
		playerX = 0;
	}
	else if (prec.Right > stgw)
	{
		playerX = stgw - playerTexture.GetWidth();
	}
	//�㉺
	if (prec.Top < 0)
	{
		playerY = 0;
	}
	else if (prec.Bottom > stgh)
	{
		playerY = stgh - playerTexture.GetHeight();
	}
	
	//���ۂɈړ�
	playerX += moveSpeed.x;
	playerY += moveSpeed.y;


	//else if (prec.Right > backGroundTexture.GetWidth())
	//{
	//	playerX = stgw - playerTexture.GetWidth();
	//}


	//if (timeCnt == 75)
	//{
	//	stressNumber -= 1;
	//	stressBarChenge -= 3;

	//	timeCnt = 0;
	//}
	//else
	//{
	//	timeCnt += 1;
	//}

}

void CSceneGame::Render()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);
	playerTexture.Render(playerX - scrollValueX, playerY - scrollValueY);
	//CGraphicsUtilities::RenderString(100, 300, "game���");
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);
	//CGraphicsUtilities::RenderFillCircle(playerX, playerY, 20, MOF_XRGB(0, 255, 0));
	//CGraphicsUtilities::RenderFillRect(stressBarX, stressBarY, stressBarX + stressBarChenge, stressBarY + 40, MOF_XRGB(0, 255, 0));
	//stressGauge.Render(stressBarX, stressBarY);
}

void CSceneGame::Release()
{
	backGroundTexture.Release();
	playerTexture.Release();
	//stressGauge.Release();
}
