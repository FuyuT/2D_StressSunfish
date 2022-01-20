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
		//食べ物
		cFish[n].Initialize();
		cShrimp[n].Initialize();
		cCrab[n].Initialize();
		cRottenFish[n].Initialize();
		cRottenShrimp[n].Initialize();
		cRottenCrab[n].Initialize();
		//障害物
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

	//チュートリアル
	if (tutorialStep <= Task_Complete)
	{
		obstacleFlg = false;
		foodFlg = true;
		rottenFlg = false;
	}
	//イベント
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
		//食べ物
		cFish[n].Update(wx, wy);
		cShrimp[n].Update(wx, wy);
		cCrab[n].Update(wx, wy);
		cRottenFish[n].Update(wx, wy);
		cRottenShrimp[n].Update(wx, wy);
		cRottenCrab[n].Update(wx, wy);
		//障害物
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
		//食べ物
		cFish[n].Render(wx, wy);
		cShrimp[n].Render(wx, wy);
		cCrab[n].Render(wx, wy);
		cRottenFish[n].Render(wx, wy);
		cRottenShrimp[n].Render(wx, wy);
		cRottenCrab[n].Render(wx, wy);
		//障害物
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

	//確認デバッグ用
	//CGraphicsUtilities::RenderString(10, 100, gFileBuffer);
}

void CObstacleManager::RenderDebug(float wx, float wy)
{
	for (int n = 0; n < 3; n++)
	{
		//食べ物
		cFish[n].RenderDebug(wx, wy);
		cShrimp[n].RenderDebug(wx, wy);
		cCrab[n].RenderDebug(wx, wy);
		cRottenFish[n].RenderDebug(wx, wy);
		cRottenShrimp[n].RenderDebug(wx, wy);
		cRottenCrab[n].RenderDebug(wx, wy);
		//障害物
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
		//食べ物
		cFish[n].Release();
		cShrimp[n].Release();
		cCrab[n].Release();
		cRottenFish[n].Release();
		cRottenShrimp[n].Release();
		cRottenCrab[n].Release();
		//障害物
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
	//障害物が重なっているかの判定
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
				case WaterFlow:	//水流は今のところ一つなので、この関数を呼ばない（読んだらSetShow(false)にはいる）
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
	//ファイルの容量確認
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//メモリ確保　バッファに読み込み
	char* gFileBuffer = (char*)malloc(fSize + 1);

	fSize = fread(gFileBuffer, 1, fSize, fp);
	gFileBuffer[fSize] = '\0';

	//データの読み込み
	//障害物
	//出現間隔
	strtok(gFileBuffer, "=");
	obstacleDistance = atoi(strtok(NULL, ","));
	//亀
	strtok(NULL, "=");
	turtleRate = atoi(strtok(NULL, ","));
	//ゴミ
	strtok(NULL, "=");
	garbageRate = atoi(strtok(NULL, ",")) + turtleRate;
	//水流
	strtok(NULL, "=");
	waterFlowRate = atoi(strtok(NULL, ",")) + garbageRate;
	//泡
	strtok(NULL, "=");
	bubbleRate = atoi(strtok(NULL, ",")) + waterFlowRate;
	//魚群
	strtok(NULL, "=");
	shoalSardineRate = atoi(strtok(NULL, ",")) + bubbleRate;
	//マグロ
	strtok(NULL, "=");
	tunaRate = atoi(strtok(NULL, ",")) + shoalSardineRate;
	//カジキ
	strtok(NULL, "=");
	swordFishRate = atoi(strtok(NULL, ",")) + tunaRate;

	//安全な食べ物
	strtok(NULL, "=");
	safeFoodDistance = atoi(strtok(NULL, ","));

	//危険な食べ物
	strtok(NULL, "=");
	dangerFoodDistance = atoi(strtok(NULL, ","));

	fclose(fp);
	return true;
}

void CObstacleManager::ObstacleGenerate(int distance, bool obstacleFlg, int eventNum, int posx)
{
	//showFlgがfalseの障害物を一つランダムで選んで、
	if (distance % obstacleDistance == 0 && distance != 0 && obstacleFlg)
	{
		obstacleNum = obstacleRandom.Random(0, 1000);

		if (eventNum == Event_Turtle)
			obstacleNum = turtleRate - 1;
		else if (eventNum == Event_ShoalSardine)
			obstacleNum = shoalSardineRate - 1;
		else if (eventNum == Event_Garbage)
			obstacleNum = garbageRate - 1;

		//ランダムで出た数字によってif文で障害物を表示する
		if (obstacleNum < turtleRate)
		{
			//亀
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
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cTurtle[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Obstacle);
					cTurtle[n].SetPosy(posY);
					if (eventNum == 3)
						return;
					//重なった場合表示しない
					Overlap(Turtle, n);
					return;
				}
			}
		}
		else if (obstacleNum >= turtleRate && obstacleNum < garbageRate)
		{
			//ごみ
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
					//ゴミのランダム決定
					int no = garbageNoRandom.Random(GARBAGE_SHOES, GARBAGE_BAG + 1);
					cGarbage[n].SetGarbageNo(no);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cGarbage[n].SetPosx(posx + g_pGraphics->GetTargetWidth());

					cGarbage[n].SetPosy(posY);
					if (eventNum == Event_Garbage)
						return;
					//重なった場合表示しない
					Overlap(Garbage, n);
					return;
				}
			}
		}
		else if (obstacleNum >= garbageRate && obstacleNum < waterFlowRate)
		{
			//水流
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
						//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

						cWaterFlow.SetPosx(posx + g_pGraphics->GetTargetWidth());
						PosYRandom(Obstacle);
						cWaterFlow.SetPosy(posY);
						return;
					}
					return;
				}
			}
		}
		else if (obstacleNum >= waterFlowRate && obstacleNum < bubbleRate)
		{
			//泡
			for (int n = 0; n < 3; n++)
			{
				if (!cBubble[n].GetShow())
				{
					cBubble[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cBubble[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Obstacle);
					cBubble[n].SetPosy(posY);
					//重なった場合表示しない
					Overlap(Bubble, n);
					return;
				}
			}
		}
		else if (obstacleNum >= bubbleRate && obstacleNum < shoalSardineRate)
		{
			//魚群
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
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cShoalSardine[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
					PosYRandom(Obstacle);
					cShoalSardine[n].SetPosy(posY);
					if (eventNum == Event_ShoalSardine)
						return;
					//重なった場合表示しない
					//Overlap(ShoalSardine, n);
					return;
				}
			}
		}
		else if (obstacleNum >= shoalSardineRate && obstacleNum < tunaRate)
		{
			//マグロ
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
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cSchoolTuna[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
					PosYRandom(Obstacle);
					cSchoolTuna[n].SetPosy(posY);
					if (eventNum == 4)
						return;
					//重なった場合表示しない
					//Overlap(SchoolTuna, n);
					return;
				}
			}
		}
		else if (obstacleNum >= tunaRate && obstacleNum < swordFishRate)
		{

			//カジキ
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
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cSwordFish[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
					PosYRandom(Obstacle);
					cSwordFish[n].SetPosy(posY);
					if (eventNum == 4)
						return;
					//重なった場合表示しない
					//Overlap(SwordFish, n);
					return;
				}
			}
		}
	}
}

void CObstacleManager::SafeFoodGenerate(int distance, bool foodFlg, int eventNum, int posx)
{
	//showFlgがfalseの安全な食べ物を一つランダムで選んで、
	if (distance % safeFoodDistance == 0 && distance != 0 && foodFlg)
	{
		foodRandom = obstacleRandom.Random(0, 300);
		//ランダムで出た数字によってif文で食べ物を表示する
		if (foodRandom < 100)
		{
			//魚
			for (int n = 0; n < 3; n++)
			{
				if (!cFish[n].GetShow())
				{
					cFish[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

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
					//重なった場合表示しない
					Overlap(FoodFish, n);
					return;
				}
			}
		}
		else if (foodRandom >= 100 && foodRandom < 200)
		{
			//エビ
			for (int n = 0; n < 3; n++)
			{
				if (!cShrimp[n].GetShow())
				{
					cShrimp[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

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
					//重なった場合表示しない
					Overlap(FoodShrimp, n);
					return;
				}
			}
		}
		else if (foodRandom >= 200)
		{
			//カニ
			for (int n = 0; n < 3; n++)
			{
				if (!cCrab[n].GetShow())
				{
					cCrab[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

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
					//重なった場合表示しない
					Overlap(FoodCrab, n);
					return;
				}
			}
		}
	}
}

void CObstacleManager::DangerFoodGenerate(int distance, bool rottenFlg, int eventNum, int posx)
{
	//showFlgがfalseの危ない食べ物を一つランダムで選んで、
	if (distance % dangerFoodDistance == 0 && distance != 0 && rottenFlg)
	{
		rottenRandom = obstacleRandom.Random(0, 300);
		//ランダムで出た数字によってif文で腐った食べ物を表示する
		if (rottenRandom < 100)
		{
			//腐った魚
			for (int n = 0; n < 3; n++)
			{
				if (!cRottenFish[n].GetShow())
				{
					cRottenFish[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cRottenFish[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Rotten);
					cRottenFish[n].SetPosy(posY);
					//重なった場合表示しない
					Overlap(RottenFish, n);
					return;
				}
			}
		}
		else if (rottenRandom >= 100 && rottenRandom < 200)
		{
			//腐ったエビ
			for (int n = 0; n < 3; n++)
			{
				if (!cRottenShrimp[n].GetShow())
				{
					cRottenShrimp[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cRottenShrimp[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Rotten);
					cRottenShrimp[n].SetPosy(posY);
					//重なった場合表示しない
					Overlap(RottenShrimp, n);
					return;
				}
			}
		}
		else if (rottenRandom >= 200)
		{
			//腐ったカニ
			for (int n = 0; n < 3; n++)
			{
				if (!cRottenCrab[n].GetShow())
				{
					cRottenCrab[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cRottenCrab[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Rotten);
					cRottenCrab[n].SetPosy(posY);
					//重なった場合表示しない
					Overlap(RottenCrab, n);
					return;
				}
			}
		}
	}	
}