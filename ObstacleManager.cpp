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
	posYRndom.SetSeed((MofU32)time(NULL));

	lastTimePosY = 0;
}

void CObstacleManager::Update(int distance,int posx,float wx,float wy, int tutorialStep, int eventNum)
{
	if (tutorialStep < Task_Action)
		return;

	//�V���������_�������̉�
	/*showFlg��false�̐H�ו�, ��Q����������_���őI��ŁA
	if (distance % 60 == 0 && distance != 0)
	{
		obstacleNum = obstacleRandom.Random(0, 700);
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
					PosYRndom();
					cTurtle[n].SetPosy(posY);
					if (eventNum == 3)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < 7; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(Turtle, m).CollisionRect(GetRect(i, m)))
							{
								if (i == Turtle)
								{
									return;
								}
								cTurtle[n].SetShow(false);
								return;
							}
						}
					}
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
					PosYRndom();
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
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(Garbage, m).CollisionRect(GetRect(i, m)))
							{
								if (i == Garbage && n == m)
								{
									return;
								}
								cGarbage[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
		}
		else if (obstacleNum >= 200 && obstacleNum < 300)
		{
			//����
			if (!cWaterFlow.GetShow())
			{
				createFlg = ObstaclePercentage(25);
				if (!createFlg)
					return;
				cWaterFlow.SetShow(true);
				//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

				cWaterFlow.SetPosx(posx + g_pGraphics->GetTargetWidth());
				PosYRndom();
				cWaterFlow.SetPosy(posY);
				//�d�Ȃ����ꍇ�\�����Ȃ�
				for (int i = 0; i < SHOW_LIMIT; i++)
				{
					for (int m = 0; m < 3; m++)
					{
						if (GetRect(WaterFlow, m).CollisionRect(GetRect(i, m)))
						{
							if (i == WaterFlow)
							{
								return;
							}
							cWaterFlow.SetShow(false);
							return;
						}
					}
				}
				return;
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
					PosYRndom();
					cBubble[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(Bubble, m).CollisionRect(GetRect(i, m)))
							{
								if (i == Bubble && n == m)
								{
									return;
								}
								cBubble[n].SetShow(false);
								return;
							}
						}
					}
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
					PosYRndom();
					cShoalSardine[n].SetPosy(posY);
					if (eventNum == Event_ShoalSardine)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(ShoalSardine, m).CollisionRect(GetRect(i, m)))
							{
								if (i == ShoalSardine)
								{
									return;
								}
								cShoalSardine[n].SetShow(false);
								return;
							}
						}
					}
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
					PosYRndom();
					cSwordFish[n].SetPosy(posY);
					if (eventNum == 4)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < 7; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(SwordFish, m).CollisionRect(GetRect(i, m)))
							{
								if (i == SwordFish)
								{
									return;
								}
								cSwordFish[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
		}
		else if (obstacleNum >= 600)
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
					PosYRndom();
					cSchoolTuna[n].SetPosy(posY);
					if (eventNum == 4)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < 7; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(SchoolTuna, m).CollisionRect(GetRect(i, m)))
							{
								if (i == SchoolTuna)
								{
									return;
								}
								cSchoolTuna[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
		}
	}
	else if(distance % 35 == 0 && distance != 0)
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
					PosYRndom();
					cFish[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(FoodFish, n).CollisionRect(GetRect(i, m)))
							{
								if (i == FoodFish && n == m)
								{
									return;
								}
								cFish[n].SetShow(false);
								return;
							}
						}
					}
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
					PosYRndom();
					cShrimp[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(FoodShrimp, n).CollisionRect(GetRect(i, m)))
							{
								if (i == FoodShrimp && n == m)
								{
									return;
								}
								cShrimp[n].SetShow(false);
								return;
							}
						}
					}
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
					PosYRndom();
					cCrab[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(FoodCrab, n).CollisionRect(GetRect(i, m)))
							{
								if (i == FoodCrab && n == m)
								{
									return;
								}
								cCrab[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
		}
	}
	else if(distance % 50 == 0 && distance != 0)
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
					PosYRndom();
					cRottenFish[n].SetPosy(posY);
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
					PosYRndom();
					cRottenShrimp[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(RottenShrimp, n).CollisionRect(GetRect(i, m)))
							{
								if (i == RottenShrimp && n == m)
								{
									return;
								}
								cRottenShrimp[n].SetShow(false);
								return;
							}
						}
					}
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
					PosYRndom();
					cRottenCrab[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(RottenCrab, n).CollisionRect(GetRect(i, m)))
							{
								if (i == RottenCrab && n == m)
								{
									return;
								}
								cRottenCrab[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
		}
	}*/


	eventNum = ShoalSardine;
	if (distance % 35 == 0 && distance != 0)
	{
		//showFlg��false�̐H�ו�,��Q����������_���őI��ŁA
		if (tutorialStep <= Task_Complete)
		{
			obstacleNum = obstacleRandom.Random(FoodFish, FoodCrab + 1);
		}
		else if(eventNum == Event_Turtle || eventNum == Event_ShoalSardine || eventNum == Event_Garbage)
		{
			eventFoodCreateFlg = ObstaclePercentage(25);
			if (eventFoodCreateFlg)
			{
				obstacleNum = obstacleRandom.Random(ShoalSardine, FoodCrab + 1);
			}
			else
			{
				if (eventNum == Event_Turtle)
					obstacleNum = Turtle;
				else if (eventNum == Event_ShoalSardine)
					obstacleNum = ShoalSardine;
				else if (eventNum == Event_Garbage)
					obstacleNum = Garbage;					
			}
		}
		else
		{
			obstacleNum = obstacleRandom.Random(0, 13);
		}

		//��Q���̈ʒu�w���showflg��true
		switch (obstacleNum)
		{
		case Turtle:
			for (int n = 0; n < 5; n++)
			{
				if (eventNum != Event_Turtle &&  n != 0)
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
					PosYRndom();
					cTurtle[n].SetPosy(posY);
					if (eventNum == 3)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < 7; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(Turtle, m).CollisionRect(GetRect(i, m)))
							{
								if (i == Turtle)
								{
									return;
								}
								cTurtle[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
			break;
		case Garbage:
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
					PosYRndom();
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
					int no = garbageNoRandom.Random(GARBAGE_SHOES,GARBAGE_BAG + 1);
					cGarbage[n].SetGarbageNo(no);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cGarbage[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					
					cGarbage[n].SetPosy(posY);
					if (eventNum == Event_Garbage)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(Garbage, m).CollisionRect(GetRect(i, m)))
							{
								if (i == Garbage && n == m)
								{
									return;
								}
								cGarbage[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
			break;
		case WaterFlow:
			if (!cWaterFlow.GetShow())
			{
				createFlg = ObstaclePercentage(25);
				if (!createFlg)
					return;
				cWaterFlow.SetShow(true);
				//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

				cWaterFlow.SetPosx(posx + g_pGraphics->GetTargetWidth());
				PosYRndom();
				cWaterFlow.SetPosy(posY);
				//�d�Ȃ����ꍇ�\�����Ȃ�
				for (int i = 0; i < SHOW_LIMIT; i++)
				{
					for (int m = 0; m < 3; m++)
					{
						if (GetRect(WaterFlow, m).CollisionRect(GetRect(i, m)))
						{
							if (i == WaterFlow)
							{
								return;
							}
							cWaterFlow.SetShow(false);
							return;
						}
					}
				}
				return;
			}

			break;
		case Bubble:
			for (int n = 0; n < 3; n++)
			{
				if (!cBubble[n].GetShow())
				{
					cBubble[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cBubble[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cBubble[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(Bubble, m).CollisionRect(GetRect(i, m)))
							{
								if (i == Bubble && n == m)
								{
									return;
								}
								cBubble[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
			break;
		case FoodFish:
			for (int n = 0; n < 3; n++)
			{
				if (!cFish[n].GetShow())
				{
					cFish[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cFish[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cFish[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(FoodFish, n).CollisionRect(GetRect(i, m)))
							{
								if (i == FoodFish && n == m)
								{
									return;
								}
								cFish[n].SetShow(false);
								return;
							}
						}						
					}
					return;
				}
			}
			break;
		case FoodShrimp:
			for (int n = 0; n < 3; n++)
			{
				if (!cShrimp[n].GetShow())
				{
					cShrimp[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cShrimp[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cShrimp[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(FoodShrimp, n).CollisionRect(GetRect(i, m)))
							{
								if (i == FoodShrimp && n == m)
								{
									return;
								}
								cShrimp[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
			break;
		case FoodCrab:
			for (int n = 0; n < 3; n++)
			{
				if (!cCrab[n].GetShow())
				{
					cCrab[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cCrab[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cCrab[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(FoodCrab, n).CollisionRect(GetRect(i, m)))
							{
								if (i == FoodCrab && n == m)
								{
									return;
								}
								cCrab[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
			break;
		case RottenFish:
			for (int n = 0; n < 3; n++)
			{
				if (!cRottenFish[n].GetShow())
				{
					cRottenFish[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cRottenFish[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cRottenFish[n].SetPosy(posY);
					return;
				}
			}
			break;
		case RottenShrimp:
			for (int n = 0; n < 3; n++)
			{
				if (!cRottenShrimp[n].GetShow())
				{
					cRottenShrimp[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cRottenShrimp[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cRottenShrimp[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(RottenShrimp, n).CollisionRect(GetRect(i, m)))
							{
								if (i == RottenShrimp && n == m)
								{
									return;
								}
								cRottenShrimp[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
			break;
		case RottenCrab:
			for (int n = 0; n < 3; n++)
			{
				if (!cRottenCrab[n].GetShow())
				{
					cRottenCrab[n].SetShow(true);
					//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j

					cRottenCrab[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cRottenCrab[n].SetPosy(posY);
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(RottenCrab, n).CollisionRect(GetRect(i, m)))
							{
								if (i == RottenCrab && n == m)
								{
									return;
								}
								cRottenCrab[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
			break;
		case ShoalSardine:
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
					PosYRndom();
					cShoalSardine[n].SetPosy(posY);
					if (eventNum == Event_ShoalSardine)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < SHOW_LIMIT; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(ShoalSardine, m).CollisionRect(GetRect(i, m)))
							{
								if (i == ShoalSardine)
								{
									return;
								}
								cShoalSardine[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
			break;
		case SwordFish:
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
					PosYRndom();
					cSwordFish[n].SetPosy(posY);
					if (eventNum == 4)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < 7; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(SwordFish, m).CollisionRect(GetRect(i, m)))
							{
								if (i == SwordFish)
								{
									return;
								}
								cSwordFish[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
			break;
		case SchoolTuna:
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
					PosYRndom();
					cSchoolTuna[n].SetPosy(posY);
					if (eventNum == 4)
						return;
					//�d�Ȃ����ꍇ�\�����Ȃ�
					for (int i = 0; i < 7; i++)
					{
						for (int m = 0; m < 3; m++)
						{
							if (GetRect(SchoolTuna, m).CollisionRect(GetRect(i, m)))
							{
								if (i == SchoolTuna)
								{
									return;
								}
								cSchoolTuna[n].SetShow(false);
								return;
							}
						}
					}
					return;
				}
			}
			break;

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
		cSwordFish[n].Update(wx, wy);
		cSchoolTuna[n].Update(wx, wy);
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

void CObstacleManager::PosYRndom()
{	
	if (obstacleNum == 1 || obstacleNum == 2)
		posYNum = posYRndom.Random(1, 4);
	else if (obstacleNum == 3)
		posYNum = posYRndom.Random(2, 6);
	else
		posYNum = posYRndom.Random(1, 6);

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