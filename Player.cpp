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
	//�m���̂��߂Ɏg���ϐ��̏�����
	random.SetSeed(time(NULL));

	/********
	* �����l
	*********/
	//���W
	posX = 200;   // 200�͓K���@���u��
	posY = g_pGraphics->GetTargetHeight() * 0.5 - texture.GetHeight() * 0.5;
	//���(�X�e�[�^�X)
	temperature = TEMPERATURE_LIMIT * 0.5;
	bodyTemp = 10;
	tempRegion = 245;
	hungry = FULL_STOMACH;
	hungerRegion = 40;
	parasite = 0;
	moveX = 0.0f;
	moveY = 0.0f;
	moveSpeed = 1.0f;
	causeOfDeath = CAUSE_None;
	//�^�C�}�[
	hungryTime = HUNGRY_SPEED;
	waterFlowTimer.SetTotalTime(4);

	//�t���O
	jumpFlg = false;
	deadFlg = false;
	possibleToEatFlg = false;
	possibleToJumpFlg = false;
	waterFlowFlg = false;
	//�A���Փ˂������
	hitFlg = false;
	hitTimer.SetTotalTime(1);

	//UI�^�C�}�[
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);
}

//�ړ�
void CPlayer::UpdateMove()
{

	//�E�Ɉړ�
	if (g_pInput->IsKeyHold(MOFKEY_D) || moveSpeed > 1.0)
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
			if (/*hungry == FULL_STOMACH*/
				hungerRegion == 40)
			{
				deadFlg = true;
				causeOfDeath = CAUSE_Obesity;
				//�G�T��H�ׂ����Ƃ�Ԃ�
				return true;
			}
		}

		//�󕠂𖞂���
		hungerRegion -= 24;
		//�����l�𒴂�����
		if (hungerRegion < 40)
		{
			hungerRegion = 40;
		}


		if (causeOfDeath == CAUSE_None)
		{
			//�����F�A�܂�
			//20%�Ŏ���
			deadFlg = DieInPercentage(20);
			if (deadFlg)
				causeOfDeath = CAUSE_ChokeOnShell;
		}

		//�G�T��H�ׂ����Ƃ�Ԃ�
		return true;
	}

	return false;
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
			moveY = PLAYER_MAXSPEED;
			moveX = PLAYER_MAXSPEED;
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
	if (jumpFlg)
	{
		posY += moveY;
	}
	else {
		posY += moveY * moveSpeed;
	}



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
		tempTimer.StartTimer();
		if (tempTimer.GetNowtime() <= 0)
		{
			if (bodyTemp < 50)
			{
				bodyTemp += TEMPERATURE_SPEED;
				tempRegion -= 4.1 * TEMPERATURE_SPEED;
				tempTimer.SetTotalTime(1);
			}
		}
		//�����F�M����
		if (bodyTemp >= 50)
		{
			deadFlg = true;
			causeOfDeath = CAUSE_Hyperthermia;
		}
	}
	else if (GetRect().Top > UNDER_SEA - TEMPERATURE_CHANGEZONE)
	{
		tempTimer.StartTimer();
		if (tempTimer.GetNowtime() <= 0)
		{
			if (bodyTemp > -30)
			{
				bodyTemp -= TEMPERATURE_SPEED;
				tempRegion += 4.1 * TEMPERATURE_SPEED;
				tempTimer.SetTotalTime(1);
			}
		}
		//�����F����
		if (bodyTemp <= -30)
		{
			if (bodyTemp > -30)
			{
				deadFlg = true;
				causeOfDeath = CAUSE_Frozen;
			}
		}

	}
	else
	{
		if (bodyTemp > 10)
		{
			//�^�C�}�[�Z�b�g
			tempTimer.StartTimer();
			if (tempTimer.GetNowtime() <= 0)
			{
				bodyTemp -= TEMPERATURE_SPEED;
				tempRegion += 4.1 * TEMPERATURE_SPEED;
				tempTimer.SetTotalTime(2);
			}
		}
		else if (bodyTemp < 10)
		{
			//�^�C�}�[�Z�b�g
			tempTimer.StartTimer();
			if (tempTimer.GetNowtime() <= 0)
			{
				bodyTemp += TEMPERATURE_SPEED;
				tempRegion -= 4.1 * TEMPERATURE_SPEED;
				tempTimer.SetTotalTime(2);
			}
		}

	}


	/*********
	 * �񐶒�
	 *********/
	if (parasite < 5)
	{
		//�^�C�}�[�Z�b�g
		parasiteTimer.StartTimer();
		if (parasiteTimer.GetNowtime() <= 0)
		{
			parasite += 1;
			if (parasite == 5)
			{
				if (causeOfDeath == CAUSE_None)
				{
					//�����F�񐶎�
					deadFlg = true;
					causeOfDeath = CAUSE_Parasite;
				}
			}
			parasiteTimer.SetTotalTime(15);
		}
	}

	/*********
	 * ��
	 *********/
	hungerTimer.StartTimer();
	if (hungerTimer.GetNowtime() <= 0)
	{
		if (hungerRegion <= 148)
		{
			hungerRegion += 12;
			//hungry -= 1;
			if (/*hungry == 0*/
				hungerRegion >= 160)
			{
				if (causeOfDeath == CAUSE_None)
				{
					//�����F�쎀
					deadFlg = true;
					causeOfDeath = CAUSE_Starvation;
				}
			}
			hungerTimer.SetTotalTime(3);
		}
	}

	//����
	if (waterFlowFlg)
	{
		waterFlowTimer.StartTimer();
		if (waterFlowTimer.GetNowtime() <= 0)
		{
			if (moveSpeed <= 1.0f)
			{
				waterFlowTimer.StopTimer();
				moveSpeed = 1.0f;
				waterFlowFlg = false;
			}
			else
			{
				moveSpeed -= WATERFLOW_SPEED;
			}

		}
		else if (WATERFLOW_MAXSPEED <= moveSpeed)
		{
			moveSpeed = WATERFLOW_MAXSPEED;
		}
		else
		{
			moveSpeed += WATERFLOW_SPEED;
		}
	}
}

//�X�V
void CPlayer::Update()
{
	//�v���C���[������ł���ꍇ
	if (deadFlg && !jumpFlg)
		return;

	//�X�e�[�^�X(���)�̍X�V
	UpdateStatus();

	//�W�����v
	Jump();

	tempTimer.Update();
	hungerTimer.Update();
	parasiteTimer.Update();

	waterFlowTimer.Update();
	hitTimer.Update();


	//���G(�f�o�b�O�p)
	if (hitFlg)
	{
		hitTimer.StartTimer();
		//���G�̉���
		if (g_pInput->IsKeyPush(MOFKEY_H) ||
			hitTimer.GetNowtime() <= 0)
		{
			hitTimer.StopTimer();
			hitFlg = false;
		}
	}

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
	if (deadFlg && !jumpFlg)
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
		CGraphicsUtilities::RenderString(200, 40, MOF_COLOR_BLACK, "<�H�ׂ�\>");
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

	//�ڂ̓����蔻��̕`��
	CGraphicsUtilities::RenderRect(
		GetEyeRect().Left - wx,
		GetEyeRect().Top - wy,
		GetEyeRect().Right - wx,
		GetEyeRect().Bottom - wy,
		MOF_COLOR_GREEN);

	//�̉�
	CGraphicsUtilities::RenderString(10, 70, MOF_COLOR_BLACK, "�̉� : %d", GetBodyTemp());
	//�񐶒�
	CGraphicsUtilities::RenderString(10, 100, MOF_COLOR_BLACK, "�񐶒� : %d / 5", parasite);
	//������
	CGraphicsUtilities::RenderString(10, 130, MOF_COLOR_BLACK, "�󕠓x : %d / %d",(GetHungry() - 40) / 12, 10);
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
	
	//���G(�f�o�b�O�p)
	CGraphicsUtilities::RenderString(10, 220, MOF_COLOR_BLACK, "�uH�v�Ŗ��G�̉���(���C��A�̏�ŘA�ł���Ɗm���Ŏ��˂�)");
	if(hitFlg)
		CGraphicsUtilities::RenderString(10, 250, MOF_COLOR_BLACK, "���G");
}

//���
void CPlayer::Release()
{
	texture.Release();
}


//�G(��Q���A�G�T�A�E�~�K���A�A�A����)�Ƃ̓����蔻��
void CPlayer::Collision(CObstacleManager& cObstacle, int num)
{
	//SetShow������Ύ�������
	/*if (!cObstacle.getshow())
	{
		return;
	}*/

	if (deadFlg && !jumpFlg)
	{
		return;
	}

	//�G�̋�`�Ǝ����̋�`�œ����蔻��
	CRectangle prec = GetRect();

	//�E�~�K��
	if (prec.CollisionRect(cObstacle.GetRect(Turtle, num)) &&
		cObstacle.GetShow(Turtle, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None)
		{
			//�f�o�b�O�p
			hitFlg = true;
			//hitTimer.SetTotalTime(1);

			//�����F�V���b�N��
			//�����������_�ő���
			deadFlg = true;
			causeOfDeath = CAUSE_SeaTurtle;
		}
	}
	//��Q��
	else if (prec.CollisionRect(cObstacle.GetRect(Garbage, num)) &&
		cObstacle.GetShow(Garbage, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None)
		{
			//�f�o�b�O�p
			hitFlg = true;
			hitTimer.SetTotalTime(1);

			//�����F�Փˎ�
			//20%�Ŏ���
			deadFlg = DieInPercentage(20);
			if (deadFlg)
				causeOfDeath = CAUSE_Obstacle;
		}
	}
	//����
	else if (prec.CollisionRect(cObstacle.GetRect(WaterFlow, num)) &&
		cObstacle.GetShow(WaterFlow, num))
	{
		//�����ɓ����������Ƃ��m�F
		waterFlowFlg = true;
		//�������Ԃ̐ݒ�
		waterFlowTimer.SetTotalTime(4);
	}

	//�A�p�̖ڂ̓����蔻��
	prec = GetEyeRect();
	//�A
	if (prec.CollisionRect(cObstacle.GetRect(Bubble, num)) &&
		cObstacle.GetShow(Bubble, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None)
		{
			//�f�o�b�O�p
			hitFlg = true;
			hitTimer.SetTotalTime(1);

			//�A��
			//5%�Ŏ���
			deadFlg = DieInPercentage(5);
			if (deadFlg)
				causeOfDeath = CAUSE_Bubble;
		}
	}


	//�G�T�̒T�m�͈�
	prec = GetSearchRect();
	//�G�T
	if (prec.CollisionRect(cObstacle.GetRect(FoodFish, num)) &&
		cObstacle.GetShow(FoodFish, num))
	{
		//�T�m�͈͓��ɃG�T������ꍇtrue
		possibleToEatFlg = true;
		//�G�T��H�ׂ�
		if (Eat())
		{
			cObstacle.SetShow(false, FoodFish, num);
		}
	}
	else if (prec.CollisionRect(cObstacle.GetRect(FoodShrimp, num)) &&
		cObstacle.GetShow(FoodShrimp, num))
	{
		//�T�m�͈͓��ɃG�T������ꍇtrue
		possibleToEatFlg = true;
		//�G�T��H�ׂ�
		if (Eat())
		{
			cObstacle.SetShow(false, FoodShrimp, num);
		}
	}
	else if (prec.CollisionRect(cObstacle.GetRect(FoodCrab, num)) &&
		cObstacle.GetShow(FoodCrab, num))
	{
		//�T�m�͈͓��ɃG�T������ꍇtrue
		possibleToEatFlg = true;
		//�G�T��H�ׂ�
		if (Eat())
		{
			cObstacle.SetShow(false, FoodCrab, num);
		}
	}
	else
	{
		//�T�m�͈͓��ɃG�T���Ȃ��ꍇfalse
		possibleToEatFlg = false;
	}

}
