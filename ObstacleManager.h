#pragma once
#include "FoodFish.h"
#include "FoodShrimp.h"
#include "FoodCrab.h"
#include "Garbage.h"
#include "Bubble.h"
#include "Turtle.h"
#include "WaterFlow.h"
#include "Player.h"

//“–‚½‚è”»’è‚Ì”»•Ê‚Ì‚½‚ß’Ç‰Á
enum obstacle {
	Turtle,
	Bubble,
	Garbage,
	WaterFlow,
	FoodFish,
	FoodShrimp,
	FoodCrab,
};

class CObstacleManager
{
private:
	CPlayer pl;

	CFoodFish   cFish[3];
	CFoodShrimp cShrimp[3];
	CFoodCrab   cCrab[3];
	CGarbage	cGarbage[3];
	CBubble		cBubble[3];
	CTurtle     cTurtle[3];
	CWaterFlow  cWaterFlow[3];

	CRandom random;
	CRandom foodRandom;

	int foodNum;


public:
	CObstacleManager();
	~CObstacleManager();
	bool Load();
	void Initialize();
	void Update(float wx, float wy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();

	bool ObstaclePercentage(int percent)
	{
		//Šm—¦‚É‚æ‚Á‚Ätrue‚ð•Ô‚·
		if (random.Random(1, 100 / percent + 1) == 1)
		{
			return true;
		}
		return false;
	}

	//“–‚½‚è”»’è‚Ì”»•Ê‚Ì‚½‚ß’Ç‰Á
	CRectangle GetRect(int type)
	{
		switch (type)
		{
			case Turtle:
				return cTurtle[0].GetRect();
				break;
			case Bubble:
				return cBubble[0].GetRect();
				break;
			case Garbage:
				return cGarbage[0].GetRect();
				break;
			//case WaterFlow:
			//	return cStream/waterflow.GetRect();
			//	break;
			case FoodFish:
				return cFish[0].GetRect();
				break;
			case FoodShrimp:
				return cShrimp[0].GetRect();
				break;
			case FoodCrab:
				return cCrab[0].GetRect();
				break;
		}
		
	}
};

