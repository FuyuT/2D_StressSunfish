#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	if (!texture.Load("tempPlayer.png"))
	{
		return false;
	}
	return true;
}

void CPlayer::Initialize()
{
	Load();

	//初期値
	posX = 200;
	posY = g_pGraphics->GetTargetHeight() / 2 - texture.GetHeight() / 2;
}

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

	//海面(スクリーン上部)　移動制限
	if (posY + texture.GetHeight() > g_pGraphics->GetTargetHeight())
	{
		posY = g_pGraphics->GetTargetHeight() - texture.GetHeight();
		moveY = 0;
	}
	//海底(スクリーン下部)　移動制限
	if (posY < 0)
	{
		posY = 0;
		moveY = 0;
	}

	//速度を座標に反映
	scrollX += moveX;
	posX += moveX;
	posY += moveY;
}

void CPlayer::Update()
{
	//移動更新
	UpdateMove();

	if (g_pInput->IsKeyPush(MOFKEY_A))
	{
		if (GetSearchRect().CollisionRect(GetFeedRect()))
		{
			feedDeadFlg = true;
		}
	}

	//仮エサが左に動く(テスト用)
	if(!feedDeadFlg)
		feedPosX -= 1;

}

void CPlayer::Render()
{
	//プレイヤーの描画
	texture.Render(posX - scrollX, posY);

	//仮エサ描画(テスト用)
	if(!feedDeadFlg)
		CGraphicsUtilities::RenderFillRect(GetFeedRect(), MOF_COLOR_RED);

	//プレイヤーの座標(デバッグ)
	CGraphicsUtilities::RenderString(10, 10, "X座標 : %d", GetPosX());
	CGraphicsUtilities::RenderString(10, 40, "Y座標 : %d", GetPosY());

	//本体の当たり判定の描画(デバッグ)
	CGraphicsUtilities::RenderRect(
		GetRect(),MOF_COLOR_GREEN);

	//エサ探知範囲の描画(デバッグ)
	CGraphicsUtilities::RenderRect(
		GetSearchRect(),MOF_COLOR_GREEN);
}

void CPlayer::Release()
{
	texture.Release();
}
