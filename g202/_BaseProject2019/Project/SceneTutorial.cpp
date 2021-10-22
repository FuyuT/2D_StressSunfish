#include "SceneTutorial.h"

CSceneTutorial::CSceneTutorial()
{
}

CSceneTutorial::~CSceneTutorial()
{
}

bool CSceneTutorial::Load()
{
	if (!pl.Load())return false;
	if (!ui.Load())return false;
	if (!cObstacle.Load())return false;
	return true;
}

void CSceneTutorial::Initialize()
{
}

void CSceneTutorial::Update()
{
}

void CSceneTutorial::Render()
{
}

void CSceneTutorial::RenderDebug()
{
}

void CSceneTutorial::Release()
{
}
