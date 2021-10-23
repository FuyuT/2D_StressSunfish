#pragma once
#include "FoodFish.h"
#include "FoodShrimp.h"
#include "FoodCrab.h"
#include "Garbage.h"
#include "Bubble.h"
#include "Turtle.h"
#include "WaterFlow.h"

//当たり判定の判別のため追加
enum obstacle {
	Turtle,
	Garbage,
	WaterFlow,
	Bubble,
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
	CWaterFlow  cWaterFlow;

public:
	CObstacleManager();
	~CObstacleManager();
	bool Load();
	void Initialize();
	void Update(float wx, float wy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();

	//当たり判定の判別のため追加
	CRectangle GetRect(int type)
	{
		switch (type)
		{
			case Turtle:
				return cTurtle.GetRect();
				break;
			case Garbage:
				return cGarbage.GetRect();
				break;
			case WaterFlow:
				return cWaterFlow.GetRect();
				break;
			case Bubble:
				return cBubble.GetRect();
				break;
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

	//player側から非表示にするため追加
	void SetShow(bool flg, int type)
	{
		switch (type)
		{
			case FoodFish:
				cFish.SetShow(flg);
				break;
			case FoodShrimp:
				cShrimp.SetShow(flg);
				break;
			case FoodCrab:
				cCrab.SetShow(flg);
				break;
		}
	}

	//player側から「画面何に存在するか」を確認するため追加
	bool GetShow(int type)
	{
		switch (type)
		{
			case Bubble:
				return cBubble.GetShow();
				break;
			case FoodFish:
				return cFish.GetShow();
				break;
			case FoodShrimp:
				return cShrimp.GetShow();
				break;
			case FoodCrab:
				return cCrab.GetShow();
				break;
		}
	}
};

