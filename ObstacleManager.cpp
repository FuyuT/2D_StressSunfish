#include "ObstacleManager.h"
#include <time.h>

CObstacleManager::CObstacleManager()
{
}

CObstacleManager::~CObstacleManager()
{
}

bool CObstacleManager::Load()
{
	for (int n = 0; n < 3; n++)
	{
		if (!cFish[n].Load())return false;
		if (!cShrimp[n].Load())return false;
		if (!cCrab[n].Load())return false;
		if (!cGarbage[n].Load())return false;
		if (!cBubble[n].Load())return false;
		if (!cRottenFish[n].Load())return false;
		if (!cRottenCrab[n].Load())return false;
		if (!cRottenShrimp[n].Load())return false;

	}
	for (int n = 0; n < 5; n++)
	{
		if (!cTurtle[n].Load())return false;
	}
	for (int n = 0; n < 2; n++)
	{	
		if (!cShoalSardine[n].Load())return false;
		if (!cSwordFish[n].Load())return false;
		if (!cSchoolTuna[n].Load())return false;
	}
	if (!cWaterFlow.Load())return false;
	return true;
}

void CObstacleManager::Initialize()
{
	for (int n = 0; n < 3; n++)
	{
		//�H�ו�
		cFish[n].Initialize();
		cShrimp[n].Initialize();
		cCrab[n].Initialize();
		cRottenFish[n].Initialize();
		cRottenShrimp[n].Initialize();
		cRottenCrab[n].Initialize();
		//��Q��
		cGarbage[n].Initialize();
		cBubble[n].Initialize();

	}
	for (int n = 0; n < 5; n++)
	{
		cTurtle[n].Initialize();
	}
	for (int n = 0; n < 2; n++)
	{

		cShoalSardine[n].Initialize();
		cSwordFish[n].Initialize();
		cSchoolTuna[n].Initialize();
	}

	cWaterFlow.Initialize();

	obstacleRandom.SetSeed((MofU32)time(NULL));
	posYRandom.SetSeed((MofU32)time(NULL));

	lastTimePosY = 0;

	////�e�L�X�g�t�@�C�����J��
	//LoadTextFile("Text\\RandomObstacle.txt");

	////�X�N���v�g�̉�͂��s��
	//char* fb = gFileBuffer;
	//while (TRUE)
	//{
	//	//�w��̍s�̍ŏ��́C�܂ł��R�}���h�̎w��
	//	char* cmd = strtok(fb, ",");
	//	fb = NULL;
	//	if (!cmd)
	//	{
	//		break;
	//	}
	//	//�R�}���h�̑O��ɋ󔒂Ȃǂ�����Ȃ珜��������
	//	cmd = Trim(cmd);
	//	//�R�}���h�̎���
	//	int sCmd = 0;
	//	//		for(sCmd = 0;sCmd < CMD_COUNT && stricmp(cmd,gScriptCommand[sCmd]) != 0;sCmd++);
	//	for (sCmd = 0; sCmd < CMD_COUNT; sCmd++)
	//	{
	//		if (stricmp(cmd, gScriptCommand[sCmd]) == 0)
	//		{
	//			break;
	//		}
	//	}
	//	//�R�}���h�ɕK�v�ȃp�����[�^�̉��
	//	char* pstr;
	//	switch (sCmd)
	//	{
	//	case CMD_SETEASY:
	//	{
	//		SETEASYCOMMAND* pCmd = new SETEASYCOMMAND();
	//		char* pstr = strtok(NULL, ",");
	//		pCmd->obstacleInterval = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->turtleRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->garbageRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->waterFlowRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->bubbleRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->shoalSardineRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->swordFishRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->schoolTunaRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->foodInterval = atof(pstr);
	//		pstr = strtok(NULL, ";");
	//		pCmd->rottenInterval = atof(pstr);
	//		gCommandList.Add((COMMAND**)&pCmd);
	//		break;
	//	}

	//	case CMD_SETNORMAL:
	//	{
	//		SETNORMALCOMMAND* pCmd = new SETNORMALCOMMAND();
	//		char* pstr = strtok(NULL, ",");
	//		pCmd->obstacleInterval = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->turtleRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->garbageRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->waterFlowRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->bubbleRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->shoalSardineRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->swordFishRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->schoolTunaRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->foodInterval = atof(pstr);
	//		pstr = strtok(NULL, ";");
	//		pCmd->rottenInterval = atof(pstr);
	//		gCommandList.Add((COMMAND**)&pCmd);
	//		break;
	//	}

	//	case CMD_SETHARD:
	//	{
	//		SETHARDCOMMAND* pCmd = new SETHARDCOMMAND();
	//		char* pstr = strtok(NULL, ",");
	//		pCmd->obstacleInterval = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->turtleRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->garbageRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->waterFlowRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->bubbleRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->shoalSardineRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->swordFishRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->schoolTunaRate = atof(pstr);
	//		pstr = strtok(NULL, ",");
	//		pCmd->foodInterval = atof(pstr);
	//		pstr = strtok(NULL, ";");
	//		pCmd->rottenInterval = atof(pstr);
	//		gCommandList.Add((COMMAND**)&pCmd);
	//		break;
	//	}

	//	default:					//��`����Ă��Ȃ��R�}���h
	//	{
	//		char* pstr = strtok(NULL, ";");
	//		MessageBox(NULL, cmd, "�R�}���h", MB_OK);
	//		break;
	//	}
	//	}
	//}
}

void CObstacleManager::Update(int distance,int posx,float wx,float wy, int tutorialStep, int eventNum)
{
	//TextFileUpdate();

	if (tutorialStep < Task_Action)
		return;

	//�`���[�g���A��
	if (tutorialStep <= Task_Complete)
	{
		obstacleFlg = false;
		foodFlg = true;
		rottenFlg = false;
	}
	//�C�x���g
	else if (eventNum == Event_Turtle || eventNum == Event_ShoalSardine || eventNum == Event_Garbage)
	{
		eventFoodCreateFlg = ObstaclePercentage(25);
		if (eventFoodCreateFlg)
		{
			obstacleFlg = false;
			foodFlg = true;
			rottenFlg = false;
		}
		else
		{
			obstacleFlg = true;
			foodFlg = false;
			rottenFlg = false;
		}
	}
	else
	{
		obstacleFlg = true;
		foodFlg = true;
		rottenFlg = true;
	}


	//�V���������_�������̉�
	//showFlg��false�̏�Q����������_���őI��ŁA
	if (distance % 20 == 0 && distance != 0 && obstacleFlg)
	{
		obstacleNum = obstacleRandom.Random(0, 1000);

		if (eventNum == Event_Turtle)
			obstacleNum = 0;
		else if (eventNum == Event_ShoalSardine)
			obstacleNum = 400;
		else if (eventNum == Event_Garbage)
			obstacleNum = 100;

		//�����_���ŏo�������ɂ����if���ŏ�Q����\������
		if (obstacleNum < 100)
		{
			//�T
			for (int n = 0; n < 5; n++)
			{
				if (eventNum != Event_Turtle && n != 0)
				{
					return;
				}
				if (!cTurtle[n].GetShow())
				{
					if (eventNum != Event_Turtle)
					{
						createFlg = ObstaclePercentage(25);
						if (!createFlg)
							return;
					}
					cTurtle[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cTurtle[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Obstacle, eventNum);
					cTurtle[n].SetPosy(posY);
					if (eventNum == 3)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(Turtle, n);
					return;
				}
			}
		}
		else if (obstacleNum >= 100 && obstacleNum < 200)
		{
			//����
			for (int n = 0; n < 3; n++)
			{
				if (!cGarbage[n].GetShow())
				{
					if (eventNum != Event_Garbage)
					{
						createFlg = ObstaclePercentage(50);
						if (!createFlg)
							return;
					}
					PosYRandom(Obstacle, eventNum);
					if (eventNum == Event_Garbage)
					{
						if (posY == lastTimePosY)
						{
							continue;
						}
						else
						{
							lastTimePosY = posY;
						}
					}
					cGarbage[n].SetShow(true);
					//�S�~�̃����_������
					int no = garbageNoRandom.Random(GARBAGE_SHOES, GARBAGE_BAG + 1);
					cGarbage[n].SetGarbageNo(no);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cGarbage[n].SetPosx(posx + g_pGraphics->GetTargetWidth());

					cGarbage[n].SetPosy(posY);
					if (eventNum == Event_Garbage)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(Garbage, n);
					return;
				}
			}
		}
		else if (obstacleNum >= 200 && obstacleNum < 300)
		{
			//����
			if (!cWaterFlow.GetShow())
			{
				if (eventNum != Event_Turtle)
				{
					if (!cWaterFlow.GetShow())
					{
						createFlg = ObstaclePercentage(25);
						if (!createFlg)
							return;
						cWaterFlow.SetShow(true);
						//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j
			
						cWaterFlow.SetPosx(posx + g_pGraphics->GetTargetWidth());
						PosYRandom(Obstacle, eventNum);
						cWaterFlow.SetPosy(posY);
						return;
					}
					return;
				}
			}
		}
		else if (obstacleNum >= 300 && obstacleNum < 400)
		{
			//�A
			for (int n = 0; n < 3; n++)
			{
				if (!cBubble[n].GetShow())
				{
					cBubble[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cBubble[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Obstacle, eventNum);
					cBubble[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(Bubble, n);
					return;
				}
			}
		}
		else if (obstacleNum >= 400 && obstacleNum < 500)
		{
			//���Q
			for (int n = 0; n < 2; n++)
			{
				if (eventNum != Event_ShoalSardine && n != 0)
				{
					return;
				}
				if (!cShoalSardine[n].GetShow())
				{
					if (eventNum != Event_ShoalSardine)
					{
						createFlg = ObstaclePercentage(25);
						if (!createFlg)
							return;
					}
					cShoalSardine[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cShoalSardine[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
					PosYRandom(Obstacle, eventNum);
					cShoalSardine[n].SetPosy(posY);
					if (eventNum == Event_ShoalSardine)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(ShoalSardine, n);
					return;
				}
			}
		}
		else if (obstacleNum >= 500 && obstacleNum < 600)
		{
			//�J�W�L
			for (int n = 0; n < 2; n++)
			{
				if (eventNum != 4 && n != 0)
				{
					return;
				}
				if (!cSwordFish[n].GetShow())
				{
					if (eventNum != 4)
					{
						createFlg = ObstaclePercentage(25);
						if (!createFlg)
							return;
					}
					cSwordFish[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cSwordFish[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
					PosYRandom(Obstacle, eventNum);
					cSwordFish[n].SetPosy(posY);
					if (eventNum == 4)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(SwordFish, n);
					return;
				}
			}
		}
		else if (obstacleNum >= 600 && obstacleNum < 700)
		{
			//�}�O��
			for (int n = 0; n < 2; n++)
			{
				if (eventNum != 4 && n != 0)
				{
					return;
				}
				if (!cSchoolTuna[n].GetShow())
				{
					if (eventNum != 4)
					{
						createFlg = ObstaclePercentage(25);
						if (!createFlg)
							return;
					}
					cSchoolTuna[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cSchoolTuna[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
					PosYRandom(Obstacle, eventNum);
					cSchoolTuna[n].SetPosy(posY);
					if (eventNum == 4)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(SchoolTuna, n);
					return;
				}
			}
		}
	}

	//showFlg��false�̈��S�ȐH�ו���������_���őI��ŁA
	if (distance % 40 == 0 && distance != 0 && foodFlg)
	{
		foodRandom = obstacleRandom.Random(0, 300);
		//�����_���ŏo�������ɂ����if���ŐH�ו���\������
		if (foodRandom < 100)
		{
			//��
			for (int n = 0; n < 3; n++)
			{
				if (!cFish[n].GetShow())
				{
					cFish[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cFish[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Food, eventNum);
					cFish[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(FoodFish, n);
					return;
				}
			}
		}
		else if (foodRandom >= 100 && foodRandom < 200)
		{
			//�G�r
			for (int n = 0; n < 3; n++)
			{
				if (!cShrimp[n].GetShow())
				{
					cShrimp[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j
	
					cShrimp[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Food, eventNum);
					cShrimp[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(FoodShrimp, n);
					return;
				}
			}
		}
		else if (foodRandom >= 200)
		{
			//�J�j
			for (int n = 0; n < 3; n++)
			{
				if (!cCrab[n].GetShow())
				{
					cCrab[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j
		
					cCrab[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Food, eventNum);
					cCrab[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(FoodCrab, n);
					return;
				}
			}
		}
	}

	//showFlg��false�̊�Ȃ��H�ו���������_���őI��ŁA
	if (distance % 50 == 0 && distance != 0 && rottenFlg)
	{
		rottenRandom = obstacleRandom.Random(0, 300);
		//�����_���ŏo�������ɂ����if���ŕ������H�ו���\������
		if (rottenRandom < 100)
		{
			//��������
			for (int n = 0; n < 3; n++)
			{
				if (!cRottenFish[n].GetShow())
				{
					cRottenFish[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cRottenFish[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Rotten, eventNum);
					cRottenFish[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(RottenFish, n);
					return;
				}
			}
		}
		else if (rottenRandom >= 100 && rottenRandom < 200)
		{
			//�������G�r
			for (int n = 0; n < 3; n++)
			{
				if (!cRottenShrimp[n].GetShow())
				{
					cRottenShrimp[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j
		
					cRottenShrimp[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Rotten, eventNum);
					cRottenShrimp[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(RottenShrimp, n);
					return;
				}
			}
		}
		else if (rottenRandom >= 200)
		{
			//�������J�j
			for (int n = 0; n < 3; n++)
			{
				if (!cRottenCrab[n].GetShow())
				{
					cRottenCrab[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cRottenCrab[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Rotten, eventNum);
					cRottenCrab[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(RottenCrab, n);
					return;
				}
			}
		}
	}


	for (int n = 0; n < 3; n++)
	{
		//�H�ו�
		cFish[n].Update(wx, wy);
		cShrimp[n].Update(wx, wy);
		cCrab[n].Update(wx, wy);
		cRottenFish[n].Update(wx, wy);
		cRottenShrimp[n].Update(wx, wy);
		cRottenCrab[n].Update(wx, wy);
		//��Q��
		cGarbage[n].Update(wx, wy);
		cBubble[n].Update(wx, wy);
	}
	for (int n = 0; n < 5; n++)
	{
		cTurtle[n].Update(wx, wy);
	}
	for (int n = 0; n < 2; n++)
	{
		cShoalSardine[n].Update(wx, wy);
	}
		cWaterFlow.Update(wx, wy);
}


void CObstacleManager::Render(float wx, float wy)
{
	for (int n = 0; n < 3; n++)
	{
		//�H�ו�
		cFish[n].Render(wx, wy);
		cShrimp[n].Render(wx, wy);
		cCrab[n].Render(wx, wy);
		cRottenFish[n].Render(wx, wy);
		cRottenShrimp[n].Render(wx, wy);
		cRottenCrab[n].Render(wx, wy);
		//��Q��
		cGarbage[n].Render(wx, wy);
		cBubble[n].Render(wx, wy);

	}
	for (int n = 0; n < 5; n++)
	{
		cTurtle[n].Render(wx, wy);
	}
	for (int n = 0; n < 2; n++)
	{
		cShoalSardine[n].Render(wx, wy);
		cSwordFish[n].Render(wx, wy);
		cSchoolTuna[n].Render(wx, wy);
	}

	cWaterFlow.Render(wx, wy);
}

void CObstacleManager::RenderDebug(float wx, float wy)
{
	for (int n = 0; n < 3; n++)
	{
		//�H�ו�
		cFish[n].RenderDebug(wx, wy);
		cShrimp[n].RenderDebug(wx, wy);
		cCrab[n].RenderDebug(wx, wy);
		cRottenFish[n].RenderDebug(wx, wy);
		cRottenShrimp[n].RenderDebug(wx, wy);
		cRottenCrab[n].RenderDebug(wx, wy);
		//��Q��
		cGarbage[n].RenderDebug(wx, wy);
		cBubble[n].RenderDebug(wx, wy);

	}
	for (int n = 0; n < 5; n++)
	{
		cTurtle[n].RenderDebug(wx, wy);
	}
	for (int n = 0; n < 2; n++)
	{

		cShoalSardine[n].RenderDebug(wx, wy);
		cSwordFish[n].RenderDebug(wx, wy);
		cSchoolTuna[n].RenderDebug(wx, wy);
	}
	cWaterFlow.RenderDebug(wx, wy);
}

void CObstacleManager::Release()
{
	for (int n = 0; n < 3; n++)
	{
		//�H�ו�
		cFish[n].Release();
		cShrimp[n].Release();
		cCrab[n].Release();
		cRottenFish[n].Release();
		cRottenShrimp[n].Release();
		cRottenCrab[n].Release();
		//��Q��
		cGarbage[n].Release();
		cBubble[n].Release();

	}
	for (int n = 0; n < 5; n++)
	{
		cTurtle[n].Release();
	}
	for (int n = 0; n < 2; n++)
	{

		cShoalSardine[n].Release();
		cSwordFish[n].Release();
		cSchoolTuna[n].Release();
	}
	cWaterFlow.Release();
}

void CObstacleManager::PosYRandom(int obstacleType,int eventNum)
{	
	if (obstacleType = Food)
	{
		if (eventNum == Event_Summer)
		{
			posYNum = posYRandom.Random(3, 5);
		}
		else if (eventNum == Event_Winter)
		{
			posYNum = posYRandom.Random(2, 4);
		}
		else
		{
			posYNum = posYRandom.Random(2, 5);
		}
	}
	else if (obstacleType = Rotten)
	{
		posYNum = posYRandom.Random(1, 5);
	}

	switch (posYNum)
	{
	case 1:
		posY = 780;
		break;
	case 2:
		posY = 1125;
		break;
	case 3:
		posY = 1470;
		break;
	case 4:
		posY = 1815;
		break;
	case 5:
		posY = 2160;
		break;
	}
}

void CObstacleManager::Overlap(int obstacle,int arrayNum)
{
	//��Q�����d�Ȃ��Ă��邩�̔���
	for (int i = 0; i < SHOW_LIMIT; i++)
	{
		for (int m = 0; m < 3; m++)
		{
			if (GetRect(obstacle, arrayNum).CollisionRect(GetRect(i, m)))
			{
				if (i == obstacle && arrayNum == m)
				{
					continue;
				}

				switch (obstacle)
				{
				case Turtle:
					cTurtle[arrayNum].SetShow(false);
					break;
				case Garbage:
					cGarbage[arrayNum].SetShow(false);
					break;
				case WaterFlow:	//�����͍��̂Ƃ����Ȃ̂ŁA���̊֐����Ă΂Ȃ��i�ǂ񂾂�SetShow(false)�ɂ͂���j
					cWaterFlow.SetShow(false);
					break;
				case Bubble:
					cBubble[arrayNum].SetShow(false);
					break;
				case FoodFish:
					cFish[arrayNum].SetShow(false);
					break;
				case FoodShrimp:
					cShrimp[arrayNum].SetShow(false);
					break;
				case FoodCrab:
					cCrab[arrayNum].SetShow(false);
					break;
				case RottenFish:
					cRottenFish[arrayNum].SetShow(false);
					break;
				case RottenCrab:
					cRottenCrab[arrayNum].SetShow(false);
					break;
				case RottenShrimp:
					cRottenShrimp[arrayNum].SetShow(false);
					break;
				case ShoalSardine:
					cShoalSardine[arrayNum].SetShow(false);
					break;
				case SwordFish:
					cSwordFish[arrayNum].SetShow(false);
					break;
				case SchoolTuna:
					cSchoolTuna[arrayNum].SetShow(false);
					break;
				}
			}
		}
	}
}

//char* CObstacleManager::Trim(char* s)
//{
//	//�����̕����񂪂Ȃ�
//	if (!s)
//	{
//		return NULL;
//	}
//	//������̌�납��󔒈ȊO�����������̈ʒu��\0�i�I�[�j��ݒ肷��
//	int l = strlen(s);
//	while (--l >= 0)
//	{
//		if (s[l] != '\t' && s[l] != '\r' && s[l] != '\n' && s[l] != ' ')
//		{
//			break;
//		}
//	}
//	s[l + 1] = '\0';
//	//�擪����󔒈ȊO���������ʒu�̃|�C���^��Ԃ�
//	int p = 0;
//	while (p < l)
//	{
//		if (s[p] != '\t' && s[p] != '\r' && s[p] != '\n' && s[p] != ' ')
//		{
//			return &s[p];
//		}
//		p++;
//	}
//	return s;
//}
//
//bool CObstacleManager::LoadTextFile(char* pName)
//{
//	//�e�L�X�g�t�@�C�����J��
//	FILE* fp = fopen(pName, "rt");
//	if (fp == NULL)
//	{
//		return false;
//	}
//	//�t�@�C���̑S�e�ʂ𒲂ׂ�
//	//��x�t�@�C���̏I�[�Ɉړ����āA���̈ʒu�𒲂ׂ邱�ƂŃT�C�Y���킩��
//	//���׏I�������̓t�@�C���̐擪�Ɉړ����Ė߂��Ă���
//	//���������̕��@�ł�����ȃT�C�Y��ǂݍ��ނ��Ƃ͂ł��Ȃ�
//	fseek(fp, 0, SEEK_END);
//	long fSize = ftell(fp);
//	fseek(fp, 0, SEEK_SET);
//	//�t�@�C���T�C�Y�������̃��������m�ۂ���
//	//�I�[���܂߂邽�߁{�P���Ă���
//	gFileBuffer = (char*)malloc(fSize + 1);
//	//�t�@�C����S�ăo�b�t�@�ɓǂݍ���
//	//�����Ŏ��ۂɓǂݍ��߂��T�C�Y�𒲂ׂĂ��̏I�[��\0�����
//	fSize = fread(gFileBuffer, 1, fSize, fp);
//	gFileBuffer[fSize] = '\0';
//	//�t�@�C�������
//	fclose(fp);
//	return true;
//}
//
//void CObstacleManager::TextFileUpdate()
//{
//	//Enter�L�[�Ŏ��̃R�}���h�����s����
//	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
//	{
//		if (gCommandNo < gCommandList.GetArrayCount())
//		{
//			//�R�}���h�̃^�C�v�ɂ���ĕ���
//			switch (gCommandList[gCommandNo]->Type)
//			{
//			case CMD_SETEASY:
//				SETEASYCOMMAND* pSpriteCommand = (SETEASYCOMMAND*)gCommandList[gCommandNo];
//				LPSprite2D* pSprite = gSpriteList.Find(pSpriteCommand->name);
//				if (!pSprite)
//					break;
//				obstacleInterval = pSpriteCommand->obstacleInterval;
//				turtleRate = pSpriteCommand->turtleRate;
//				garbageRate = pSpriteCommand->garbageRate;
//				waterFlowRate = pSpriteCommand->waterFlowRate;
//				bubbleRate = pSpriteCommand->bubbleRate;
//				shoalSardineRate = pSpriteCommand->shoalSardineRate;
//				swordFishRate = pSpriteCommand->swordFishRate;
//				schoolTunaRate = pSpriteCommand->schoolTunaRate;
//				foodInterval = pSpriteCommand->foodInterval;
//				rottenInterval = pSpriteCommand->rottenInterval;
//				break;
//
//			case CMD_SETNORMAL:
//			{
//				SETNORMALCOMMAND* pSpriteCommand = (SETNORMALCOMMAND*)gCommandList[gCommandNo];
//				LPSprite2D* pSprite = gSpriteList.Find(pSpriteCommand->name);
//				if (!pSprite)
//					break;
//				obstacleInterval = pSpriteCommand->obstacleInterval;
//				turtleRate = pSpriteCommand->turtleRate;
//				garbageRate = pSpriteCommand->garbageRate;
//				waterFlowRate = pSpriteCommand->waterFlowRate;
//				bubbleRate = pSpriteCommand->bubbleRate;
//				shoalSardineRate = pSpriteCommand->shoalSardineRate;
//				swordFishRate = pSpriteCommand->swordFishRate;
//				schoolTunaRate = pSpriteCommand->schoolTunaRate;
//				foodInterval = pSpriteCommand->foodInterval;
//				rottenInterval = pSpriteCommand->rottenInterval;
//				break;
//			}
//
//			case CMD_SETHARD:
//			{
//				SETHARDCOMMAND* pSpriteCommand = (SETHARDCOMMAND*)gCommandList[gCommandNo];
//				LPSprite2D* pSprite = gSpriteList.Find(pSpriteCommand->name);
//				if (!pSprite)
//					break;
//				obstacleInterval = pSpriteCommand->obstacleInterval;
//				turtleRate = pSpriteCommand->turtleRate;
//				garbageRate = pSpriteCommand->garbageRate;
//				waterFlowRate = pSpriteCommand->waterFlowRate;
//				bubbleRate = pSpriteCommand->bubbleRate;
//				shoalSardineRate = pSpriteCommand->shoalSardineRate;
//				swordFishRate = pSpriteCommand->swordFishRate;
//				schoolTunaRate = pSpriteCommand->schoolTunaRate;
//				foodInterval = pSpriteCommand->foodInterval;
//				rottenInterval = pSpriteCommand->rottenInterval;
//				break;
//			}
//
//
//			default:					//��`����Ă��Ȃ��R�}���h
//				break;
//			}
//			//���̃R�}���h��
//			gCommandNo++;
//		}
//	}
//}
