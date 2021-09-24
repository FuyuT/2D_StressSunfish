#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	if (!texture.Load("tempPlayer.png"))
	{
		return false;
	}
	return true;
}

void CPlayer::Initialize()
{
	Load();

	//�����l
	posX = 200;
	posY = g_pGraphics->GetTargetHeight() / 2 - texture.GetHeight() / 2;
}

void CPlayer::UpdateMove()
{

	//�E�Ɉړ�
	if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		moveX += PLAYER_SPEED;
		if (moveX > PLAYER_MAXSPEED)
		{
			moveX = PLAYER_MAXSPEED;
		}
	}
	else
	{
		if (moveX > 0)
		{
			moveX -= PLAYER_SPEED;
			if (moveX <= 0)
			{
				moveX = 0;
			}
		}
	}

	//��Ɉړ�
	if (g_pInput->IsKeyHold(MOFKEY_W))
	{
		moveY -= PLAYER_SPEED;
		if (moveY < -PLAYER_MAXSPEED)
		{
			moveY = -PLAYER_MAXSPEED;
		}
	}
	//���Ɉړ�
	else if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		moveY += PLAYER_SPEED;
		if (moveY > PLAYER_MAXSPEED)
		{
			moveY = PLAYER_MAXSPEED;
		}
	}
	else
	{
		if (moveY < 0)
		{
			moveY += PLAYER_SPEED;
			if (moveY >= 0)
			{
				moveY = 0;
			}
		}
		else if (moveY > 0)
		{
			moveY -= PLAYER_SPEED;
			if (moveY <= 0)
			{
				moveY = 0;
			}
		}
	}

	//�C��(�X�N���[���㕔)�@�ړ�����
	if (posY + texture.GetHeight() > g_pGraphics->GetTargetHeight())
	{
		posY = g_pGraphics->GetTargetHeight() - texture.GetHeight();
		moveY = 0;
	}
	//�C��(�X�N���[������)�@�ړ�����
	if (posY < 0)
	{
		posY = 0;
		moveY = 0;
	}

	//���x�����W�ɔ��f
	scrollX += moveX;
	posX += moveX;
	posY += moveY;
}

void CPlayer::Update()
{
	//�ړ��X�V
	UpdateMove();

	if (g_pInput->IsKeyPush(MOFKEY_A))
	{
		if (GetSearchRect().CollisionRect(GetFeedRect()))
		{
			feedDeadFlg = true;
		}
	}

	//���G�T�����ɓ���(�e�X�g�p)
	if(!feedDeadFlg)
		feedPosX -= 1;

}

void CPlayer::Render()
{
	//�v���C���[�̕`��
	texture.Render(posX - scrollX, posY);

	//���G�T�`��(�e�X�g�p)
	if(!feedDeadFlg)
		CGraphicsUtilities::RenderFillRect(GetFeedRect(), MOF_COLOR_RED);

	//�v���C���[�̍��W(�f�o�b�O)
	CGraphicsUtilities::RenderString(10, 10, "X���W : %d", GetPosX());
	CGraphicsUtilities::RenderString(10, 40, "Y���W : %d", GetPosY());

	//�{�̂̓����蔻��̕`��(�f�o�b�O)
	CGraphicsUtilities::RenderRect(
		GetRect(),MOF_COLOR_GREEN);

	//�G�T�T�m�͈͂̕`��(�f�o�b�O)
	CGraphicsUtilities::RenderRect(
		GetSearchRect(),MOF_COLOR_GREEN);
}

void CPlayer::Release()
{
	texture.Release();
}
