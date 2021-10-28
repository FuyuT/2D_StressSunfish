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
	CFoodFish   cFish[3];
	CFoodShrimp cShrimp[3];
	CFoodCrab   cCrab[3];
	CGarbage	cGarbage[3];
	CBubble		cBubble[3];
	CTurtle     cTurtle[3];
	CWaterFlow  cWaterFlow[3];

	CRandom obstacleRandom;
	CRandom posYRndom;

	int obstacleNum;
	int posY;
	int posYNum;

public:
	CObstacleManager();
	~CObstacleManager();
	bool Load();
	void Initialize();
	void Update(int distance,int posx, float wx, float wy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();
	void PosYRndom();

	//当たり判定の判別のため追加
	CRectangle GetRect(int type)
	{
		switch (type)
		{
			case Turtle:
				return cTurtle[0].GetRect();
				break;
			case Garbage:
				return cGarbage[0].GetRect();
				break;
			case WaterFlow:
				return cWaterFlow[0].GetRect();
				break;
			case Bubble:
				return cBubble[0].GetRect();
				break;
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

	//player側から非表示にするため追加
	void SetShow(bool flg, int type)
	{
		switch (type)
		{
			case FoodFish:
				cFish[0].SetShow(flg);
				break;
			case FoodShrimp:
				cShrimp[0].SetShow(flg);
				break;
			case FoodCrab:
				cCrab[0].SetShow(flg);
				break;
		}
	}

	//player側から「画面何に存在するか」を確認するため追加
	bool GetShow(int type)
	{
		switch (type)
		{
			case Bubble:
				return cBubble[0].GetShow();
				break;
			case FoodFish:
				return cFish[0].GetShow();
				break;
			case FoodShrimp:
				return cShrimp[0].GetShow();
				break;
			case FoodCrab:
				return cCrab[0].GetShow();
				break;
		}
	}
};

