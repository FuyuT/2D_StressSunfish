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
	if (!cFishShadow.Load())return false;
	TextLoad(obstacleDistance, turtleRate, garbageRate, waterFlowRate, bubbleRate, shoalSardineRate, tunaRate, swordFishRate, safeFoodDistance, dangerFoodDistance);
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
	cFishShadow.Initialize();

	obstacleRandom.SetSeed((MofU32)time(NULL));
	posYRandom.SetSeed((MofU32)time(NULL));

	lastTimePosY = 0;
}

void CObstacleManager::Update(int distance,int posx,float wx,float wy, int tutorialStep, int eventNum)
{
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

	ObstacleGenerate(distance,obstacleFlg,eventNum,posx);
	SafeFoodGenerate(distance, foodFlg, eventNum, posx);
	DangerFoodGenerate(distance, rottenFlg, eventNum, posx);

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
		cSwordFish[n].Update(wx, wy);
		cSchoolTuna[n].Update(wx, wy);
	}
	cWaterFlow.Update(wx, wy);
	cFishShadow.Update(wx, wy);
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
	cFishShadow .Render(wx, wy);

	//�m�F�f�o�b�O�p
	//CGraphicsUtilities::RenderString(10, 100, gFileBuffer);
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
	cFishShadow.RenderDebug(wx, wy);
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
	cFishShadow.Release();

}

void CObstacleManager::PosYRandom(int obstacleType)
{	
	if (obstacleType = Food)
	{
		posYNum = posYRandom.Random(2, 5);
	}
	else if (obstacleType = SummerFood)
	{
		posYNum = posYRandom.Random(3, 5);
	}
	else if (obstacleType = WinterFood)
	{
		posYNum = posYRandom.Random(2, 4);
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

bool CObstacleManager::TextLoad(int& obstacleDistance,int& turtleRate, int& garbageRate, int& waterFlowRate, int& bubbleRate, int& shoalSardineRate, int& tunaRate, int& swordFishRate, int& safeFoodDistance, int& dangerFoodDistance)
{
	FILE* fp = fopen("Text\\RandomObstacle.txt", "rt");
	if (fp == NULL)
		return false;
	//�t�@�C���̗e�ʊm�F
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�������m�ہ@�o�b�t�@�ɓǂݍ���
	char* gFileBuffer = (char*)malloc(fSize + 1);

	fSize = fread(gFileBuffer, 1, fSize, fp);
	gFileBuffer[fSize] = '\0';

	//�f�[�^�̓ǂݍ���
	//��Q��
	//�o���Ԋu
	strtok(gFileBuffer, "=");
	obstacleDistance = atoi(strtok(NULL, ","));
	//�T
	strtok(NULL, "=");
	turtleRate = atoi(strtok(NULL, ","));
	//�S�~
	strtok(NULL, "=");
	garbageRate = atoi(strtok(NULL, ",")) + turtleRate;
	//����
	strtok(NULL, "=");
	waterFlowRate = atoi(strtok(NULL, ",")) + garbageRate;
	//�A
	strtok(NULL, "=");
	bubbleRate = atoi(strtok(NULL, ",")) + waterFlowRate;
	//���Q
	strtok(NULL, "=");
	shoalSardineRate = atoi(strtok(NULL, ",")) + bubbleRate;
	//�}�O��
	strtok(NULL, "=");
	tunaRate = atoi(strtok(NULL, ",")) + shoalSardineRate;
	//�J�W�L
	strtok(NULL, "=");
	swordFishRate = atoi(strtok(NULL, ",")) + tunaRate;

	//���S�ȐH�ו�
	strtok(NULL, "=");
	safeFoodDistance = atoi(strtok(NULL, ","));

	//�댯�ȐH�ו�
	strtok(NULL, "=");
	dangerFoodDistance = atoi(strtok(NULL, ","));

	fclose(fp);
	return true;
}

void CObstacleManager::ObstacleGenerate(int distance, bool obstacleFlg, int eventNum, int posx)
{
	//showFlg��false�̏�Q����������_���őI��ŁA
	if (distance % obstacleDistance == 0 && distance != 0 && obstacleFlg)
	{
		obstacleNum = obstacleRandom.Random(0, 1000);

		if (eventNum == Event_Turtle)
			obstacleNum = turtleRate - 1;
		else if (eventNum == Event_ShoalSardine)
			obstacleNum = shoalSardineRate - 1;
		else if (eventNum == Event_Garbage)
			obstacleNum = garbageRate - 1;

		//�����_���ŏo�������ɂ����if���ŏ�Q����\������
		if (obstacleNum < turtleRate)
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
					PosYRandom(Obstacle);
					cTurtle[n].SetPosy(posY);
					if (eventNum == 3)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(Turtle, n);
					return;
				}
			}
		}
		else if (obstacleNum >= turtleRate && obstacleNum < garbageRate)
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
					PosYRandom(Obstacle);
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
		else if (obstacleNum >= garbageRate && obstacleNum < waterFlowRate)
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
						PosYRandom(Obstacle);
						cWaterFlow.SetPosy(posY);
						return;
					}
					return;
				}
			}
			else if (obstacleNum >= waterFlowRate && obstacleNum < bubbleRate)
			{
				//�A
				for (int n = 0; n < 3; n++)
				{
					if (!cBubble[n].GetShow())
					{
						cBubble[n].SetShow(true);
						//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

						cBubble[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
						PosYRandom(Obstacle);
						cBubble[n].SetPosy(posY);
						//�d�Ȃ����ꍇ�\�����Ȃ�
						Overlap(Bubble, n);
						return;
					}
				}
			}
			else if (obstacleNum >= bubbleRate && obstacleNum < shoalSardineRate)
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
						cSound->Play(SOUND_ALERT);
						cShoalSardine[n].SetShow(true);
						//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

						cShoalSardine[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
						PosYRandom(Obstacle);
						cShoalSardine[n].SetPosy(posY);
						if (eventNum == Event_ShoalSardine)
							return;
						//�d�Ȃ����ꍇ�\�����Ȃ�
						//Overlap(ShoalSardine, n);
						return;
					}
				}
			}
			else if (obstacleNum >= shoalSardineRate && obstacleNum < tunaRate)
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
						cSound->Play(SOUND_ALERT);
						cSchoolTuna[n].SetShow(true);
						//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

						cSchoolTuna[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
						PosYRandom(Obstacle);
						cSchoolTuna[n].SetPosy(posY);
						if (eventNum == 4)
							return;
						//�d�Ȃ����ꍇ�\�����Ȃ�
						//Overlap(SchoolTuna, n);
						return;
					}
				}
			}
			else if (obstacleNum >= tunaRate && obstacleNum < swordFishRate)
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
						cSound->Play(SOUND_ALERT);
						cSwordFish[n].SetShow(true);
						//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

						cSwordFish[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
						PosYRandom(Obstacle);
						cSwordFish[n].SetPosy(posY);
						if (eventNum == 4)
							return;
						//�d�Ȃ����ꍇ�\�����Ȃ�
						//Overlap(SwordFish, n);
						return;
					}
				}
			}
		}
	}
}

void CObstacleManager::SafeFoodGenerate(int distance, bool foodFlg, int eventNum, int posx)
{
	//showFlg��false�̈��S�ȐH�ו���������_���őI��ŁA
	if (distance % safeFoodDistance == 0 && distance != 0 && foodFlg)
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
					if (eventNum = Event_Summer)
					{
						PosYRandom(SummerFood);
					}
					else if (eventNum = Event_Winter)
					{
						PosYRandom(WinterFood);
					}
					else
					{
						PosYRandom(Food);
					}
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
					if (eventNum = Event_Summer)
					{
						PosYRandom(SummerFood);
					}
					else if (eventNum = Event_Winter)
					{
						PosYRandom(WinterFood);
					}
					else
					{
						PosYRandom(Food);
					}
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
					if (eventNum = Event_Summer)
					{
						PosYRandom(SummerFood);
					}
					else if (eventNum = Event_Winter)
					{
						PosYRandom(WinterFood);
					}
					else
					{
						PosYRandom(Food);
					}
					cCrab[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(FoodCrab, n);
					return;
				}
			}
		}
	}
}

void CObstacleManager::DangerFoodGenerate(int distance, bool rottenFlg, int eventNum, int posx)
{
	//showFlg��false�̊�Ȃ��H�ו���������_���őI��ŁA
	if (distance % dangerFoodDistance == 0 && distance != 0 && rottenFlg)
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
					PosYRandom(Rotten);
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
					PosYRandom(Rotten);
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
					PosYRandom(Rotten);
					cRottenCrab[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					Overlap(RottenCrab, n);
					return;
				}
			}
		}
	}	
}