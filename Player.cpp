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
	hungry = FULL_STOMACH;
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
			if (hungry == FULL_STOMACH)
			{
				deadFlg = true;
				causeOfDeath = CAUSE_Obesity;
				//エサのshowFlgをfalseにする
				return false;
			}
		}

		//空腹を満たす
		hungry += FEED_SATIETYLEVEL;
		//満腹値を超えたら
		if (hungry > FULL_STOMACH)
		{
			hungry = FULL_STOMACH;
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
	posY += moveY * moveSpeed;


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
		//体温上昇
		if (temperature >= TEMPERATURE_LIMIT)
		{
			if (causeOfDeath == CAUSE_None)
			{
				//死因：熱中症
				deadFlg = true;
				causeOfDeath = CAUSE_Hyperthermia;
			}
		}
		else if (temperatureTime < 0)
		{
			temperature += 1;
			temperatureTime = TEMPERATURE_SPEED;
		}
		else
		{
			temperatureTime--;
		}

	}
	else if(GetRect().Top > UNDER_SEA - TEMPERATURE_CHANGEZONE)
	{
		//体温下降
		if (temperature <= 0)
		{
			if (causeOfDeath == CAUSE_None)
			{
				//死因：凍死
				deadFlg = true;
				causeOfDeath = CAUSE_Frozen;
			}
		}
		else if (temperatureTime < 0)
		{
			temperature -= 1;
			temperatureTime = TEMPERATURE_SPEED;
		}
		else
		{
			temperatureTime--;
		}
	}
	else
	{
		//体温が平温に近づく
		if (temperatureTime < 0)
		{
			if (temperature > TEMPERATURE_LIMIT / 2)
			{
				temperature -= 1;
			}
			else if (temperature < TEMPERATURE_LIMIT / 2)
			{
				temperature += 1;
			}
			temperatureTime = TEMPERATURE_SPEED * 2;
		}
		else
		{
			temperatureTime--;
		}
	}


	/*********
	 * 寄生虫
	 *********/
	if (parasite >= PARASITE_LIMIT)
	{
		if (causeOfDeath == CAUSE_None)
		{
			//死因：寄生死
			deadFlg = true;
			causeOfDeath = CAUSE_Parasite;
		}
	}
	else if (parasiteTime < 0)
	{
		parasite += 1;
		parasiteTime = PARASITE_SPEED;
	}
	else
	{
		parasiteTime--;
	}

	/*********
	 * 空腹
	 *********/
	if (hungry <= 0)
	{
		if (causeOfDeath == CAUSE_None)
		{
			//死因：餓死
			deadFlg = true;
			causeOfDeath = CAUSE_Starvation;
		}
	}
	else if (hungryTime < 0)
	{
		hungry -= 1;
		hungryTime = HUNGRY_SPEED;
	}
	else
	{
		hungryTime--;
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
	if (deadFlg)
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

}

//描画
void CPlayer::Render(float wx, float wy)
{
	//プレイヤーが死んでいる場合
	if (deadFlg)
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
		CGraphicsUtilities::RenderString(200, 10, MOF_COLOR_BLACK, "<食べる>");
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
	CGraphicsUtilities::RenderString(10, 70, MOF_COLOR_BLACK, "体温 : %d", GetTemperature());
	//寄生虫
	CGraphicsUtilities::RenderString(10, 100, MOF_COLOR_BLACK, "寄生虫 : %d / %d", GetParasite(),PARASITE_LIMIT / 50);
	//腹減り
	CGraphicsUtilities::RenderString(10, 130, MOF_COLOR_BLACK, "空腹度 : %d / %d", GetHungry(),FULL_STOMACH);
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
	
}

//解放
void CPlayer::Release()
{
	texture.Release();

}


//敵(障害物、エサ、ウミガメ、泡、水流)との当たり判定
void CPlayer::Collision(Enemy& ene)
{

	if (!ene.GetShow())
	{
		return;
	}

	//敵の矩形と自分の矩形で当たり判定
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();
	if (prec.CollisionRect(erec))
	{
		switch (ene.GetType())
		{
			//ウミガメ
			case 0:
				if (causeOfDeath == CAUSE_None)
				{
					//死因：ショック死
					//当たった時点で即死
					deadFlg = true;
					causeOfDeath = CAUSE_SeaTurtle;
				}
				break;
			//泡
			case 1:
				ene.SetShow(false);
				if (causeOfDeath == CAUSE_None)
				{
					//泡死
					//5%で死ぬ
					deadFlg = DieInPercentage(5);
					if (deadFlg)
						causeOfDeath = CAUSE_Bubble;
				}
				break;
			//障害物
			case 2:
				ene.SetShow(false);
				if (causeOfDeath == CAUSE_None)
				{
					//死因：衝突死
					//20%で死ぬ
					deadFlg = DieInPercentage(20);
					if (deadFlg)
						causeOfDeath = CAUSE_Obstacle;
				}
				break;
			//水流
			case 3:
				ene.SetShow(false);
				//速度が二倍に
				moveSpeed = 2.0f;
				//持続時間の設定
				streamTime = STREAM;
				break;

		}

	}

	//エサであるならば
	if (ene.GetType() == 4)
	{
		//エサとの当たり判定(エサ用のクラスがあるなら、新しくCollsionItem()とかを作ってそこに移す)
		prec = GetSearchRect();
		if (prec.CollisionRect(erec))
		{
			//探知範囲内にエサがある場合true
			possibleToEatFlg = true;

			//エサを食べる
			ene.SetShow(Eat());
		}
		else
		{
			//探知範囲内にエサがない場合false
			possibleToEatFlg = false;
		}
	}

}
