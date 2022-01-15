#include "Player.h"

CPlayer::CPlayer() :
	standTexture(),
	random(),
	posX(0.0f),
	posY(0.0f),
	moveX(0.0f),
	moveY(0.0f),
	moveSpeed(1.0f),
	jumpFlg(false),
	jumpDangerFlg(false),
	deadFlg(false),
	possibleToJumpFlg(false),
	possibleToEatFlg(),
	causeOfDeath(0),
	hitFlg(false),
	hitTimer(),
	bodyTemp(0),
	tempRegion(0.0f),
	hungerRegion(0),
	parasite(0),
	waterFlowTimer(),
	waterFlowFlg(false),
	brakeTimer(),
	tempTimer(),
	hungerTimer(),
	parasiteTimer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	//プレイヤーのテクスチャの読みこみ
	if (!standTexture.Load("sheet_manbo si_manbo 2_stand.png"))
	{
		return false;
	}
	if (!eatTexture.Load("sheet_manbo si_manbo 2_Eat_anim.png"))
	{
		return false;
	}
	if (!deathTexture.Load("sheet_manbo si_manbo 2_Death.png"))
	{
		return false;
	}
	if (!jumpTexture.Load("sheet_manbo_manbo_jump_anime_1.png"))
	{
		return false;
	}
	//hot
	if (!hotStandTexture.Load("sheet_manbo si_manbo hot_Stand.png"))
	{
		return false;
	}
	if (!hotEatTexture.Load("sheet_manbo si_manbo hot_Eat.png"))
	{
		return false;
	}
	if (!hotDeathTexture.Load("sheet_manbo si_manbo hot_Death.png"))
	{
		return false;
	}
	if (!hotJumpTexture.Load("sheet_manbo si_manbo hot_jump.png"))
	{
		return false;
	}
	//cold
	if (!coldStandTexture.Load("sheet_manbo si_manbo cold_stand.png"))
	{
		return false;
	}
	if (!coldEatTexture.Load("sheet_manbo si_manbo cold_Eat_anim.png"))
	{
		return false;
	}
	if (!coldDeathTexture.Load("sheet_manbo si_manbo cold_Death.png"))
	{
		return false;
	}
	if (!coldJumpTexture.Load("sheet_manbo_manbo jump_cold_jump.png"))
	{
		return false;
	}


	return true;
}

//初期化
void CPlayer::Initialize()
{
	/********
	* 初期値
	*********/
	//確率
	random.SetSeed(time(NULL));
	//座標
	posX = STARTPOS_X;
	posY = STARTPOS_Y;
	//体温
	bodyTemp = STANDARD_TEMPERATURE;
	tempRegion = 50;
	temperature = Temperature::Temp_Normal;
	//空腹度
	hungerRegion = INIT_STOMACH;
	//寄生虫
	parasite = 0;
	//速度
	moveX = 0.0f;
	moveY = 0.0f;
	//ジャンプ
	jumpFlg = false;
	jumpDangerFlg = false;
	jumpDangerTimer.SetTotalTime(5);
	//水流
	moveSpeed = 1.0f;
	waterFlowTimer.SetTotalTime(4);
	waterFlowFlg = false;
	//死因
	causeOfDeath = CAUSE_None;
	//連続衝突を避ける
	hitFlg = false;
	hitTimer.SetTotalTime(1);

	//フラグ
	deadFlg = false;
	for (int i = 0; i < FEED_MAXCOUNT; i++)
	{
		possibleToEatFlg[i] = false;
	}
	possibleToJumpFlg = false;

	//UIタイマー
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);

	//チュートリアル
	eatTaskFlg = false;
	jumpTaskFlg = false;
	taskCompleteStep = Task_Movement;
	moveUpTaskTimer.SetTotalTime(3);
	moveDownTaskTimer.SetTotalTime(3);

	//ブレーキ(テスト)
	brakeTimer.SetTotalTime(0);

	//アニメーション
	SpriteAnimationCreate anim[] = {
		{
			"通常",
			0,0,
			166,166,
			TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
				  {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
				  {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2},{4,5,2},
				  {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
				  {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}
		},
		{
			"食べる",
			0,0,
			166,166,
			FALSE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
				  {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
				  {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2},{4,5,2},
				  {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
				  {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}
		},
		{
			"ジャンプ",
			0,0,
			166,166,
			FALSE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
				  {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
				  {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2},{4,5,2},
				  {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
				  {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}
		},
		{
			"死ぬ",
			0,0,
			166,166,
			FALSE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
				  {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
				  {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2},{4,5,2},
				  {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
				  {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}
		},
	};
	motion.Create(anim, MOTION_COUNT);

	//motion.ChangeMotion(MOTION_STAND);

	playerMaxSpeedX = 10.0f;
	playerMaxSpeedY = 10.0f;
}

//移動
void CPlayer::UpdateMove(int tutorialStep)
{

	//右に移動
	/*
	if (g_pInput->IsKeyHold(MOFKEY_D) || moveSpeed > 1.0)
	{
		moveX += PLAYER_SPEED;
		if (moveX > PLAYER_MAXSPEED)
		{
			moveX = PLAYER_MAXSPEED;
		}
	}
	else
	{
		if (moveX > 0)
		{
			moveX -= PLAYER_SPEED;
			if (moveX <= 0)
			{
				moveX = 0;
			}
		}
	}
	*/

	//ブレーキ(テスト)
	if (g_pInput->IsKeyPush(MOFKEY_B))
	{
		brakeTimer.SetTotalTime(0.5f);
	}

	if (brakeTimer.GetNowtime() >= 0)
	{
		brakeTimer.StartTimer();
		if (moveX < 2.0f)
		{
			moveX = 2.0f;
		}
		else
		{
			moveX -= 1.0f;
		}
	}

	//自動で右に進むように
	if (moveX > playerMaxSpeedX)
	{
		moveX = playerMaxSpeedX;
	}
	else
	{
		moveX += PLAYER_SPEED;
	}

	//チュートリアル用入力検知
	if (tutorialStep == Task_Movement)
	{
		if (g_pInput->IsKeyPush(MOFKEY_W))
		{
			moveUpTaskTimer.StartTimer();
		}
		else if (g_pInput->IsKeyPull(MOFKEY_W))
		{
			moveUpTaskTimer.StopTimer();
		}
		if (g_pInput->IsKeyPush(MOFKEY_S))
		{
			moveDownTaskTimer.StartTimer();
		}
		else if (g_pInput->IsKeyPull(MOFKEY_S))
		{
			moveDownTaskTimer.StopTimer();
		}
	}

	//上に移動
	if (g_pInput->IsKeyHold(MOFKEY_W))
	{
		moveY -= PLAYER_SPEED;
		if (moveY < -playerMaxSpeedY)
		{
			moveY = -playerMaxSpeedY;
		}
	}
	//下に移動
	else if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		moveY += PLAYER_SPEED;
		if (moveY > playerMaxSpeedY)
		{
			moveY = playerMaxSpeedY;
		}
	}
	else
	{
		if (moveY < 0)
		{
			moveY += PLAYER_SPEED;
			if (moveY >= 0)
			{
				moveY = 0;
			}
		}
		else if (moveY > 0)
		{
			moveY -= PLAYER_SPEED;
			if (moveY <= 0)
			{
				moveY = 0;
			}
		}
	}

	//移動のキー入力が無ければ重力の影響を受けるよう
	if (!g_pInput->IsKeyHold(MOFKEY_W) && 
		!g_pInput->IsKeyHold(MOFKEY_S))
	{
		posY += GRAVITY;
	}

	//海底(スクリーン下部)　移動制限
	if (GetRect().Bottom > UNDER_SEA)
	{
		posY = UNDER_SEA - TEXTURE_SIZE + COLLISION_ADJUSTMENT_BOTTOM;
		moveY = 0;
	}
	
	//海面(スクリーン上部)　移動制限
	if (GetRect().Top < SEA_LEVEL)
	{
		posY = SEA_LEVEL - COLLISION_ADJUSTMENT_TOP;
		moveY = 0;
	}	

	
	//一定距離毎にMAX SPEEDを0.01上げる
	if (GetDistance() < 1000)
	{
		playerMaxSpeedX = 10.0f;
		playerMaxSpeedY = 10.0f;
	}
	else if (GetDistance() < 2500)
	{
		playerMaxSpeedX = 11.2f;
		playerMaxSpeedY = 10.5;
	}
	else if (GetDistance() < 5000)
	{
		playerMaxSpeedX = 12.4f;
		playerMaxSpeedY = 11.0f;
	}
	else if (GetDistance() < 10000)
	{
		playerMaxSpeedX = 13.6f;
		playerMaxSpeedY = 11.5f;
	}
	else if (GetDistance() < 25000)
	{
		playerMaxSpeedX = 14.8f;
		playerMaxSpeedY = 12.0f;
	}
	else if (GetDistance() < 50000)
	{
		playerMaxSpeedX = 16.0f;
		playerMaxSpeedY = 12.5f;
	}
	else if (GetDistance() < 100000)
	{
		playerMaxSpeedX = 17.2f;
		playerMaxSpeedY = 13.0f;
	}
	else if (GetDistance() < 200000)
	{
		playerMaxSpeedX = 18.4f;
		playerMaxSpeedY = 13.5f;
	}
	else if (GetDistance() < 300000)
	{
		playerMaxSpeedX = 19.6;
		playerMaxSpeedY = 14.0f;
	}
	else
	{
		playerMaxSpeedX = 20.8;
		playerMaxSpeedY = 14.5f;
	}

	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		playerMaxSpeedX = 20.8;
		playerMaxSpeedY = 14.5f;
	}

}

//エサを食べる
bool CPlayer::Eat(bool rottenFlg, bool unDeadFlg, int tutorialStep)
{
	//エサを食べる
	if (g_pInput->IsKeyPush(MOFKEY_A) && tutorialStep >= Task_Action)
	{
		cSound->Play(SOUND_EAT);
		//チュートリアルタスク
		eatTaskFlg = true;

		if(motion.GetMotionNo() == MOTION_STAND)
			motion.ChangeMotion(MOTION_EAT);

		for (int i = 0; i < FEED_MAXCOUNT; i++)
		{
			possibleToEatFlg[i] = false;
		}

		//死因が確定していない
		if (causeOfDeath == CAUSE_None && !unDeadFlg)
		{
			//死因：肥満
			if (hungerRegion <= FULL_STOMACH)
			{
				cSound->Play(SOUND_OBESITY);
				motion.ChangeMotion(MOTION_DEATH);
				causeOfDeath = CAUSE_Obesity;
				//エサを食べたことを返す
				return true;
			}
		}

		//空腹を満たす
		hungerTimer.SetTotalTime(3);
		if(rottenFlg)
			hungerRegion -= FEED_SATIETYLEVEL;
		else
			hungerRegion -= FEED_SATIETYLEVEL / 2;

		//満腹値を超えたら
		if (hungerRegion < FULL_STOMACH)
		{
			hungerRegion = FULL_STOMACH - 5.0f;
		}

		//死因が確定していない
		if (causeOfDeath == CAUSE_None && !unDeadFlg)
		{
			//腐っていれば確率で死ぬ
			if (rottenFlg)
			{
				//死因：喉つまり
				//20%で死ぬ
				if (DieInPercentage(20))
				{
					cSound->Play(SOUND_CLOGGED);
					motion.ChangeMotion(MOTION_DEATH);
					causeOfDeath = CAUSE_ChokeOnShell;
				}
			}
		}

		cSound->Play(SOUND_EAT);
		//エサを食べたことを返す
		return true;
	}

	return false;
}

//ジャンプ
void CPlayer::Jump(bool unDeadFlg, int tutorialStep)
{
	//海面に近いとき(ジャンプ可能である際) に A を押す
	if (g_pInput->IsKeyPush(MOFKEY_A) &&
		possibleToJumpFlg && tutorialStep >= Task_Action)
	{
		cSound->Play(SOUND_JUMP_START);
		cSound->Play(SOUND_JUMPING);
		//チュートリアルタスク
		jumpTaskFlg = true;

		jumpFlg = true;	
		possibleToJumpFlg = false;

		motion.ChangeMotion(MOTION_JUMP);

		//ジャンプ力
		moveY = -JUMP_POWER_Y;
		moveX = JUMP_POWER_X;

	}
	else if (jumpFlg)
	{
		cSound->Play(SOUND_WATER_LANDING);
		moveY += PLAYER_SPEED;
		//海面より下か(海に戻ったか)
		//落下による勢いで少し潜るように
		if (posY > SEA_LEVEL + WATER_LANDING_DEEP)
		{
			//jumpDangerTimerの時間内にジャンプを行うと死亡
			if (jumpDangerFlg)
			{
				//死因が確定していない
				if (causeOfDeath == CAUSE_None && !unDeadFlg)
				{
					motion.ChangeMotion(MOTION_DEATH);
					causeOfDeath = CAUSE_Jump;
				}
			}
			else
			{
				jumpDangerFlg = true;
				jumpDangerTimer.SetTotalTime(5);
				jumpDangerTimer.StartTimer();
			}
			//寄生虫を振り落とす
			parasiteTimer.SetTotalTime(15);
			parasite = 0;

			//着水後に勢いを持たせる
			moveY = playerMaxSpeedX;
			moveX = playerMaxSpeedX;

			jumpFlg = false;

		}
	}


}

//プレイヤーの状態を更新
void CPlayer::UpdateStatus(bool unDeadFlg, int tutorialStep, int eventNum)
{

	if (motion.GetMotionNo() != MOTION_STAND &&
		motion.IsEndMotion())
	{
		motion.ChangeMotion(MOTION_STAND);
	}

	//速度を座標に反映
	posX += moveX * moveSpeed;
	//ジャンプの高さには水流による速度upが入らないように
	if (jumpFlg)
	{
		posY += moveY;
	}
	else
	{
		posY += moveY * moveSpeed;
	}

	//ジャンプ可能
	//海面からどこまでがジャンプ可能範囲か
	if (GetRect().Top < SEA_LEVEL + JUMP_ZONE && !jumpFlg)
	{
		possibleToJumpFlg = true;
	}
	else
	{
		possibleToJumpFlg = false;
	}

	/*********
	 * 体温
	 *********/
	if (!jumpFlg && tutorialStep >= Task_End)
	{
		if (GetRect().Top < SEA_LEVEL + TEMPERATURE_CHANGEZONE)
		{
			if (tempRegion > HYPERTHERMIA_LIMIT)
			{
				if(eventNum == Event_Summer)
					tempRegion -= TEMPERATURE_LEVEL * 2;
				else
					tempRegion -= TEMPERATURE_LEVEL;
			}			
		}
		else if (GetRect().Top > UNDER_SEA - TEMPERATURE_CHANGEZONE)
		{
			if (tempRegion < FROZEN_LIMIT)
			{
				if(eventNum == Event_Winter)
					tempRegion += TEMPERATURE_LEVEL * 2;
				else
					tempRegion += TEMPERATURE_LEVEL;
			}
		}
		else
		{
			if(eventNum == Event_Summer)
				tempRegion -= TEMPERATURE_LEVEL * 2;
			else if(eventNum == Event_Winter)
				tempRegion += TEMPERATURE_LEVEL * 2;
			else
			{
				if (tempRegion < (FROZEN_LIMIT + HYPERTHERMIA_LIMIT) / 2)
				{
					tempRegion += TEMPERATURE_LEVEL / 3.0f;
				}
				else if (tempRegion > (FROZEN_LIMIT + HYPERTHERMIA_LIMIT) / 2)
				{
					tempRegion -= TEMPERATURE_LEVEL / 3.0f;
				}
			}
		}
	}

	if (causeOfDeath == CAUSE_None && !unDeadFlg)
	{
		//死因：熱中症
		if (tempRegion <= HYPERTHERMIA_LIMIT)
		{
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_Hyperthermia;
		}
		//死因：凍死
		if (tempRegion >= FROZEN_LIMIT)
		{
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_Frozen;
		}
	}

	//モーション切り替え用
	if (500 * (tempRegion * 0.01f) <= 150)
	{
		temperature = Temperature::Temp_Hot;
	}
	else if(500 * (tempRegion * 0.01f) >= 330)
	{
		temperature = Temperature::Temp_Cold;
	}
	else
	{
		temperature = Temperature::Temp_Normal;
	}


	/*********
	 * 寄生虫
	 *********/
	if (!jumpFlg && tutorialStep >= Task_Action)
	{
		if (parasite < PARASITE_LIMIT)
		{
			//タイマーセット
			parasiteTimer.StartTimer();
			if (parasiteTimer.GetNowtime() <= 0)
			{
				cSound->Play(SOUND_PARASITE_STICK);
				parasite += 1;
				if (causeOfDeath == CAUSE_None && !unDeadFlg)
				{
					if (parasite == PARASITE_LIMIT)
					{
						//死因：寄生死
						motion.ChangeMotion(MOTION_DEATH);
						causeOfDeath = CAUSE_Parasite;
					}
				}
				parasiteTimer.SetTotalTime(15);
			}
		}
	}

	/*********
	 * 空腹
	 *********/
	if (tutorialStep >= Task_Action)
	{
		if (hungerRegion <= STARVATION)
		{
			hungerRegion += HUNGRYLEVEL;
		}
		else if (hungerRegion >= STARVATION)
		{
			if (causeOfDeath == CAUSE_None)
			{
				if (causeOfDeath == CAUSE_None && !unDeadFlg)
				{
					if (causeOfDeath == CAUSE_None && !unDeadFlg)
					{
						//死因：餓死
						motion.ChangeMotion(MOTION_DEATH);
						causeOfDeath = CAUSE_Starvation;
					}
				}
			}
		}
	}
	

	/*********
	*  水流
	**********/
	if (waterFlowFlg)
	{
		waterFlowTimer.StartTimer();
		if (waterFlowTimer.GetNowtime() <= 0)
		{
			if (moveSpeed <= 1.0f)
			{
				waterFlowTimer.StopTimer();
				moveSpeed = 1.0f;
				waterFlowFlg = false;
			}
			else if(!jumpFlg)
			{
				moveSpeed -= WATERFLOW_SPEED;
			}

		}
		else if (WATERFLOW_MAXSPEED <= moveSpeed)
		{
			moveSpeed = WATERFLOW_MAXSPEED;
		}
		else
		{
			moveSpeed += WATERFLOW_SPEED;
		}
	}

	//無敵
	if (hitFlg)
	{
		hitTimer.StartTimer();
		//無敵の解除
		if (hitTimer.GetNowtime() <= 0)
		{
			hitTimer.StopTimer();
			hitFlg = false;
		}
	}
}

//更新
void CPlayer::Update(bool unDeadFlg, int tutorialStep,int eventNum)
{
	//アニメーションの更新
	motion.AddTimer(CUtilities::GetFrameSecond());

	//死亡アニメーションが終わり次第、deadflgをtrueにする
	if (motion.GetMotionNo() == MOTION_DEATH)
	{
		if (motion.IsEndMotion())
		{
			deadFlg = true;
		}
	}

	//プレイヤーが死んでいる場合、操作が行えないように
	if ((deadFlg || motion.GetMotionNo() == MOTION_DEATH) && !jumpFlg)
		return;

	//ステータス(状態)の更新
	UpdateStatus(unDeadFlg,tutorialStep,eventNum);

	//ジャンプ
	Jump(unDeadFlg,tutorialStep);

	//タイマー
	tempTimer.Update();
	hungerTimer.Update();
	parasiteTimer.Update();
	waterFlowTimer.Update();
	hitTimer.Update();
	brakeTimer.Update();
	if (!jumpFlg) jumpDangerTimer.Update();
	if (!jumpDangerTimer.GetUpdateFlg()) jumpDangerFlg = false;

	moveUpTaskTimer.Update();
	moveDownTaskTimer.Update();

	//チュートリアル
	if (GetMoveUpTask() && GetMoveDownTask() && taskCompleteStep == Task_Movement)
	{
		taskCompleteStep = Task_Action;
	}
	else if (eatTaskFlg && jumpTaskFlg && taskCompleteStep == Task_Action)
	{
		taskCompleteStep = Task_Complete;
	}

	//ジャンプ中は操作が行えないように
	if (jumpFlg)
		return;

	//移動更新
	UpdateMove(tutorialStep);
}

//描画
void CPlayer::Render(float wx, float wy)
{
	//プレイヤーが死んでいる場合
	if (deadFlg && !jumpFlg)
		return;

	//プレイヤーの描画
	switch (motion.GetMotionNo())
	{
		case MOTION_STAND:
			if(temperature == Temperature::Temp_Normal)
				standTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());
			else if (temperature == Temperature::Temp_Hot)
				hotStandTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());
			else
				coldStandTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());

			break;
		case MOTION_EAT:
			if (temperature == Temperature::Temp_Normal)
				eatTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());
			else if (temperature == Temperature::Temp_Hot)
				hotEatTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());
			else
				coldEatTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());

			break;
		case MOTION_JUMP:
			if (temperature == Temperature::Temp_Normal)
				jumpTexture.RenderScale(posX - wx, posY - wy, 1.8f, motion.GetSrcRect());
			else if (temperature == Temperature::Temp_Hot)
				hotJumpTexture.RenderScale(posX - wx, posY - wy, 1.8f, motion.GetSrcRect());
			else
				coldJumpTexture.RenderScale(posX - wx, posY - wy, 1.8f, motion.GetSrcRect());
			
			break;
		case MOTION_DEATH:
			if (temperature == Temperature::Temp_Normal)
				deathTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());
			else if (temperature == Temperature::Temp_Hot)
				hotDeathTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());
			else
				coldDeathTexture.RenderScale(posX - wx, posY - wy, 2.0f, motion.GetSrcRect());
			
			break;
	}
}

//デバッグ描画
void CPlayer::RenderDebug(float wx,float wy)
{
	//「ジャンプ」が可能
	if (possibleToJumpFlg)
	{
		CGraphicsUtilities::RenderString(200, 10, MOF_COLOR_BLACK, "<ジャンプ可能>");
	}

	//「エサを食べる」が可能
	if (GetEat())
	{
		CGraphicsUtilities::RenderString(200, 40, MOF_COLOR_BLACK, "<食べる可能>");
	}

	//プレイヤーの座標
	CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "X座標 : %d", GetPosX());
	CGraphicsUtilities::RenderString(10, 40, MOF_COLOR_BLACK, "Y座標 : %d", GetPosY());

	//本体の当たり判定の描画
	CGraphicsUtilities::RenderRect(
		GetRect().Left - wx,
		GetRect().Top - wy,
		GetRect().Right - wx,
		GetRect().Bottom - wy,
		MOF_COLOR_GREEN);

	//エサ探知範囲の描画
	CGraphicsUtilities::RenderRect(
		GetSearchRect().Left - wx,
		GetSearchRect().Top - wy,
		GetSearchRect().Right - wx,
		GetSearchRect().Bottom - wy,
		MOF_COLOR_GREEN);

	//目の当たり判定の描画
	CGraphicsUtilities::RenderRect(
		GetEyeRect().Left - wx,
		GetEyeRect().Top - wy,
		GetEyeRect().Right - wx,
		GetEyeRect().Bottom - wy,
		MOF_COLOR_GREEN);

	//体温
	CGraphicsUtilities::RenderString(10, 70, MOF_COLOR_BLACK, "体温 : %d", GetBodyTemp());
	//寄生虫
	CGraphicsUtilities::RenderString(10, 100, MOF_COLOR_BLACK, "寄生虫 : %d / 5", parasite);
	//腹減り
	CGraphicsUtilities::RenderString(10, 130, MOF_COLOR_BLACK, "空腹度 : %d / %d",(GetHungry() - 40) / 12, 10);
	//死因
	switch (causeOfDeath)
	{
		case CAUSE_None:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : なし(生存中)");
			break;
		case CAUSE_Hyperthermia:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : 熱中症");
			break;
		case CAUSE_Frozen:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : 凍死");
			break;
		case CAUSE_Starvation:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : 餓死");
			break;
		case CAUSE_ChokeOnShell:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : 喉つまり");
			break;
		case CAUSE_Obesity:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : 肥満");
			break;
		case CAUSE_Obstacle:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : 障害物に衝突");
			break;
		case CAUSE_Jump:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : ジャンプの衝撃");
			break;
		case CAUSE_Parasite:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : 寄生虫");
			break;
		case CAUSE_Bubble:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : 泡");
			break;
		case CAUSE_SeaTurtle:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : ウミガメショック");
			break;
		case CAUSE_WaterFlow:
			CGraphicsUtilities::RenderString(10, 160, MOF_COLOR_BLACK, "死因 : 加速死");
			break;
	}

	//進んだ距離
	CGraphicsUtilities::RenderString(10, 190, MOF_COLOR_BLACK, "%d m", GetDistance());
	
	//無敵(デバッグ用)
	if(hitFlg)
		CGraphicsUtilities::RenderString(10, 220, MOF_COLOR_BLACK, "無敵");
	CGraphicsUtilities::RenderString(10, 260, MOF_COLOR_BLACK, "最高速度 %d",playerMaxSpeedX);
}

//解放
void CPlayer::Release()
{
	standTexture.Release();
	eatTexture.Release();
	jumpTexture.Release();
	deathTexture.Release();

	hotStandTexture.Release();
	hotEatTexture.Release();
	hotJumpTexture.Release();
	hotDeathTexture.Release();

	coldStandTexture.Release();
	coldEatTexture.Release();
	coldJumpTexture.Release();
	coldDeathTexture.Release();

	motion.Release();
}


//敵(障害物、エサ、ウミガメ、泡、水流)との当たり判定
void CPlayer::Collision(CObstacleManager& cObstacle, int num, bool unDeadFlg, int tutorialStep)
{

	if ((deadFlg || motion.GetMotionNo() == MOTION_DEATH) && !jumpFlg)
	{
		return;
	}

	//敵の矩形と自分の矩形で当たり判定
	CRectangle prec = GetRect();

	//ウミガメ
	if (prec.CollisionRect(cObstacle.GetRect(Turtle, num)) &&
		cObstacle.GetShow(Turtle, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None && !unDeadFlg)
		{
			cSound->Play(SOUND_COLLISION);
			//衝突
			hitFlg = true;

			//死因：ショック死
			//当たった時点で即死
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_SeaTurtle;
		}
	}
	//画面内に4体目、5対目が出てくるのは今のところウミガメだけのため、処理を切り上げる
	if (num == 3 || num == 4)
	{
		return;
	}

	//魚群は最大でも二体までしか出ない
	if (num != 2)
	{
		//todo:死因を障害物と衝突にしてるので、あとで変更
		//魚群（イワシ）
		if (prec.CollisionRect(cObstacle.GetRect(ShoalSardine, num)) &&
			cObstacle.GetShow(ShoalSardine, num) && !hitFlg)
		{
			if (causeOfDeath == CAUSE_None && !unDeadFlg)
			{
				cSound->Play(SOUND_COLLISION);
				//衝突
				hitFlg = true;
				//死因：衝突死
				motion.ChangeMotion(MOTION_DEATH);
				causeOfDeath = CAUSE_ShoalFish;
			}
		}
		else if (prec.CollisionRect(cObstacle.GetRect(SwordFish, num)) &&
			cObstacle.GetShow(SwordFish, num) && !hitFlg)
		{
			if (causeOfDeath == CAUSE_None && !unDeadFlg)
			{
				cSound->Play(SOUND_COLLISION);
				//衝突
				hitFlg = true;
				//死因：衝突死
				motion.ChangeMotion(MOTION_DEATH);
				causeOfDeath = CAUSE_ShoalFish;
			}
		}
		else if (prec.CollisionRect(cObstacle.GetRect(SchoolTuna, num)) &&
			cObstacle.GetShow(SchoolTuna, num) && !hitFlg)
		{
			if (causeOfDeath == CAUSE_None && !unDeadFlg)
			{
				cSound->Play(SOUND_COLLISION);
				//衝突
				hitFlg = true;
				//死因：衝突死
				motion.ChangeMotion(MOTION_DEATH);
				causeOfDeath = SchoolTuna;
			}
		}

	}

	//障害物
	if (prec.CollisionRect(cObstacle.GetRect(Garbage, num)) &&
		cObstacle.GetShow(Garbage, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None && !unDeadFlg)
		{
			cSound->Play(SOUND_COLLISION);
			//衝突
			hitFlg = true;
			//死因：衝突死
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_Obstacle;
		}
	}
	//水流
	else if (prec.CollisionRect(cObstacle.GetRect(WaterFlow, num)) &&
		cObstacle.GetShow(WaterFlow, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None && !waterFlowFlg && !unDeadFlg)
		{
			cSound->Play(SOUND_WATERFLOW);
			//水流に当たったことを確認
			waterFlowFlg = true;
			//持続時間の設定
			waterFlowTimer.SetTotalTime(4);
			hitFlg = true;
			hitTimer.SetTotalTime(2);
		}
		else
		{
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_WaterFlow;
		}
		
	}

	//泡用の目の当たり判定
	prec = GetEyeRect();
	//泡
	if (prec.CollisionRect(cObstacle.GetRect(Bubble, num)) &&
		cObstacle.GetShow(Bubble, num) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None && !unDeadFlg)
		{
			cSound->Play(SOUND_BUBBLE_COLLISION);
			//衝突
			hitFlg = true;
			//泡死
			motion.ChangeMotion(MOTION_DEATH);
			causeOfDeath = CAUSE_Bubble;
		}
	}


	//エサの探知範囲
	prec = GetSearchRect();
	//エサ
	if (prec.CollisionRect(cObstacle.GetRect(FoodFish, num)) &&
		cObstacle.GetShow(FoodFish, num))
	{
		//探知範囲内にエサがある場合true
		possibleToEatFlg[num] = true;
		//エサを食べる
		if (Eat(false,unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, FoodFish, num);
		}
	}
	else if (prec.CollisionRect(cObstacle.GetRect(FoodShrimp, num)) &&
		cObstacle.GetShow(FoodShrimp, num))
	{
		//探知範囲内にエサがある場合true
		possibleToEatFlg[num] = true;
		//エサを食べる
		if (Eat(false, unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, FoodShrimp, num);
		}
	}
	else if (prec.CollisionRect(cObstacle.GetRect(FoodCrab, num)) &&
		cObstacle.GetShow(FoodCrab, num))
	{
		//探知範囲内にエサがある場合true
		possibleToEatFlg[num] = true;
		//エサを食べる
		if (Eat(false, unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, FoodCrab, num);
		}
	}
	//腐ったエサ
	else if (prec.CollisionRect(cObstacle.GetRect(RottenFish, num)) &&
		cObstacle.GetShow(RottenFish, num))
	{
		//探知範囲内にエサがある場合true
		possibleToEatFlg[num] = true;
		//エサを食べる
		if (Eat(true, unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, RottenFish, num);
		}
	}
	else if (prec.CollisionRect(cObstacle.GetRect(RottenShrimp, num)) &&
		cObstacle.GetShow(RottenShrimp, num))
	{
		//探知範囲内にエサがある場合true
		possibleToEatFlg[num] = true;
		//エサを食べる
		if (Eat(true, unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, RottenShrimp, num);
		}
	}
	else if (prec.CollisionRect(cObstacle.GetRect(RottenCrab, num)) &&
		cObstacle.GetShow(RottenCrab, num))
	{
		//探知範囲内にエサがある場合true
		possibleToEatFlg[num] = true;
		//エサを食べる
		if (Eat(true, unDeadFlg, tutorialStep))
		{
			cObstacle.SetShow(false, RottenCrab, num);
		}
	}

	else
	{
		//探知範囲内にエサがない場合false
		possibleToEatFlg[num] = false;
	}

}
