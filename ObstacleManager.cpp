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

	obstacleRandom.SetSeed((MofU32)time(NULL));
	posYRandom.SetSeed((MofU32)time(NULL));

	lastTimePosY = 0;

	////テキストファイルを開く
	//LoadTextFile("Text\\RandomObstacle.txt");

	////スクリプトの解析を行う
	//char* fb = gFileBuffer;
	//while (TRUE)
	//{
	//	//指定の行の最初の，までがコマンドの指定
	//	char* cmd = strtok(fb, ",");
	//	fb = NULL;
	//	if (!cmd)
	//	{
	//		break;
	//	}
	//	//コマンドの前後に空白などがあるなら除去をする
	//	cmd = Trim(cmd);
	//	//コマンドの識別
	//	int sCmd = 0;
	//	//		for(sCmd = 0;sCmd < CMD_COUNT && stricmp(cmd,gScriptCommand[sCmd]) != 0;sCmd++);
	//	for (sCmd = 0; sCmd < CMD_COUNT; sCmd++)
	//	{
	//		if (stricmp(cmd, gScriptCommand[sCmd]) == 0)
	//		{
	//			break;
	//		}
	//	}
	//	//コマンドに必要なパラメータの解析
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

	//	default:					//定義されていないコマンド
	//	{
	//		char* pstr = strtok(NULL, ";");
	//		MessageBox(NULL, cmd, "コマンド", MB_OK);
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


	//新しいランダム生成の仮
	//showFlgがfalseの障害物を一つランダムで選んで、
	if (distance % 20 == 0 && distance != 0 && obstacleFlg)
	{
		obstacleNum = obstacleRandom.Random(0, 1000);

		if (eventNum == Event_Turtle)
			obstacleNum = 0;
		else if (eventNum == Event_ShoalSardine)
			obstacleNum = 400;
		else if (eventNum == Event_Garbage)
			obstacleNum = 100;

		//ランダムで出た数字によってif文で障害物を表示する
		if (obstacleNum < 100)
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
					PosYRandom(Obstacle, eventNum);
					cTurtle[n].SetPosy(posY);
					if (eventNum == 3)
						return;
					//重なった場合表示しない
					Overlap(Turtle, n);
					return;
				}
			}
		}
		else if (obstacleNum >= 100 && obstacleNum < 200)
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
		else if (obstacleNum >= 200 && obstacleNum < 300)
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
			//泡
			for (int n = 0; n < 3; n++)
			{
				if (!cBubble[n].GetShow())
				{
					cBubble[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cBubble[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRandom(Obstacle, eventNum);
					cBubble[n].SetPosy(posY);
					//重なった場合表示しない
					Overlap(Bubble, n);
					return;
				}
			}
		}
		else if (obstacleNum >= 400 && obstacleNum < 500)
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
					cShoalSardine[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cShoalSardine[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
					PosYRandom(Obstacle, eventNum);
					cShoalSardine[n].SetPosy(posY);
					if (eventNum == Event_ShoalSardine)
						return;
					//重なった場合表示しない
					Overlap(ShoalSardine, n);
					return;
				}
			}
		}
		else if (obstacleNum >= 500 && obstacleNum < 600)
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
					cSwordFish[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cSwordFish[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
					PosYRandom(Obstacle, eventNum);
					cSwordFish[n].SetPosy(posY);
					if (eventNum == 4)
						return;
					//重なった場合表示しない
					Overlap(SwordFish, n);
					return;
				}
			}
		}
		else if (obstacleNum >= 600 && obstacleNum < 700)
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
					cSchoolTuna[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cSchoolTuna[n].SetPosx(posx + g_pGraphics->GetTargetWidth() + 500);
					PosYRandom(Obstacle, eventNum);
					cSchoolTuna[n].SetPosy(posY);
					if (eventNum == 4)
						return;
					//重なった場合表示しない
					Overlap(SchoolTuna, n);
					return;
				}
			}
		}
	}

	//showFlgがfalseの安全な食べ物を一つランダムで選んで、
	if (distance % 40 == 0 && distance != 0 && foodFlg)
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
					PosYRandom(Food, eventNum);
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
					PosYRandom(Food, eventNum);
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
					PosYRandom(Food, eventNum);
					cCrab[n].SetPosy(posY);
					//重なった場合表示しない
					Overlap(FoodCrab, n);
					return;
				}
			}
		}
	}

	//showFlgがfalseの危ない食べ物を一つランダムで選んで、
	if (distance % 50 == 0 && distance != 0 && rottenFlg)
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
					PosYRandom(Rotten, eventNum);
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
					PosYRandom(Rotten, eventNum);
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
					PosYRandom(Rotten, eventNum);
					cRottenCrab[n].SetPosy(posY);
					//重なった場合表示しない
					Overlap(RottenCrab, n);
					return;
				}
			}
		}
	}


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
	}
		cWaterFlow.Update(wx, wy);
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

//char* CObstacleManager::Trim(char* s)
//{
//	//引数の文字列がない
//	if (!s)
//	{
//		return NULL;
//	}
//	//文字列の後ろから空白以外を見つけた次の位置に\0（終端）を設定する
//	int l = strlen(s);
//	while (--l >= 0)
//	{
//		if (s[l] != '\t' && s[l] != '\r' && s[l] != '\n' && s[l] != ' ')
//		{
//			break;
//		}
//	}
//	s[l + 1] = '\0';
//	//先頭から空白以外を見つけた位置のポインタを返す
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
//	//テキストファイルを開く
//	FILE* fp = fopen(pName, "rt");
//	if (fp == NULL)
//	{
//		return false;
//	}
//	//ファイルの全容量を調べる
//	//一度ファイルの終端に移動して、その位置を調べることでサイズがわかる
//	//調べ終わった後はファイルの先頭に移動して戻しておく
//	//ただしこの方法でも正常なサイズを読み込むことはできない
//	fseek(fp, 0, SEEK_END);
//	long fSize = ftell(fp);
//	fseek(fp, 0, SEEK_SET);
//	//ファイルサイズ分だけのメモリを確保する
//	//終端を含めるため＋１しておく
//	gFileBuffer = (char*)malloc(fSize + 1);
//	//ファイルを全てバッファに読み込む
//	//ここで実際に読み込めたサイズを調べてその終端に\0を入る
//	fSize = fread(gFileBuffer, 1, fSize, fp);
//	gFileBuffer[fSize] = '\0';
//	//ファイルを閉じる
//	fclose(fp);
//	return true;
//}
//
//void CObstacleManager::TextFileUpdate()
//{
//	//Enterキーで次のコマンドを実行する
//	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
//	{
//		if (gCommandNo < gCommandList.GetArrayCount())
//		{
//			//コマンドのタイプによって分岐
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
//			default:					//定義されていないコマンド
//				break;
//			}
//			//次のコマンドへ
//			gCommandNo++;
//		}
//	}
//}
