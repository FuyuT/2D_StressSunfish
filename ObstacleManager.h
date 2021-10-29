#pragma once
#include "FoodFish.h"
#include "FoodShrimp.h"
#include "FoodCrab.h"
#include "Garbage.h"
#include "Bubble.h"
#include "Turtle.h"
#include "WaterFlow.h"

//�����蔻��̔��ʂ̂��ߒǉ�
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

	//�����蔻��̔��ʂ̂��ߒǉ�
	CRectangle GetRect(int type,int num)
	{
		switch (type)
		{
			case Turtle:
				return cTurtle[num].GetRect();
				break;
			case Garbage:
				return cGarbage[num].GetRect();
				break;
			case WaterFlow:
				return cWaterFlow[num].GetRect();
				break;
			case Bubble:
				return cBubble[num].GetRect();
				break;
			case FoodFish:
				return cFish[num].GetRect();
				break;
			case FoodShrimp:
				return cShrimp[num].GetRect();
				break;
			case FoodCrab:
				return cCrab[num].GetRect();
				break;
		}
		
	}

	//player�������\���ɂ��邽�ߒǉ�
	void SetShow(bool flg, int type,int num)
	{
		switch (type)
		{
			case FoodFish:
				cFish[num].SetShow(flg);
				break;
			case FoodShrimp:
				cShrimp[num].SetShow(flg);
				break;
			case FoodCrab:
				cCrab[num].SetShow(flg);
				break;
		}
	}

	//player������u��ʉ��ɑ��݂��邩�v���m�F���邽�ߒǉ�
	bool GetShow(int type, int num)
	{
		switch (type)
		{
		case Turtle:
			return cTurtle[num].GetShow();
			break;
		case Garbage:
			return cGarbage[num].GetShow();
			break;
		case WaterFlow:
			return cWaterFlow[num].GetShow();
			break;
		case Bubble:
			return cBubble[num].GetShow();
			break;
		case FoodFish:
			return cFish[num].GetShow();
			break;
		case FoodShrimp:
			return cShrimp[num].GetShow();
			break;
		case FoodCrab:
			return cCrab[num].GetShow();
			break;
		}
	}
};

