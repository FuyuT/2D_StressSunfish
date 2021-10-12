#include "Player.h"

CPlayer::CPlayer() :
	texture(),
	posX(0.0f),
	posY(0.0f),
	moveX(0.0f),
	moveY(0.0f),
	moveSpeed(1.0f),
	random(),
	jumpFlg(false),
	deadFlg(false),
	possibleToJumpFlg(false),
	possibleToEatFlg(false),
	hungry(10),
	temperature(50)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	//�v���C���[�̃e�N�X�`���̓ǂ݂���
	if (!texture.Load("�}���{�E.png"))
	{
		return false;
	}

	return true;
}

void CPlayer::Initialize()
{
	//�ǂݍ��݂��s��
	Load();

	//�m���̂��߂Ɏg���ϐ��̏�����
	random.SetSeed(time(NULL));

	/********
	* �����l
	*********/
	//���W
	posX = 200;   // 200�͓K���@���u��
	posY = g_pGraphics->GetTargetHeight() / 2 - texture.GetHeight() / 2;
	//���(�X�e�[�^�X)
	temperature = TEMPERATURE_LIMIT / 2;
	hungry = FULL_STOMACH;
	parasite = 0;
	moveX = 0.0f;
	moveY = 0.0f;
	moveSpeed = 1.0f;
	causeOfDeath = CAUSE_None;
	//�^�C�}�[
	hungryTime = HUNGRY_SPEED;

	//�t���O
	jumpFlg = false;
	deadFlg = false;
	possibleToEatFlg = false;
	possibleToJumpFlg = false;
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
	if (GetRect().Bottom > UNDER_SEA)
	{
		posY = UNDER_SEA - texture.GetHeight() + COLLISION_ADJUSTMENT;
		moveY = 0;
	}
	
	//�C��(�X�N���[���㕔)�@�ړ�����
	if (GetRect().Top < SEA_LEVEL)
	{
		posY = SEA_LEVEL - COLLISION_ADJUSTMENT;
		moveY = 0;
	}
	
	
}

//�G�T��H�ׂ�
bool CPlayer::Eat()
{
	//�G�T��H�ׂ�
	if (g_pInput->IsKeyPush(MOFKEY_A))
	{
		
		possibleToEatFlg = false;

		if (causeOfDeath == CAUSE_None)
		{
			//�����F�얞
			if (hungry == FULL_STOMACH)
			{
				deadFlg = true;
				causeOfDeath = CAUSE_Obesity;
				//�G�T��showFlg��false�ɂ���
				return false;
			}
		}

		//�󕠂𖞂���
		hungry += FEED_SATIETYLEVEL;
		//�����l�𒴂�����
		if (hungry > FULL_STOMACH)
		{
			hungry = FULL_STOMACH;
		}

		
		if (causeOfDeath == CAUSE_None)
		{
			//�����F�A�܂�
			//20%�Ŏ���
			deadFlg = DieInPercentage(20);
			if (deadFlg)
				causeOfDeath = CAUSE_ChokeOnShell;
		}

		//�G�T��showFlg��false�ɂ���
		return false;
	}

	//�G�T��H�ׂȂ������Ƃ��́A�G�T��showFlg��true�̂܂܂ɂ���
	return true;
}

//�W�����v
void CPlayer::Jump()
{
	//�C�ʂɋ߂��Ƃ��� A ������
	//�C�ʂ��� +40(�K��)�ȓ��͈͓̔��ł����
	if (g_pInput->IsKeyPush(MOFKEY_A) &&
		possibleToJumpFlg )
	{
		jumpFlg = true;	
		possibleToJumpFlg = false;
		//�񐶒���U�藎�Ƃ�
		parasite = 0;

		moveY = -JUMP_POWER_Y;
		moveX = JUMP_POWER_X;
	}
	else if (jumpFlg)
	{
		moveY += PLAYER_SPEED;

		//�C�ʂ�艺��(�C�ɖ߂�����)
		//�����ɂ�鐨���ŏ�������悤�� +50(�K��)
		if (posY > SEA_LEVEL + 50.0f)
		{
			moveY = 0;
			moveX = 0;
			jumpFlg = false;
			if (causeOfDeath == CAUSE_None)
			{
				//�����F�Ռ���
				//10%�Ŏ���
				deadFlg = DieInPercentage(10);
				if (deadFlg)
					causeOfDeath = CAUSE_Jump;
			}
		}

	}
}

//�v���C���[�̏�Ԃ��X�V
void CPlayer::UpdateStatus()
{
	if (deadFlg)
	{
		//���ʃA�j���[�V�����̍Đ��Ƃ�
	}

	//���x�����W�ɔ��f
	posX += moveX * moveSpeed;
	posY += moveY * moveSpeed;


	//�W�����v�\
	//40�͉��̐��� �C�ʂ���ǂꂭ�炢�͈̔͂��W�����v�\�G���A��
	if (GetRect().Top < SEA_LEVEL + 40.0f &&
		!jumpFlg)
	{
		possibleToJumpFlg = true;
	}
	else
	{
		possibleToJumpFlg = false;
	}

	

	/*********
	 * �̉�
	 *********/
	if (GetRect().Top < SEA_LEVEL + TEMPERATURE_CHANGEZONE)
	{
		//�̉��㏸
		if (temperature >= TEMPERATURE_LIMIT)
		{
			if (causeOfDeath == CAUSE_None)
			{
				//�����F�M����
				deadFlg = true;
				causeOfDeath = CAUSE_Hyperthermia;
			}
		}
		else if (temperatureTime < 0)
		{
			temperature += 1;
			temperatureTime = TEMPERATURE_SPEED;
		}
		else
		{
			temperatureTime--;
		}

	}
	else if(GetRect().Top > UNDER_SEA - TEMPERATURE_CHANGEZONE)
	{
		//�̉����~
		if (temperature <= 0)
		{
			if (causeOfDeath == CAUSE_None)
			{
				//�����F����
				deadFlg = true;
				causeOfDeath = CAUSE_Frozen;
			}
		}
		else if (temperatureTime < 0)
		{
			temperature -= 1;
			temperatureTime = TEMPERATURE_SPEED;
		}
		else
		{
			temperatureTime--;
		}
	}
	else
	{
		//�̉��������ɋ߂Â�
		if (temperatureTime < 0)
		{
			if (temperature > TEMPERATURE_LIMIT / 2)
			{
				temperature -= 1;
			}
			else if (temperature < TEMPERATURE_LIMIT / 2)
			{
				temperature += 1;
			}
			temperatureTime = TEMPERATURE_SPEED * 2;
		}
		else
		{
			temperatureTime--;
		}
	}


	/*********
	 * �񐶒�
	 *********/
	if (parasite >= PARASITE_LIMIT)
	{
		if (causeOfDeath == CAUSE_None)
		{
			//�����F�񐶎�
			deadFlg = true;
			causeOfDeath = CAUSE_Parasite;
		}
	}
	else if (parasiteTime < 0)
	{
		parasite += 1;
		parasiteTime = PARASITE_SPEED;
	}
	else
	{
		parasiteTime--;
	}

	/*********
	 * ��
	 *********/
	if (hungry <= 0)
	{
		if (causeOfDeath == CAUSE_None)
		{
			//�����F�쎀
			deadFlg = true;
			causeOfDeath = CAUSE_Starvation;
		}
	}
	else if (hungryTime < 0)
	{
		hungry -= 1;
		hungryTime = HUNGRY_SPEED;
	}
	else
	{
		hungryTime--;
	}

	//����
	if (streamTime > 0)
	{
		streamTime--;
	}
	else if (moveSpeed > 1.0f)
	{
		// 0.1 ������
		moveSpeed -= 0.1f;
		// ���x�̔{���� 1.0 �ȉ��ɂȂ����� 1.0 �ŏ�����
		if (moveSpeed < 1.0f)
		{
			moveSpeed = 1.0f;
		}
	}

}

//�X�V
void CPlayer::Update()
{
	//�v���C���[������ł���ꍇ
	if (deadFlg)
		return;

	//�X�e�[�^�X(���)�̍X�V
	UpdateStatus();

	//�W�����v
	Jump();

	//�W�����v���͑��̑��삪�s���Ȃ��悤��
	if (jumpFlg)
		return;

	//�ړ��X�V
	UpdateMove();

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
void CPlayer::RenderDebug(float wx,float wy)
{
	//�u�W�����v�v���\
	if (possibleToJumpFlg)
	{
		CGraphicsUtilities::RenderString(200, 10, MOF_COLOR_BLACK, "<�W�����v�\>");
	}

	//�u�G�T��H�ׂ�v���\
	if (possibleToEatFlg)
	{
		CGraphicsUtilities::RenderString(200, 10, MOF_COLOR_BLACK, "<�H�ׂ�>");
	}

	//�v���C���[�̍��W
	CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "X���W : %d", GetPosX());
	CGraphicsUtilities::RenderString(10, 40, MOF_COLOR_BLACK, "Y���W : %d", GetPosY());

	//�{�̂̓����蔻��̕`��
	CGraphicsUtilities::RenderRect(
		GetRect().Left - wx,
		GetRect().Top - wy,
		GetRect().Right - wx,
		GetRect().Bottom - wy,
		MOF_COLOR_GREEN);

	//�G�T�T�m�͈͂̕`��
	CGraphicsUtilities::RenderRect(
		GetSearchRect().Left - wx,
		GetSearchRect().Top - wy,
		GetSearchRect().Right - wx,
		GetSearchRect().Bottom - wy,
		MOF_COLOR_GREEN);

	//�̉�
	CGraphicsUtilities::RenderString(10, 70, MOF_COLOR_BLACK, "�̉� : %d", GetTemperature());
	//�񐶒�
	CGraphicsUtilities::RenderString(10, 100, MOF_COLOR_BLACK, "�񐶒� : %d / %d", GetParasite(),PARASITE_LIMIT / 50);
	//������
	CGraphicsUtilities::RenderString(10, 130, MOF_COLOR_BLACK, "�󕠓x : %d / %d", GetHungry(),FULL_STOMACH);
	//����
	switch (causeOfDeath)
	{
		case CAUSE_None:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : �Ȃ�(������)");
			break;
		case CAUSE_Hyperthermia:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : �M����");
			break;
		case CAUSE_Frozen:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : ����");
			break;
		case CAUSE_Starvation:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : �쎀");
			break;
		case CAUSE_ChokeOnShell:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : �A�܂�");
			break;
		case CAUSE_Obesity:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : �얞");
			break;
		case CAUSE_Obstacle:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : ��Q���ɏՓ�");
			break;
		case CAUSE_Jump:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : �W�����v�̏Ռ�");
			break;
		case CAUSE_Parasite:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : �񐶒�");
			break;
		case CAUSE_Bubble:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : �A");
			break;
		case CAUSE_SeaTurtle:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : �E�~�K���V���b�N");
			break;
	}

	//�i�񂾋���
	CGraphicsUtilities::RenderString(10, 190, MOF_COLOR_BLACK, "%d m", GetDistance());
	
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
				if (causeOfDeath == CAUSE_None)
				{
					//�����F�V���b�N��
					//�����������_�ő���
					deadFlg = true;
					causeOfDeath = CAUSE_SeaTurtle;
				}
				break;
			//�A
			case 1:
				ene.SetShow(false);
				if (causeOfDeath == CAUSE_None)
				{
					//�A��
					//5%�Ŏ���
					deadFlg = DieInPercentage(5);
					if (deadFlg)
						causeOfDeath = CAUSE_Bubble;
				}
				break;
			//��Q��
			case 2:
				ene.SetShow(false);
				if (causeOfDeath == CAUSE_None)
				{
					//�����F�Փˎ�
					//20%�Ŏ���
					deadFlg = DieInPercentage(20);
					if (deadFlg)
						causeOfDeath = CAUSE_Obstacle;
				}
				break;
			//����
			case 3:
				ene.SetShow(false);
				//���x����{��
				moveSpeed = 2.0f;
				//�������Ԃ̐ݒ�
				streamTime = STREAM;
				break;

		}

	}

	//�G�T�ł���Ȃ��
	if (ene.GetType() == 4)
	{
		//�G�T�Ƃ̓����蔻��(�G�T�p�̃N���X������Ȃ�A�V����CollsionItem()�Ƃ�������Ă����Ɉڂ�)
		prec = GetSearchRect();
		if (prec.CollisionRect(erec))
		{
			//�T�m�͈͓��ɃG�T������ꍇtrue
			possibleToEatFlg = true;

			//�G�T��H�ׂ�
			ene.SetShow(Eat());
		}
		else
		{
			//�T�m�͈͓��ɃG�T���Ȃ��ꍇfalse
			possibleToEatFlg = false;
		}
	}

}
