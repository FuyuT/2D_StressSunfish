#include "Player.h"

CPlayer::CPlayer() :
	standTexture(),
	random(),
	posX(0.0f),
	posY(0.0f),
	moveX(0.0f),
	moveY(0.0f),
	moveSpeed(1.0f),
	jumpFlg(false),
	jumpDangerFlg(false),
	deadFlg(false),
	possibleToJumpFlg(false),
	possibleToEatFlg(),
	causeOfDeath(0),
	hitFlg(false),
	hitTimer(),
	bodyTemp(0),
	tempRegion(0.0f),
	hungerRegion(0),
	parasite(0),
	waterFlowTimer(),
	waterFlowFlg(false),
	brakeTimer(),
	tempTimer(),
	hungerTimer(),
	parasiteTimer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	//�v���C���[�̃e�N�X�`���̓ǂ݂���
	if (!standTexture.Load("sheet_manbo si_manbo 2_stand.png"))
	{
		return false;
	}
	if (!eatTexture.Load("sheet_manbo si_manbo 2_Eat_anim.png"))
	{
		return false;
	}
	if (!deathTexture.Load("sheet_manbo si_manbo 2_Death.png"))
	{
		return false;
	}
	if (!jumpTexture.Load("sheet_manbo_manbo_jump_anime_1.png"))
	{
		return false;
	}


	return true;
}

//������
void CPlayer::Initialize()
{
	/********
	* �����l
	*********/
	//�m��
	random.SetSeed(time(NULL));
	//���W
	posX = STARTPOS_X;
	posY = STARTPOS_Y;
	//�̉�
	bodyTemp = STANDARD_TEMPERATURE;
	tempRegion = 50;
	//�󕠓x
	hungerRegion = FULL_STOMACH;
	//�񐶒�
	parasite = 0;
	//���x
	moveX = 0.0f;
	moveY = 0.0f;
	//�W�����v
	jumpFlg = false;
	jumpDangerFlg = false;
	jumpDangerTimer.SetTotalTime(5);
	//����
	moveSpeed = 1.0f;
	waterFlowTimer.SetTotalTime(4);
	waterFlowFlg = false;
	//����
	causeOfDeath = CAUSE_None;
	//�A���Փ˂������
	hitFlg = false;
	hitTimer.SetTotalTime(1);

	//�t���O
	deadFlg = false;
	for (int i = 0; i < FEED_MAXCOUNT; i++)
	{
		possibleToEatFlg[i] = false;
	}
	possibleToJumpFlg = false;

	//UI�^�C�}�[
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);

	//�`���[�g���A��
	eatTaskFlg = false;
	jumpTaskFlg = false;
	taskCompleteStep = Task_Movement;
	moveUpTaskTimer.SetTotalTime(3);
	moveDownTaskTimer.SetTotalTime(3);

	//�u���[�L(�e�X�g)
	brakeTimer.SetTotalTime(0);

	//�A�j���[�V����
	SpriteAnimationCreate anim[] = {
		{
			"�ʏ�",
			0,0,
			166,166,
			TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
				  {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
				  {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2},{4,5,2},
				  {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
				  {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}
		},
		{
			"�H�ׂ�",
			0,0,
			166,166,
			FALSE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
				  {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
				  {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2},{4,5,2},
				  {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
				  {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}
		},
		{
			"�W�����v",
			0,0,
			166,166,
			FALSE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
				  {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
				  {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2},{4,5,2},
				  {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
				  {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}
		},
		{
			"����",
			0,0,
			166,166,
			FALSE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
				  {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
				  {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2},{4,5,2},
				  {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
				  {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}
		},
	};
	motion.Create(anim, MOTION_COUNT);

	//motion.ChangeMotion(MOTION_STAND);
}

//�ړ�
void CPlayer::UpdateMove(int tutorialStep)
{

	//�E�Ɉړ�
	/*
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
	*/

	//�u���[�L(�e�X�g)
	if (g_pInput->IsKeyPush(MOFKEY_B))
	{
		brakeTimer.SetTotalTime(0.5f);
	}

	if (brakeTimer.GetNowtime() >= 0)
	{
		brakeTimer.StartTimer();
		if (moveX < 2.0f)
		{
			moveX = 2.0f;
		}
		else
		{
			moveX -= 1.0f;
		}
	}

	//�����ŉE�ɐi�ނ悤��
	if (moveX > PLAYER_MAXSPEED)
	{
		moveX = PLAYER_MAXSPEED;
	}
	else
	{
		moveX += PLAYER_SPEED;
	}

	//�`���[�g���A���p���͌��m
	if (tutorialStep == Task_Movement)
	{
		if (g_pInput->IsKeyPush(MOFKEY_W))
		{
			moveUpTaskTimer.StartTimer();
		}
		else if (g_pInput->IsKeyPull(MOFKEY_W))
		{
			moveUpTaskTimer.StopTimer();
		}
		if (g_pInput->IsKeyPush(MOFKEY_S))
		{
			moveDownTaskTimer.StartTimer();
		}
		else if (g_pInput->IsKeyPull(MOFKEY_S))
		{
			moveDownTaskTimer.StopTimer();
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
	if (!g_pInput->IsKeyHold(MOFKEY_W) && 
		!g_pInput->IsKeyHold(MOFKEY_S))
	{
		posY += GRAVITY;
	}

	//�C��(�X�N���[������)�@�ړ�����
	if (GetRect().Bottom > UNDER_SEA)
	{
		posY = UNDER_SEA - TEXTURE_SIZE + COLLISION_ADJUSTMENT_BOTTOM;
		moveY = 0;
	}
	
	//�C��(�X�N���[���㕔)�@�ړ�����
	if (GetRect().Top < SEA_LEVEL)
	{
		posY = SEA_LEVEL - COLLISION_ADJUSTMENT_TOP;
		moveY = 0;
	}	
}

//�G�T��H�ׂ�
bool CPlayer::Eat(bool rottenFlg, bool unDeadFlg, int tutorialStep)
{
	//�G�T��H�ׂ�
	if (g_pInput->IsKeyPush(MOFKEY_A) && tutorialStep >= Task_Action)
	{
		//�`���[�g���A���^�X�N
		eatTaskFlg = true;

		if(motion.GetMotionNo() == MOTION_STAND)
			motion.ChangeMotion(MOTION_EAT);

		for (int i = 0; i < FEED_MAXCOUNT; i++)
		{
			possibleToEatFlg[i] = false;
		}

		//�������m�肵�Ă��Ȃ�
		if (causeOfDeath == CAUSE_None && !unDeadFlg)
		{
			//�����F�얞
			if (hungerRegion <= FULL_STOMACH)
			{
				motion.ChangeMotion(MOTION_DEATH);
				causeOfDeath = CAUSE_Obesity;
				//�G�T��H�ׂ����Ƃ�Ԃ�
				return true;
			}
		}

		//�󕠂𖞂���
		hungerTimer.SetTotalTime(3);
		if(rottenFlg)
			hungerRegion -= FEED_SATIETYLEVEL;
		else
			hungerRegion -= FEED_SATIETYLEVEL / 2;

		//�����l�𒴂�����
		if (hungerRegion < FULL_STOMACH)
		{
			hungerRegion = FULL_STOMACH - 5.0f;
		}

		//�������m�肵�Ă��Ȃ�
		if (causeOfDeath == CAUSE_None && !unDeadFlg)
		{
			//�����Ă���Ίm���Ŏ���
			if (rottenFlg)
			{
				//�����F�A�܂�
				//20%�Ŏ���
				if (DieInPercentage(20))
				{
					motion.ChangeMotion(MOTION_DEATH);
					causeOfDeath = CAUSE_ChokeOnShell;
				}
			}
		}

		//�G�T��H�ׂ����Ƃ�Ԃ�
		return true;
	}

	return false;
}

//�W�����v
void CPlayer::Jump(bool unDeadFlg, int tutorialStep)
{
	//�C�ʂɋ߂��Ƃ�(�W�����v�\�ł����) �� A ������
	if (g_pInput->IsKeyPush(MOFKEY_A) &&
		possibleToJumpFlg && tutorialStep >= Task_Action)
	{
		//�`���[�g���A���^�X�N
		jumpTaskFlg = true;

		jumpFlg = true;	
		possibleToJumpFlg = false;

		motion.ChangeMotion(MOTION_JUMP);

		//�W�����v��
		moveY = -JUMP_POWER_Y;
		moveX = JUMP_POWER_X;

	}
	else if (jumpFlg)
	{
		moveY += PLAYER_SPEED;
		//�C�ʂ�艺��(�C�ɖ߂�����)
		//�����ɂ�鐨���ŏ�������悤��
		if (posY > SEA_LEVEL + WATER_LANDING_DEEP)
		{
			//jumpDangerTimer�̎��ԓ��ɃW�����v���s���Ǝ��S
			if (jumpDangerFlg)
			{
				//�������m�肵�Ă��Ȃ�
				if (causeOfDeath == CAUSE_None && !unDeadFlg)
				{
					motion.ChangeMotion(MOTION_DEATH);
					causeOfDeath = CAUSE_Jump;
				}
			}
			else
			{
				jumpDangerFlg = true;
				jumpDangerTimer.SetTotalTime(5);
				jumpDangerTimer.StartTimer();
			}
			//�񐶒���U�藎�Ƃ�
			parasiteTimer.SetTotalTime(15);
			parasite = 0;

			//������ɐ�������������
			moveY = PLAYER_MAXSPEED;
			moveX = PLAYER_MAXSPEED;

			jumpFlg = false;

		}
	}


}

//�v���C���[�̏�Ԃ��X�V
void CPlayer::UpdateStatus(bool unDeadFlg, int tutorialStep, int eventNum)
{

	if (motion.GetMotionNo() != MOTION_STAND &&
		motion.IsEndMotion())
	{
		motion.ChangeMotion(MOTION_STAND);
	}

	//���x�����W�ɔ��f
	posX += moveX * moveSpeed;
	//�W�����v�̍����ɂ͐����ɂ�鑬�xup������Ȃ��悤��
	if (jumpFlg)
	{
		posY += moveY;
	}
	else
	{
		posY += moveY * moveSpeed;
	}

	//�W�����v�\
	//�C�ʂ���ǂ��܂ł��W�����v�\�͈͂�
	if (GetRect().Top < SEA_LEVEL + JUMP_ZONE && !jumpFlg)
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
	if (!jumpFlg && tutorialStep >= Task_End)
	{
		if (GetRect().Top < SEA_LEVEL + TEMPERATURE_CHANGEZONE)
		{
			if (tempRegion > HYPERTHERMIA_LIMIT)
			{
				if(eventNum == 1)
					tempRegion -= TEMPERATURE_LEVEL * 2;
				else
					tempRegion -= TEMPERATURE_LEVEL;
			}			
		}
		else if (GetRect().Top > UNDER_SEA - TEMPERATURE_CHANGEZONE)
		{
			if (tempRegion < FROZEN_LIMIT)
			{
				if(eventNum == 2)
					tempRegion += TEMPERATURE_LEVEL * 2;
				else
					tempRegion += TEMPERATURE_LEVEL;
			}
		}
		else
		{
			if(eventNum == 1)
				tempRegion -= TEMPERATURE_LEVEL * 2;
			else if(eventNum == 2)
				tempRegion += TEMPERATURE_LEVEL * 2;
			else
			{
				if (tempRegion < (FROZEN_LIMIT + HYPERTHERMIA_LIMIT) / 2)
				{
					tempRegion += TEMPERATURE_LEVEL / 3.0f;
				}
				else if (tempRegion > (FROZEN_LIMIT + HYPERTHERMIA_LIMIT) / 2)
				{
					tempRegion -= TEMPERATURE_LEVEL / 3.0f;
				}
			}
		}
	}

	if (causeOfDeath == CAUSE_None && !unDeadFlg)
	{
		//�����F�M����
		if (tempRegion <= HYPERTHERMIA_LIMIT)
		{
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_Hyperthermia;
		}
		//�����F����
		if (tempRegion >= FROZEN_LIMIT)
		{
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_Frozen;
		}
	}


	/*********
	 * �񐶒�
	 *********/
	if (!jumpFlg && tutorialStep >= Task_Action)
	{
		if (parasite < PARASITE_LIMIT)
		{
			//�^�C�}�[�Z�b�g
			parasiteTimer.StartTimer();
			if (parasiteTimer.GetNowtime() <= 0)
			{
				parasite += 1;
				if (causeOfDeath == CAUSE_None && !unDeadFlg)
				{
					if (parasite == PARASITE_LIMIT)
					{
						//�����F�񐶎�
						motion.ChangeMotion(MOTION_DEATH);
						causeOfDeath = CAUSE_Parasite;
					}
				}
				parasiteTimer.SetTotalTime(15);
			}
		}
	}

	/*********
	 * ��
	 *********/
	if (tutorialStep >= Task_Action)
	{
		if (hungerRegion <= STARVATION)
		{
			hungerRegion += HUNGRYLEVEL;
		}
		else if (hungerRegion >= STARVATION)
		{
			if (causeOfDeath == CAUSE_None)
			{
				if (causeOfDeath == CAUSE_None && !unDeadFlg)
				{
					if (causeOfDeath == CAUSE_None && !unDeadFlg)
					{
						//�����F�쎀
						motion.ChangeMotion(MOTION_DEATH);
						causeOfDeath = CAUSE_Starvation;
					}
				}
			}
		}
	}
	

	/*********
	*  ����
	**********/
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
			else if(!jumpFlg)
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

	//���G
	if (hitFlg)
	{
		hitTimer.StartTimer();
		//���G�̉���
		if (hitTimer.GetNowtime() <= 0)
		{
			hitTimer.StopTimer();
			hitFlg = false;
		}
	}
}

//�X�V
void CPlayer::Update(bool unDeadFlg, int tutorialStep,int eventNum)
{
	//�A�j���[�V�����̍X�V
	motion.AddTimer(CUtilities::GetFrameSecond());

	//���S�A�j���[�V�������I��莟��Adeadflg��true�ɂ���
	if (motion.GetMotionNo() == MOTION_DEATH)
	{
		if (motion.IsEndMotion())
		{
			deadFlg = true;
		}
	}

	//�v���C���[������ł���ꍇ�A���삪�s���Ȃ��悤��
	if ((deadFlg || motion.GetMotionNo() == MOTION_DEATH) && !jumpFlg)
		return;

	//�X�e�[�^�X(���)�̍X�V
	UpdateStatus(unDeadFlg,tutorialStep,eventNum);

	//�W�����v
	Jump(unDeadFlg,tutorialStep);

	//�^�C�}�[
	tempTimer.Update();
	hungerTimer.Update();
	parasiteTimer.Update();
	waterFlowTimer.Update();
	hitTimer.Update();
	brakeTimer.Update();
	if (!jumpFlg) jumpDangerTimer.Update();
	if (!jumpDangerTimer.GetUpdateFlg()) jumpDangerFlg = false;

	moveUpTaskTimer.Update();
	moveDownTaskTimer.Update();

	//�`���[�g���A��
	if (GetMoveUpTask() && GetMoveDownTask() && taskCompleteStep == Task_Movement)
	{
		taskCompleteStep = Task_Action;
	}
	else if (eatTaskFlg && jumpTaskFlg && taskCompleteStep == Task_Action)
	{
		taskCompleteStep = Task_Complete;
	}

	//�W�����v���͑��삪�s���Ȃ��悤��
	if (jumpFlg)
		return;

	//�ړ��X�V
	UpdateMove(tutorialStep);

}

//�`��
void CPlayer::Render(float wx, float wy)
{
	//�v���C���[������ł���ꍇ
	if (deadFlg && !jumpFlg)
		return;

	//�v���C���[�̕`��
	switch (motion.GetMotionNo())
	{
		case MOTION_STAND:
			standTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());
			break;
		case MOTION_EAT:
			eatTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());
			break;
		case MOTION_JUMP:
			jumpTexture.RenderScale(posX - wx, posY - wy, 1.8f, motion.GetSrcRect());
			break;
		case MOTION_DEATH:
			deathTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());
			break;
	}
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
	if (GetEat())
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
		case CAUSE_WaterFlow:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "���� : ������");
			break;
	}

	//�i�񂾋���
	CGraphicsUtilities::RenderString(10, 190, MOF_COLOR_BLACK, "%d m", GetDistance());
	
	//���G(�f�o�b�O�p)
	if(hitFlg)
		CGraphicsUtilities::RenderString(10, 220, MOF_COLOR_BLACK, "���G");
}

//���
void CPlayer::Release()
{
	standTexture.Release();
	eatTexture.Release();
	jumpTexture.Release();
	deathTexture.Release();

	motion.Release();
}


//�G(��Q���A�G�T�A�E�~�K���A�A�A����)�Ƃ̓����蔻��
void CPlayer::Collision(CObstacleManager& cObstacle, int num, bool unDeadFlg, int tutorialStep)
{

	if ((deadFlg || motion.GetMotionNo() == MOTION_DEATH) && !jumpFlg)
	{
		return;
	}

	//�G�̋�`�Ǝ����̋�`�œ����蔻��
	CRectangle prec = GetRect();

	//�E�~�K��
	if (prec.CollisionRect(cObstacle.GetRect(Turtle, num)) &&
		cObstacle.GetShow(Turtle, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None && !unDeadFlg)
		{
			//�Փ�
			hitFlg = true;

			//�����F�V���b�N��
			//�����������_�ő���
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_SeaTurtle;
		}
	}
	//��ʓ���4�̖ځA5�Ζڂ��o�Ă���͍̂��̂Ƃ���E�~�K�������̂��߁A������؂�グ��
	if (num == 3 || num == 4)
	{
		return;
	}

	//���Q�͍ő�ł���̂܂ł����o�Ȃ�
	if (num != 2)
	{
		//todo:��������Q���ƏՓ˂ɂ��Ă�̂ŁA���ƂŕύX
		//���Q�i�C���V�j
		if (prec.CollisionRect(cObstacle.GetRect(ShoalSardine, num)) &&
			cObstacle.GetShow(ShoalSardine, num) && !hitFlg)
		{
			if (causeOfDeath == CAUSE_None && !unDeadFlg)
			{
				//�Փ�
				hitFlg = true;
				//�����F�Փˎ�
				motion.ChangeMotion(MOTION_DEATH);
				causeOfDeath = CAUSE_ShoalFish;
			}
		}
		else if (prec.CollisionRect(cObstacle.GetRect(SwordFish, num)) &&
			cObstacle.GetShow(SwordFish, num) && !hitFlg)
		{
			if (causeOfDeath == CAUSE_None && !unDeadFlg)
			{
				//�Փ�
				hitFlg = true;
				//�����F�Փˎ�
				motion.ChangeMotion(MOTION_DEATH);
				causeOfDeath = CAUSE_ShoalFish;
			}
		}
		else if (prec.CollisionRect(cObstacle.GetRect(SchoolTuna, num)) &&
			cObstacle.GetShow(SchoolTuna, num) && !hitFlg)
		{
			if (causeOfDeath == CAUSE_None && !unDeadFlg)
			{
				//�Փ�
				hitFlg = true;
				//�����F�Փˎ�
				motion.ChangeMotion(MOTION_DEATH);
				causeOfDeath = SchoolTuna;
			}
		}

	}

	//��Q��
	if (prec.CollisionRect(cObstacle.GetRect(Garbage, num)) &&
		cObstacle.GetShow(Garbage, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None && !unDeadFlg)
		{
			//�Փ�
			hitFlg = true;
			//�����F�Փˎ�
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_Obstacle;
		}
	}
	//����
	else if (prec.CollisionRect(cObstacle.GetRect(WaterFlow, num)) &&
		cObstacle.GetShow(WaterFlow, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None && !waterFlowFlg && !unDeadFlg)
		{
			//�����ɓ����������Ƃ��m�F
			waterFlowFlg = true;
			//�������Ԃ̐ݒ�
			waterFlowTimer.SetTotalTime(4);
			hitFlg = true;
			hitTimer.SetTotalTime(2);
		}
		else
		{
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_WaterFlow;
		}
		
	}

	//�A�p�̖ڂ̓����蔻��
	prec = GetEyeRect();
	//�A
	if (prec.CollisionRect(cObstacle.GetRect(Bubble, num)) &&
		cObstacle.GetShow(Bubble, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None && !unDeadFlg)
		{
			//�Փ�
			hitFlg = true;
			//�A��
			motion.ChangeMotion(MOTION_DEATH);
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
		possibleToEatFlg[num] = true;
		//�G�T��H�ׂ�
		if (Eat(false,unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, FoodFish, num);
		}
	}
	else if (prec.CollisionRect(cObstacle.GetRect(FoodShrimp, num)) &&
		cObstacle.GetShow(FoodShrimp, num))
	{
		//�T�m�͈͓��ɃG�T������ꍇtrue
		possibleToEatFlg[num] = true;
		//�G�T��H�ׂ�
		if (Eat(false, unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, FoodShrimp, num);
		}
	}
	else if (prec.CollisionRect(cObstacle.GetRect(FoodCrab, num)) &&
		cObstacle.GetShow(FoodCrab, num))
	{
		//�T�m�͈͓��ɃG�T������ꍇtrue
		possibleToEatFlg[num] = true;
		//�G�T��H�ׂ�
		if (Eat(false, unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, FoodCrab, num);
		}
	}
	//�������G�T
	else if (prec.CollisionRect(cObstacle.GetRect(RottenFish, num)) &&
		cObstacle.GetShow(RottenFish, num))
	{
		//�T�m�͈͓��ɃG�T������ꍇtrue
		possibleToEatFlg[num] = true;
		//�G�T��H�ׂ�
		if (Eat(true, unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, RottenFish, num);
		}
	}
	else if (prec.CollisionRect(cObstacle.GetRect(RottenShrimp, num)) &&
		cObstacle.GetShow(RottenShrimp, num))
	{
		//�T�m�͈͓��ɃG�T������ꍇtrue
		possibleToEatFlg[num] = true;
		//�G�T��H�ׂ�
		if (Eat(true, unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, RottenShrimp, num);
		}
	}
	else if (prec.CollisionRect(cObstacle.GetRect(RottenCrab, num)) &&
		cObstacle.GetShow(RottenCrab, num))
	{
		//�T�m�͈͓��ɃG�T������ꍇtrue
		possibleToEatFlg[num] = true;
		//�G�T��H�ׂ�
		if (Eat(true, unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, RottenCrab, num);
		}
	}

	else
	{
		//�T�m�͈͓��ɃG�T���Ȃ��ꍇfalse
		possibleToEatFlg[num] = false;
	}

}
