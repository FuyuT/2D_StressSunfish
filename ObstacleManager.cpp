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
	}
	if (!cTurtle.Load())return false;
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
		//障害物
		cGarbage[n].Initialize();
		cBubble[n].Initialize();
	}
		cTurtle.Initialize();
		cWaterFlow.Initialize();

	obstacleRandom.SetSeed((MofU32)time(NULL));
	posYRndom.SetSeed((MofU32)time(NULL));
}

void CObstacleManager::Update(int distance,int posx,float wx,float wy)
{
	//選ぶタイミング条件後で追加
	if (distance % 35 == 0 && distance != 0)
	{
		//showFlgがfalseの食べ物,障害物を一つランダムで選んで、
		obstacleNum = obstacleRandom.Random(0, 7);
		//障害物の位置指定とshowflgをtrue
		switch (obstacleNum)
		{
		case Turtle:
			if (!cTurtle.GetShow())
			{
				createFlg = ObstaclePercentage(25);
				if (!createFlg)
					return;
				cTurtle.SetShow(true);
				//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

				cTurtle.SetPosx(posx + g_pGraphics->GetTargetWidth());
				PosYRndom();
				cTurtle.SetPosy(posY);
				return;
			}
			break;
		case Garbage:
			for (int n = 0; n < 3; n++)
			{
				if (!cGarbage[n].GetShow())
				{
					createFlg = ObstaclePercentage(50);
					if (!createFlg)
						return;
					cGarbage[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cGarbage[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cGarbage[n].SetPosy(posY);
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
				//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

				cWaterFlow.SetPosx(posx + g_pGraphics->GetTargetWidth());
				PosYRndom();
				cWaterFlow.SetPosy(posY);
				return;
			}

			break;
		case Bubble:
			for (int n = 0; n < 3; n++)
			{
				if (!cBubble[n].GetShow())
				{
					cBubble[n].SetShow(true);
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cBubble[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cBubble[n].SetPosy(posY);
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
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cFish[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cFish[n].SetPosy(posY);
					////重なった場合表示しない
					//for (int i = 0; i < 7; i++)
					//{
					//	if (GetRect(FoodFish).CollisionRect(GetRect(i)) && FoodFish != i)
					//	{
					//		cFish[n].SetShow(false);
					//	}
					//}
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
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cShrimp[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cShrimp[n].SetPosy(posY);
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
					//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）

					cCrab[n].SetPosx(posx + g_pGraphics->GetTargetWidth());
					PosYRndom();
					cCrab[n].SetPosy(posY);
					return;
				}
			}
			break;
		}
	}



	for (int n = 0; n < 3; n++)
	{
		//食べ物
		cFish[n].Update(wx, wy);
		cShrimp[n].Update(wx, wy);
		cCrab[n].Update(wx, wy);
		//障害物
		cGarbage[n].Update(wx, wy);
		cBubble[n].Update(wx, wy);

	}
	cTurtle.Update(wx, wy);
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
		//障害物
		cGarbage[n].Render(wx, wy);
		cBubble[n].Render(wx, wy);
	}
		cTurtle.Render(wx, wy);
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
		//障害物
		cGarbage[n].RenderDebug(wx, wy);
		cBubble[n].RenderDebug(wx, wy);
	}
		cTurtle.RenderDebug(wx, wy);
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
		//障害物
		cGarbage[n].Release();
		cBubble[n].Release();
	}
		cTurtle.Release();
		cWaterFlow.Release();
}

void CObstacleManager::PosYRndom()
{	
	if (obstacleNum == 1 || obstacleNum == 2)
		posYNum = posYRndom.Random(1, 4);
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