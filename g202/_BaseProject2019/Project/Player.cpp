#include "Player.h"

CPlayer::CPlayer() :
	texture(),
	posX(0.0f),
	posY(0.0f),
	moveX(0.0f),
	moveY(0.0f),
	moveSpeed(1.0f),
	beforeJumpingPosY(0.0f),
	random(),
	jumpFlg(false),
	deadFlg(false),
	jumpPossibleFlg(false),
	eatPossibleFlg(false)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	//プレイヤーのテクスチャの読みこみ
	if (!texture.Load("Player.png"))
	{
		return false;
	}

	return true;
}

void CPlayer::Initialize()
{
	Load();

	//確率のために使う変数の初期化
	random.SetSeed(time(NULL));

	//初期値
	posX = 200;
	posY = g_pGraphics->GetTargetHeight() / 2 - texture.GetHeight() / 2;
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
	if (posY + texture.GetHeight() > UNDER_SEA)
	{
		posY = UNDER_SEA - texture.GetHeight();
		moveY = 0;
	}
	
	//海面(スクリーン上部)　移動制限
	if (posY < SEA_LEVEL)
	{
		posY = SEA_LEVEL;
		moveY = 0;
	}
	
	
}

//エサを食べる
void CPlayer::Eat()
{
	//エサを食べる
	if (g_pInput->IsKeyPush(MOFKEY_A) &&
		eatPossibleFlg)
	{

		//死因：肥満
		if(hungry == FULL_STOMACH)
		{
			deadFlg = true;
			return;
		}

		//空腹を満たす
		hungry += FEED_SATIETYLEVEL;
		//満腹値を超えたら
		if (hungry > FULL_STOMACH)
		{
			hungry = FULL_STOMACH;
		}

		//死因：喉つまり
		//20%で死ぬ
		deadFlg = DieInPercentage(20);
	}
}

//ジャンプ
void CPlayer::Jump()
{
	//海面に近いときに A を押す 50は仮の数字
	if (g_pInput->IsKeyPush(MOFKEY_A) && !jumpFlg)
	{
		jumpFlg = true;	
		jumpPossibleFlg = false;

		//落下による勢いで少し潜るように 50は適当
		beforeJumpingPosY = posY + 50.0f;

		moveY = -JUMP_POWER_Y;
		moveX = JUMP_POWER_X;
	}
	else if (jumpFlg)
	{
		moveY += PLAYER_SPEED;
		if (posY > beforeJumpingPosY)
		{
			moveY = 0;
			moveX = 0;
			jumpFlg = false;
		}

	}
}

//更新
void CPlayer::Update()
{
	//プレイヤーが死んでいる場合
	if (deadFlg)
		return;

	//速度を座標に反映
	posX += moveX;
	posY += moveY;

	//ジャンプ
	Jump();

	//ジャンプ中は他の操作が行えないように
	if (jumpFlg)
		return;

	//移動更新
	UpdateMove();

	//エサを食べる
	Eat();

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
void CPlayer::RenderDebug()
{
	//デバッグ
	if (jumpFlg)
	{
		CGraphicsUtilities::RenderString(100, 100, "ジャンプ!!");
	}

	//プレイヤーの座標(デバッグ)
	CGraphicsUtilities::RenderString(10, 10, "X座標 : %d", GetPosX());
	CGraphicsUtilities::RenderString(10, 40, "Y座標 : %d", GetPosY());

	//本体の当たり判定の描画(デバッグ)
	CGraphicsUtilities::RenderRect(
		GetRect(), MOF_COLOR_GREEN);

	//エサ探知範囲の描画(デバッグ)
	CGraphicsUtilities::RenderRect(
		GetSearchRect(), MOF_COLOR_GREEN);
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
				//当たれば即死
				deadFlg = true;
				break;
			//泡
			case 1:
				//5%で死ぬ
				deadFlg = DieInPercentage(5);
				break;
			//障害物
			case 2:
				//20%で死ぬ
				deadFlg = DieInPercentage(20);
				break;
			//水流
			case 3:
				moveSpeed = 2.0f;
				break;

		}

	}

	//エサであるならば
	if (ene.GetType() == 3)
	{
		//エサとの当たり判定(エサ用のクラスがあるなら、新しくCollsionItem()とかを作ってそこに移す)
		prec = GetSearchRect();
		if (prec.CollisionRect(erec))
		{
			//探知範囲内にエサがある場合true
			eatPossibleFlg = true;
		}
		else
		{
			//探知範囲内にエサがない場合false
			eatPossibleFlg = false;
		}
	}

}
