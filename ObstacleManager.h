#pragma once
#include "FoodFish.h"
#include "FoodShrimp.h"
#include "FoodCrab.h"
#include "Garbage.h"
#include "Bubble.h"
#include "Turtle.h"

//“–‚½‚è”»’è‚Ì”»•Ê‚Ì‚½‚ß’Ç‰Á
enum obstacle {
	Turtle,
	Bubble,
	Garbage,
	Stream,
	FoodFish,
	FoodShrimp,
	FoodCrab,
};

class CObstacleManager
{
private:
	CFoodFish   cFish;
	CFoodShrimp cShrimp;
	CFoodCrab   cCrab;
	CGarbage	cGarbage;
	CBubble		cBubble;
	CTurtle     cTurtle;

public:
	CObstacleManager();
	~CObstacleManager();
	bool Load();
	void Initialize();
	void Update(float wx, float wy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();

	//“–‚½‚è”»’è‚Ì”»•Ê‚Ì‚½‚ß’Ç‰Á
	CRectangle GetRect(int type)
	{
		switch (type)
		{
			case Turtle:
				return cTurtle.GetRect();
				break;
			case Bubble:
				return cBubble.GetRect();
				break;
			case Garbage:
				return cGarbage.GetRect();
				break;
			//case Stream:
			//	return cStream/waterflow.GetRect();
			//	break;
			case FoodFish:
				return cFish.GetRect();
				break;
			case FoodShrimp:
				return cShrimp.GetRect();
				break;
			case FoodCrab:
				return cCrab.GetRect();
				break;
		}
		
	}
};

