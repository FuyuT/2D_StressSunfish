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
		//�H�ו�
		cFish[n].Initialize();
		cShrimp[n].Initialize();
		cCrab[n].Initialize();
		//��Q��
		cGarbage[n].Initialize();
		cBubble[n].Initialize();
		cTurtle[n].Initialize();
		cWaterFlow[n].Initialize();
	}

}

void CObstacleManager::Update(float wx, float wy)
{
	//�I�ԃ^�C�~���O������Œǉ�


	//showFlg��false�̐H�ו���������_���őI��ŁA
	foodNum = foodRandom.Random(4, 7);
	//��Q���̈ʒu�w���showflg��true
	switch (foodNum)
	{
	case FoodFish:
		for (int n = 0; n < 3; n++)
		{
			if (!cFish[n].GetShowflg())
			{
				cFish[n].SetShowFlg(true);
				//Player��pos.x + screenWidth��y��pos�i�C����o�Ȃ��悤�Ƀ����_���j
			
				//cFish[n].SetInitPos(Vector2 initPos(pl.GetPosX() + g_pInput->GetTargetWidth(),))

				return;
			}
		}
		//�S��showFlg��true
		break;
	case FoodShrimp:
		break;
	case FoodCrab:
		break;
	}

	
	//�H�ו�
	//cFish.Update(wx, wy);
	//cShrimp.Update(wx, wy);
	//cCrab.Update(wx, wy);

	////��Q��
	//cGarbage.Update(wx, wy);
	//cBubble.Update(wx, wy);
	//cTurtle.Update(wx, wy);
	//cWaterFlow.Update(wx, wy);
}

void CObstacleManager::Render(float wx, float wy)
{
	////�H�ו�	
	//fishFlg = ObstaclePercentage(20);
	//if(fishFlg)
	//	cFish.Render(wx, wy);
 //   		
	//cShrimp.Render(wx, wy);
	//cCrab.Render(wx, wy);

	////��Q��
	//cGarbage.Render(wx, wy);
	//cBubble.Render(wx, wy);
	//cTurtle.Render(wx, wy);
	//cWaterFlow.Render(wx, wy);
}

void CObstacleManager::RenderDebug(float wx, float wy)
{
	////�H�ו�
	//cFish.RenderDebug(wx, wy);
	//cShrimp.RenderDebug(wx, wy);
	//cCrab.RenderDebug(wx, wy);

	////��Q��
	//cGarbage.RenderDebug(wx, wy);
	//cBubble.RenderDebug(wx, wy);
	//cTurtle.RenderDebug(wx, wy);
	//cWaterFlow.RenderDebug(wx, wy);

}

void CObstacleManager::Release()
{
	for (int n = 0; n < 3; n++)
	{
		//�H�ו�
		cFish[n].Release();
		cShrimp[n].Release();
		cCrab[n].Release();
		//��Q��
		cGarbage[n].Release();
		cBubble[n].Release();
		cTurtle[n].Release();
		cWaterFlow[n].Release();
	}

}

