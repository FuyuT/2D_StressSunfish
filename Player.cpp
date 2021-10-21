#include "Player.h"

CPlayer::CPlayer() :
	texture(),
	posX(0.0f),
	posY(0.0f),
	moveX(0.0f),
	moveY(0.0f),
	moveSpeed(1.0f),
	random(),
	jumpFlg(false),
	deadFlg(false),
	possibleToJumpFlg(false),
	possibleToEatFlg(false),
	hungry(10),
	temperature(50)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	//プレイヤーのテクスチャの読みこみ
	if (!texture.Load("マンボウ.png"))
	{
		return false;
	}

	return true;
}

void CPlayer::Initialize()
{
	//読み込みを行う
	Load();

	//確率のために使う変数の初期化
	random.SetSeed(time(NULL));

	/********
	* 初期値
	*********/
	//座標
	posX = 200;   // 200は適当　仮置き
	posY = g_pGraphics->GetTargetHeight() / 2 - texture.GetHeight() / 2;
	//状態(ステータス)
	temperature = TEMPERATURE_LIMIT / 2;
	bodyTemp = 10;
	tempRegion = 245;
	hungry = FULL_STOMACH;
	hungerRegion = 40;
	parasite = 0;
	moveX = 0.0f;
	moveY = 0.0f;
	moveSpeed = 1.0f;
	causeOfDeath = CAUSE_None;
	//タイマー
	hungryTime = HUNGRY_SPEED;

	//フラグ
	jumpFlg = false;
	deadFlg = false;
	possibleToEatFlg = false;
	possibleToJumpFlg = false;
	//(デバッグ用)
	hitFlg = false;

	//UIタイマー
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);
}

//移動
void CPlayer::UpdateMove()
{

	//右に移動
	if (g_pInput->IsKeyHold(MOFKEY_D))
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

	//上に移動
	if (g_pInput->IsKeyHold(MOFKEY_W))
	{
		moveY -= PLAYER_SPEED;
		if (moveY < -PLAYER_MAXSPEED)
		{
			moveY = -PLAYER_MAXSPEED;
		}
	}
	//下に移動
	else if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		moveY += PLAYER_SPEED;
		if (moveY > PLAYER_MAXSPEED)
		{
			moveY = PLAYER_MAXSPEED;
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
	if (!g_pInput->IsKeyHold(MOFKEY_D) && 
		!g_pInput->IsKeyHold(MOFKEY_W) && 
		!g_pInput->IsKeyHold(MOFKEY_S))
	{
		posY += GRAVITY;
	}

	
	//海底(スクリーン下部)　移動制限
	if (GetRect().Bottom > UNDER_SEA)
	{
		posY = UNDER_SEA - texture.GetHeight() + COLLISION_ADJUSTMENT;
		moveY = 0;
	}
	
	//海面(スクリーン上部)　移動制限
	if (GetRect().Top < SEA_LEVEL)
	{
		posY = SEA_LEVEL - COLLISION_ADJUSTMENT;
		moveY = 0;
	}
	
	
}

//エサを食べる
bool CPlayer::Eat()
{
	//エサを食べる
	if (g_pInput->IsKeyPush(MOFKEY_A))
	{
		
		possibleToEatFlg = false;

		if (causeOfDeath == CAUSE_None)
		{
			//死因：肥満
			if (/*hungry == FULL_STOMACH*/
				hungerRegion == 40)
			{
				deadFlg = true;
				causeOfDeath = CAUSE_Obesity;
				//エサのshowFlgをfalseにする
				return false;
			}
		}

		//空腹を満たす
		//hungry += FEED_SATIETYLEVEL;
		hungerRegion -= 24;
		//満腹値を超えたら
		/*if (hungry > FULL_STOMACH)
		{
			hungry = FULL_STOMACH;
		}*/
		if (hungerRegion < 40)
		{
			hungerRegion = 40;
		}

		
		if (causeOfDeath == CAUSE_None)
		{
			//死因：喉つまり
			//20%で死ぬ
			deadFlg = DieInPercentage(20);
			if (deadFlg)
				causeOfDeath = CAUSE_ChokeOnShell;
		}

		//エサのshowFlgをfalseにする
		return false;
	}

	//エサを食べなかったときは、エサのshowFlgをtrueのままにする
	return true;
}

//ジャンプ
void CPlayer::Jump()
{
	//海面に近いときに A を押す
	//海面から +40(適当)以内の範囲内であれば
	if (g_pInput->IsKeyPush(MOFKEY_A) &&
		possibleToJumpFlg )
	{
		jumpFlg = true;	
		possibleToJumpFlg = false;
		//寄生虫を振り落とす
		parasite = 0;

		moveY = -JUMP_POWER_Y;
		moveX = JUMP_POWER_X;
	}
	else if (jumpFlg)
	{
		moveY += PLAYER_SPEED;

		//海面より下か(海に戻ったか)
		//落下による勢いで少し潜るように +50(適当)
		if (posY > SEA_LEVEL + 50.0f)
		{
			moveY = 0;
			moveX = 0;
			jumpFlg = false;
			if (causeOfDeath == CAUSE_None)
			{
				//死因：衝撃死
				//10%で死ぬ
				deadFlg = DieInPercentage(10);
				if (deadFlg)
					causeOfDeath = CAUSE_Jump;
			}
		}

	}
}

//プレイヤーの状態を更新
void CPlayer::UpdateStatus()
{
	if (deadFlg)
	{
		//死ぬアニメーションの再生とか
	}

	//速度を座標に反映
	posX += moveX * moveSpeed;
	if (jumpFlg)
	{
		posY += moveY;
	}
	else {
		posY += moveY * moveSpeed;
	}


	//ジャンプ可能
	//40は仮の数字 海面からどれくらいの範囲がジャンプ可能エリアか
	if (GetRect().Top < SEA_LEVEL + 40.0f &&
		!jumpFlg)
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

	if (GetRect().Top < SEA_LEVEL + TEMPERATURE_CHANGEZONE)
	{
		tempTimer.StartTimer();
		if (tempTimer.GetNowtime() <= 0)
		{
			if (bodyTemp < 50)
			{
				bodyTemp += 1;
				tempRegion -= 4.1;
				tempTimer.SetTotalTime(1);
			}
			else if (bodyTemp >= 50)
			{
				if (causeOfDeath == CAUSE_None)
				{
					//死因：熱中症
					deadFlg = true;
					causeOfDeath = CAUSE_Hyperthermia;
				}
			}
		}
	}
	else if(GetRect().Top > UNDER_SEA - TEMPERATURE_CHANGEZONE)
	{
		tempTimer.StartTimer();
		if (tempTimer.GetNowtime() <= 0)
		{
			if (bodyTemp > -30)
			{
				bodyTemp -= 1;
				tempRegion += 4.1;
				tempTimer.SetTotalTime(1);
			}
			else if (bodyTemp <= -30)
			{
				if (causeOfDeath == CAUSE_None)
				{
					//死因：凍死
					deadFlg = true;
					causeOfDeath = CAUSE_Frozen;
				}
			}
		}

	}
	else
	{
		if (bodyTemp > 10)
		{
			//タイマーセット
			tempTimer.StartTimer();
			if (tempTimer.GetNowtime() <= 0)
			{
				bodyTemp -= 1;
				tempRegion += 4.1;
				tempTimer.SetTotalTime(2);
			}
		}
		else if (bodyTemp < 10)
		{
			//タイマーセット
			tempTimer.StartTimer();
			if (tempTimer.GetNowtime() <= 0)
			{
				bodyTemp += 1;
				tempRegion -= 4.1;
				tempTimer.SetTotalTime(2);
			}
		}

	}


	/*********
	 * 寄生虫
	 *********/
	if (parasite < 5)
	{
		//タイマーセット
		parasiteTimer.StartTimer();
		if (parasiteTimer.GetNowtime() <= 0)
		{
			parasite += 1;
			if (parasite == 5)
			{
				if (causeOfDeath == CAUSE_None)
				{
					//死因：寄生死
					deadFlg = true;
					causeOfDeath = CAUSE_Parasite;
				}
			}
			parasiteTimer.SetTotalTime(15);
		}
	}

	/*********
	 * 空腹
	 *********/
	hungerTimer.StartTimer();
	if (hungerTimer.GetNowtime() <= 0)
	{
		if (hungerRegion <= 148)
		{
			hungerRegion += 12;
			//hungry -= 1;
		    if (/*hungry == 0*/
				hungerRegion == 160)
		    {
			    if (causeOfDeath == CAUSE_None)
			    {
				    //死因：餓死
				    deadFlg = true;
				    causeOfDeath = CAUSE_Starvation;
			    }
		    }
			hungerTimer.SetTotalTime(3);
		}		
	}

	//水流
	if (streamTime > 0)
	{
		streamTime--;
	}
	else if (moveSpeed > 1.0f)
	{
		// 0.1 ずつ減速
		moveSpeed -= 0.1f;
		// 速度の倍率が 1.0 以下になったら 1.0 で初期化
		if (moveSpeed < 1.0f)
		{
			moveSpeed = 1.0f;
		}
	}

}

//更新
void CPlayer::Update()
{
	//プレイヤーが死んでいる場合
	if (deadFlg && !jumpFlg)
		return;

	//ステータス(状態)の更新
	UpdateStatus();

	//ジャンプ
	Jump();

	//ジャンプ中は他の操作が行えないように
	if (jumpFlg)
		return;

	//移動更新
	UpdateMove();

	//無敵(デバッグ用)
	if (hitFlg)
	{
		//無敵の解除
		if (g_pInput->IsKeyPush(MOFKEY_H))
		{
			hitFlg = false;
		}
	}

	tempTimer.Update();
	hungerTimer.Update();
	parasiteTimer.Update();
}

//描画
void CPlayer::Render(float wx, float wy)
{
	//プレイヤーが死んでいる場合
	if (deadFlg && !jumpFlg)
		return;

	//プレイヤーの描画
	texture.Render(posX - wx, posY - wy);
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
	if (possibleToEatFlg)
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
	}

	//進んだ距離
	CGraphicsUtilities::RenderString(10, 190, MOF_COLOR_BLACK, "%d m", GetDistance());
	
	//無敵(デバッグ用)
	CGraphicsUtilities::RenderString(10, 220, MOF_COLOR_BLACK, "「H」で無敵の解除(長靴や泡の上で連打すると確率で死ねる)");
	if(hitFlg)
		CGraphicsUtilities::RenderString(10, 250, MOF_COLOR_BLACK, "無敵");
}

//解放
void CPlayer::Release()
{
	texture.Release();
}


//敵(障害物、エサ、ウミガメ、泡、水流)との当たり判定
void CPlayer::Collision(CObstacleManager& cObstacle)
{
	//SetShowがあれば実装する
	/*if (!cObstacle.getshow())
	{
		return;
	}*/

	if (deadFlg && !jumpFlg)
	{
		return;
	}

	//敵の矩形と自分の矩形で当たり判定
	CRectangle prec = GetRect();

	//ウミガメ
	if (prec.CollisionRect(cObstacle.GetRect(Turtle)) && !hitFlg)
	{
		if (causeOfDeath == CAUSE_None)
		{
			//デバッグ用
			hitFlg = true;

			//死因：ショック死
			//当たった時点で即死
			deadFlg = true;
			causeOfDeath = CAUSE_SeaTurtle;
		}
	}
	//泡
	else if (prec.CollisionRect(cObstacle.GetRect(Bubble)) && !hitFlg)
	{
		//ene.SetShow(false);
		if (causeOfDeath == CAUSE_None)
		{
			//デバッグ用
			hitFlg = true;

			//泡死
			//5%で死ぬ
			deadFlg = DieInPercentage(5);
			if (deadFlg)
				causeOfDeath = CAUSE_Bubble;
		}
	}
	//障害物
	else if (prec.CollisionRect(cObstacle.GetRect(Garbage)) && !hitFlg)
	{

		//ene.SetShow(false);
		if (causeOfDeath == CAUSE_None)
		{
			//デバッグ用
			hitFlg = true;

			//死因：衝突死
			//20%で死ぬ
			deadFlg = DieInPercentage(20);
			if (deadFlg)
				causeOfDeath = CAUSE_Obstacle;
		}
	}
	////水流
	//else if (prec.CollisionRect(cObstacle.GetRect(WaterFlow)))
	//{
	//	//ene.SetShow(false);
	//		//速度が二倍に
	//	moveSpeed = 2.0f;
	//	//持続時間の設定
	//	streamTime = STREAM;
	//}

	//エサの探知範囲
	prec = GetSearchRect();
	//エサ
	if (prec.CollisionRect(cObstacle.GetRect(FoodFish)) ||
		prec.CollisionRect(cObstacle.GetRect(FoodShrimp)) ||
		prec.CollisionRect(cObstacle.GetRect(FoodCrab)))
	{
		//探知範囲内にエサがある場合true
		possibleToEatFlg = true;
		//エサを食べる
		Eat();

		//ene.SetShow();
	}
	else
	{
		//探知範囲内にエサがない場合false
		possibleToEatFlg = false;
	}

}
