#pragma once

#include "Mof.h"
#include "ObstacleManager.h"
#include "timer.h"
#include "time.h"

//初期位置 X
#define		STARTPOS_X				200

//座標を進んだ距離に変換する割合
#define		TRANSLATE_DISTANCE		20

//移動速度	
#define		PLAYER_SPEED			0.6f
//最大速度
#define		PLAYER_MAXSPEED			10.0f
//重力
#define		GRAVITY					1.0f

//エサ探知範囲
#define		FEED_SEARCHRANGE		60.0f
//当たり判定の幅調整
#define		COLLISION_ADJUSTMENT	130.0f

//ジャンプ力
#define		JUMP_POWER_X			9.0f
#define		JUMP_POWER_Y			30.0f
//ジャンプ後に潜る量
#define		WATER_LANDING_DEEP		50.0f
//海面からどこまでがジャンプ可能か
#define		JUMP_ZONE				40.0f

//海面
#define		SEA_LEVEL				780
//海底
#define		UNDER_SEA				2160

//お腹が空く度合い
#define		HUNGRYLEVEL				12
//エサを食べたときに得られる満腹度
#define		FEED_SATIETYLEVEL		36
//満腹
#define		FULL_STOMACH			40
//餓死
#define		STARVATION				160

//寄生虫許容限界数
#define		PARASITE_LIMIT			5

//体温が上変動する度合い
#define		TEMPERATURE_LEVEL		3
//標準体温
#define		STANDARD_TEMPERATURE	10
//体温限界値(熱中症)
#define		HYPERTHERMIA_LIMIT		50
//体温限界値(凍死)
#define		FROZEN_LIMIT			30
//体温変動区域
#define		TEMPERATURE_CHANGEZONE	500

//水流による最大加速度
#define		WATERFLOW_MAXSPEED		1.5f
//水流による加速度
#define		WATERFLOW_SPEED			0.02f

//死因一覧
enum CAUSE_OF_DEATH
{
	CAUSE_None,				//死んでいない
	CAUSE_Hyperthermia,     //熱中症(温度)			
	CAUSE_Frozen,			//凍死(温度)			
	CAUSE_Starvation,		//餓死(空腹度・エサ)	
	CAUSE_ChokeOnShell,		//喉つまり(エサ)		
	CAUSE_Obesity,			//肥満(エサ)			
	CAUSE_Obstacle,			//衝突(障害物)			
	CAUSE_Jump,				//ジャンプ				
	CAUSE_Parasite,			//寄生虫				
	CAUSE_Bubble,			//泡					
	CAUSE_SeaTurtle,			//ショック死(ウミガメ)
	CAUSE_WaterFlow,		//急な加速(水流)

};


class CPlayer
{
private:
	//テクスチャ
	CTexture	texture;
	//確率
	CRandom		random;
	//座標
	float		posX;
	float		posY;
	//速度
	float		moveX;
	float		moveY;
	//速度の倍数
	float		moveSpeed;
	//ジャンプしているかを表すフラグ
	bool		jumpFlg;
	//生きているかを表すフラグ
	bool		deadFlg;
	//アクション可能であるか表すフラグ
	bool		possibleToJumpFlg;
	bool		possibleToEatFlg;
	//死因
	int			causeOfDeath;
	//無敵(連続で同じ障害物にぶつかり続けてしまうため、衝突後は解除されるまで無敵にする)
	bool		hitFlg;
	CTimer		hitTimer;

	//ステータス( 状態 に関する変数)
	//体温
	int         bodyTemp;
	float       tempRegion;
	//空腹
	int         hungerRegion;
	//寄生虫
	int			parasite;
	//水流
	CTimer		waterFlowTimer;
	bool		waterFlowFlg;

	//ブレーキ(テスト)
	CTimer		brakeTimer;

	//UI
	CTimer tempTimer;
	CTimer hungerTimer;
	CTimer parasiteTimer;

public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize();
	void UpdateMove();
	//確率で死ぬ 100を割り切れる数のみ対応(1,2,4,5,10,20,25,50,100)
	bool DieInPercentage(int percent)
	{
		//確率によってtrueを返す
		if (random.Random(1, 100 / percent + 1) == 1)
		{
			return true;
		}
		return false;
	}
	//食べる
	bool Eat();
	//ジャンプ
	void Jump();
	void UpdateStatus();
	void Update();
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release();

	//プレイヤーの座標を返す
	int GetPosX()
	{
		return (int)posX;
	};
	int GetPosY()
	{
		return (int)posY;
	};

	//プレイヤー自身の当たり判定を返す
	CRectangle GetRect()
	{
		return CRectangle(
			posX + COLLISION_ADJUSTMENT,
			posY + COLLISION_ADJUSTMENT,
			posX + texture.GetWidth() - COLLISION_ADJUSTMENT,
			posY + texture.GetHeight() - COLLISION_ADJUSTMENT
		);
	}

	//エサが食べられる範囲にあるかを判断するための当たり判定
	CRectangle GetSearchRect()
	{
		return CRectangle(
			posX + COLLISION_ADJUSTMENT - FEED_SEARCHRANGE,
			posY + COLLISION_ADJUSTMENT - FEED_SEARCHRANGE,
			posX + texture.GetWidth() - COLLISION_ADJUSTMENT + FEED_SEARCHRANGE,
			posY + texture.GetHeight() - COLLISION_ADJUSTMENT + FEED_SEARCHRANGE
		);
	}
	CRectangle GetEyeRect()
	{
		return CRectangle(
			posX + texture.GetWidth() - COLLISION_ADJUSTMENT,
			posY + COLLISION_ADJUSTMENT + 25,
			posX + texture.GetWidth() - COLLISION_ADJUSTMENT + 30,
			posY + COLLISION_ADJUSTMENT + 55
		);
	}

	void Collision(CObstacleManager& cObstacle,int num);

	//死んでいればtrueを返す
	bool GetDead()
	{
		return deadFlg;
	}
	//体温を返す 100 ～ 0
	float	GetTemperature()
	{
		return tempRegion;
	}
	int     GetBodyTemp()
	{
		return bodyTemp;
	}
	//寄生虫の付着数を返す 0 ～ 6
	int GetParasite()
	{
		return parasite;
	}
	//空腹度を返す 10～0
	int GetHungry()
	{
		return hungerRegion;
	}
	//死因を返す
	int GetCauseOfDeath()
	{
		return causeOfDeath;
	}
	//進んだ距離(m数)を返す
	int GetDistance()
	{
		//X座標の20分の1(適当)を進んだ距離とする
		return (posX - STARTPOS_X) / TRANSLATE_DISTANCE;
	}
	//「ジャンプ」が可能かを返す
	bool GetJump()
	{
		return possibleToJumpFlg;
	}
	//「食べる」が可能かを返す
	bool GetEat()
	{
		return possibleToEatFlg;
	}

};

