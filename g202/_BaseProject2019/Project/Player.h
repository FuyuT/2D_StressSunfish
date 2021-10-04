#pragma once

#include "Mof.h"
#include "Enemy.h"
#include "time.h"

//移動速度
#define		PLAYER_SPEED		0.6f
//最大速度
#define		PLAYER_MAXSPEED		10.0f
//エサ探知範囲
#define		FEED_SEARCHRANGE	60.0f
//重力
#define		GRAVITY				1.0f
//ジャンプ力
#define		JUMP_POWER_X		8.0f
#define		JUMP_POWER_Y		30.0f
//海面
#define		SEA_LEVEL			780
//海底
#define		UNDER_SEA			2160


//ステータス( 状態 に関する定数)

//エサを食べたときに得られる満腹度
#define		FEED_SATIETYLEVEL	3
//空腹になる速度
#define		HUNGRY_SPEED		150
//満腹
#define		FULL_STOMACH		10
//寄生虫の増える速度
#define		PARASITE_SPEED		30
//最大寄生虫許容量
#define		PARASITE_LIMIT		100
//体温が上下する速度
#define		TEMPERATURE_SPEED	30
//体温限界値
#define		TEMPERATURE_LIMIT	100


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
	//ジャンプを行う前のY座標
	float		beforeJumpingPosY;
	//ジャンプしているかを表すフラグ
	bool		jumpFlg;
	//生きているかを表すフラグ
	bool		deadFlg;
	//アクション可能であるか表すフラグ
	bool		jumpPossibleFlg;
	bool		eatPossibleFlg;

	//使わんかも
	//ステータス( 状態 に関する変数)
	//体温
	int			temperature;
	int			temperatureTime;
	//空腹
	int			hungry;
	int			hungryTime;
	//寄生虫
	int			parasite;
	int			parasiteTime;

public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize();
	void UpdateMove();
	//確率で死ぬ
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
	void Eat();
	//ジャンプ
	void Jump();
	void Update();
	void Render(float wx,float wy);
	void RenderDebug();
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
			posX,
			posY,
			posX + texture.GetWidth(),
			posY + texture.GetHeight()
		);
	}

	//エサが食べられる範囲にあるかを判断するための当たり判定
	CRectangle GetSearchRect()
	{
		return CRectangle(
			posX - FEED_SEARCHRANGE,
			posY - FEED_SEARCHRANGE,
			posX + texture.GetWidth() + FEED_SEARCHRANGE,
			posY + texture.GetHeight() + FEED_SEARCHRANGE
		);
	}

	void Collision(Enemy& ene);

	bool IsDead()
	{
		return deadFlg;
	}
};

