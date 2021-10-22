#include "ObstacleManager.h"

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
		if (!cTurtle[n].Load())return false;
		if (!cWaterFlow[n].Load())return false;
	}
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
		cTurtle[n].Initialize();
		cWaterFlow[n].Initialize();
	}

}

void CObstacleManager::Update(float wx, float wy)
{
	//選ぶタイミング条件後で追加


	//showFlgがfalseの食べ物を一つランダムで選んで、
	foodNum = foodRandom.Random(4, 7);
	//障害物の位置指定とshowflgをtrue
	switch (foodNum)
	{
	case FoodFish:
		for (int n = 0; n < 3; n++)
		{
			if (!cFish[n].GetShowflg())
			{
				cFish[n].SetShowFlg(true);
				//Playerのpos.x + screenWidthとyのpos（海から出ないようにランダム）
			
				//cFish[n].SetInitPos(Vector2 initPos(pl.GetPosX() + g_pInput->GetTargetWidth(),))

				return;
			}
		}
		//全てshowFlgがtrue
		break;
	case FoodShrimp:
		break;
	case FoodCrab:
		break;
	}

	
	//食べ物
	//cFish.Update(wx, wy);
	//cShrimp.Update(wx, wy);
	//cCrab.Update(wx, wy);

	////障害物
	//cGarbage.Update(wx, wy);
	//cBubble.Update(wx, wy);
	//cTurtle.Update(wx, wy);
	//cWaterFlow.Update(wx, wy);
}

void CObstacleManager::Render(float wx, float wy)
{
	////食べ物	
	//fishFlg = ObstaclePercentage(20);
	//if(fishFlg)
	//	cFish.Render(wx, wy);
 //   		
	//cShrimp.Render(wx, wy);
	//cCrab.Render(wx, wy);

	////障害物
	//cGarbage.Render(wx, wy);
	//cBubble.Render(wx, wy);
	//cTurtle.Render(wx, wy);
	//cWaterFlow.Render(wx, wy);
}

void CObstacleManager::RenderDebug(float wx, float wy)
{
	////食べ物
	//cFish.RenderDebug(wx, wy);
	//cShrimp.RenderDebug(wx, wy);
	//cCrab.RenderDebug(wx, wy);

	////障害物
	//cGarbage.RenderDebug(wx, wy);
	//cBubble.RenderDebug(wx, wy);
	//cTurtle.RenderDebug(wx, wy);
	//cWaterFlow.RenderDebug(wx, wy);

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
		cTurtle[n].Release();
		cWaterFlow[n].Release();
	}

}

