#include "Player.h"

CPlayer::CPlayer() :
	texture(),
	posX(0.0f),
	posY(0.0f),
	moveX(0.0f),
	moveY(0.0f),
	moveSpeed(1.0f),
	beforeJumpingPosY(0.0f),
	random(),
	jumpFlg(false),
	deadFlg(false),
	jumpPossibleFlg(false),
	eatPossibleFlg(false)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	//�v���C���[�̃e�N�X�`���̓ǂ݂���
	if (!texture.Load("Player.png"))
	{
		return false;
	}

	return true;
}

void CPlayer::Initialize()
{
	Load();

	//�m���̂��߂Ɏg���ϐ��̏�����
	random.SetSeed(time(NULL));

	//�����l
	posX = 200;
	posY = g_pGraphics->GetTargetHeight() / 2 - texture.GetHeight() / 2;
}

//�ړ�
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

	//�ړ��̃L�[���͂�������Ώd�͂̉e�����󂯂�悤
	if (!g_pInput->IsKeyHold(MOFKEY_D) && 
		!g_pInput->IsKeyHold(MOFKEY_W) && 
		!g_pInput->IsKeyHold(MOFKEY_S))
	{
		posY += GRAVITY;
	}

	
	//�C��(�X�N���[������)�@�ړ�����
	if (posY + texture.GetHeight() > UNDER_SEA)
	{
		posY = UNDER_SEA - texture.GetHeight();
		moveY = 0;
	}
	
	//�C��(�X�N���[���㕔)�@�ړ�����
	if (posY < SEA_LEVEL)
	{
		posY = SEA_LEVEL;
		moveY = 0;
	}
	
	
}

//�G�T��H�ׂ�
void CPlayer::Eat()
{
	//�G�T��H�ׂ�
	if (g_pInput->IsKeyPush(MOFKEY_A) &&
		eatPossibleFlg)
	{

		//�����F�얞
		if(hungry == FULL_STOMACH)
		{
			deadFlg = true;
			return;
		}

		//�󕠂𖞂���
		hungry += FEED_SATIETYLEVEL;
		//�����l�𒴂�����
		if (hungry > FULL_STOMACH)
		{
			hungry = FULL_STOMACH;
		}

		//�����F�A�܂�
		//20%�Ŏ���
		deadFlg = DieInPercentage(20);
	}
}

//�W�����v
void CPlayer::Jump()
{
	//�C�ʂɋ߂��Ƃ��� A ������ 50�͉��̐���
	if (g_pInput->IsKeyPush(MOFKEY_A) && !jumpFlg)
	{
		jumpFlg = true;	
		jumpPossibleFlg = false;

		//�����ɂ�鐨���ŏ�������悤�� 50�͓K��
		beforeJumpingPosY = posY + 50.0f;

		moveY = -JUMP_POWER_Y;
		moveX = JUMP_POWER_X;
	}
	else if (jumpFlg)
	{
		moveY += PLAYER_SPEED;
		if (posY > beforeJumpingPosY)
		{
			moveY = 0;
			moveX = 0;
			jumpFlg = false;
		}

	}
}

//�X�V
void CPlayer::Update()
{
	//�v���C���[������ł���ꍇ
	if (deadFlg)
		return;

	//���x�����W�ɔ��f
	posX += moveX;
	posY += moveY;

	//�W�����v
	Jump();

	//�W�����v���͑��̑��삪�s���Ȃ��悤��
	if (jumpFlg)
		return;

	//�ړ��X�V
	UpdateMove();

	//�G�T��H�ׂ�
	Eat();

}

//�`��
void CPlayer::Render(float wx, float wy)
{
	//�v���C���[������ł���ꍇ
	if (deadFlg)
		return;

	//�v���C���[�̕`��
	texture.Render(posX - wx, posY - wy);
}

//�f�o�b�O�`��
void CPlayer::RenderDebug()
{
	//�f�o�b�O
	if (jumpFlg)
	{
		CGraphicsUtilities::RenderString(100, 100, "�W�����v!!");
	}

	//�v���C���[�̍��W(�f�o�b�O)
	CGraphicsUtilities::RenderString(10, 10, "X���W : %d", GetPosX());
	CGraphicsUtilities::RenderString(10, 40, "Y���W : %d", GetPosY());

	//�{�̂̓����蔻��̕`��(�f�o�b�O)
	CGraphicsUtilities::RenderRect(
		GetRect(), MOF_COLOR_GREEN);

	//�G�T�T�m�͈͂̕`��(�f�o�b�O)
	CGraphicsUtilities::RenderRect(
		GetSearchRect(), MOF_COLOR_GREEN);
}

//���
void CPlayer::Release()
{
	texture.Release();

}


//�G(��Q���A�G�T�A�E�~�K���A�A�A����)�Ƃ̓����蔻��
void CPlayer::Collision(Enemy& ene)
{

	if (!ene.GetShow())
	{
		return;
	}

	//�G�̋�`�Ǝ����̋�`�œ����蔻��
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();
	if (prec.CollisionRect(erec))
	{
		switch (ene.GetType())
		{
			//�E�~�K��
			case 0:
				//������Α���
				deadFlg = true;
				break;
			//�A
			case 1:
				//5%�Ŏ���
				deadFlg = DieInPercentage(5);
				break;
			//��Q��
			case 2:
				//20%�Ŏ���
				deadFlg = DieInPercentage(20);
				break;
			//����
			case 3:
				moveSpeed = 2.0f;
				break;

		}

	}

	//�G�T�ł���Ȃ��
	if (ene.GetType() == 3)
	{
		//�G�T�Ƃ̓����蔻��(�G�T�p�̃N���X������Ȃ�A�V����CollsionItem()�Ƃ�������Ă����Ɉڂ�)
		prec = GetSearchRect();
		if (prec.CollisionRect(erec))
		{
			//�T�m�͈͓��ɃG�T������ꍇtrue
			eatPossibleFlg = true;
		}
		else
		{
			//�T�m�͈͓��ɃG�T���Ȃ��ꍇfalse
			eatPossibleFlg = false;
		}
	}

}
