#include "ObstacleManager.h"

CObstacleManager::CObstacleManager()
{
}

CObstacleManager::~CObstacleManager()
{
}

bool CObstacleManager::Load()
{
	if(!cFish.Load())return false;
	if (!cShrimp.Load())return false;
	if (!cCrab.Load())return false;
	if (!cGarbage.Load())return false;
	if (!cBubble.Load())return false;
	if (!cTurtle.Load())return false;
	if (!cWaterFlow.Load())return false;

	return true;
}

void CObstacleManager::Initialize()
{
	//êHÇ◊ï®
	cFish.Initialize();
	cShrimp.Initialize();
	cCrab.Initialize();
	//è·äQï®
	cGarbage.Initialize();
	cBubble.Initialize();
	cTurtle.Initialize();
	cWaterFlow.Initialize();

}

void CObstacleManager::Update(float wx, float wy)
{
	//êHÇ◊ï®
	cFish.Update(wx, wy);
	cShrimp.Update(wx, wy);
	cCrab.Update(wx, wy);

	//è·äQï®
	cGarbage.Update(wx, wy);
	cBubble.Update(wx, wy);
	cTurtle.Update(wx, wy);
	cWaterFlow.Update(wx, wy);
}

void CObstacleManager::Render(float wx, float wy)
{
	//êHÇ◊ï®
	cFish.Render(wx, wy);	
	cShrimp.Render(wx, wy);
	cCrab.Render(wx, wy);

	//è·äQï®
	cGarbage.Render(wx, wy);
	cBubble.Render(wx, wy);
	cTurtle.Render(wx, wy);
	cWaterFlow.Render(wx, wy);
}

void CObstacleManager::RenderDebug(float wx, float wy)
{
	//êHÇ◊ï®
	cFish.RenderDebug(wx, wy);
	cShrimp.RenderDebug(wx, wy);
	cCrab.RenderDebug(wx, wy);

	//è·äQï®
	cGarbage.RenderDebug(wx, wy);
	cBubble.RenderDebug(wx, wy);
	cTurtle.RenderDebug(wx, wy);
	cWaterFlow.RenderDebug(wx, wy);

}

void CObstacleManager::Release()
{
	cFish.Release();
	cShrimp.Release();
	cCrab.Release();
	cGarbage.Release();
	cBubble.Release();
	cTurtle.Release();
	cWaterFlow.Release();
}