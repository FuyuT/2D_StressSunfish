#include "ShoalSardine.h"

CShoalSardine::CShoalSardine():
	warningLineShow(true)
{
}

CShoalSardine::~CShoalSardine()
{
}

bool CShoalSardine::Load()
{
	if (!Texture.Load("Obstacle\\mureanim.png"))return false;

	return true;
}

void CShoalSardine::Initialize()
{
	pos.x = 1000;
	pos.y = 1500;
	moveSpeed.x = 20.0f;
	warningLineShow = true;


	SpriteAnimationCreate anim = {
		"泳ぐ",
		0,0,
		446,286,
		TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},
			  {4,0,1},{4,1,1},{4,2,1},{4,3,1},
			  {4,0,2},{4,1,2},{4,2,2},{4,3,2},
			  {4,0,3},{4,1,3},{4,2,3},{4,3,3},
			  {4,0,4},{4,1,4},{4,2,4},{4,3,4},
			  {4,0,5},{4,1,5},{4,2,5},{4,3,5},
			  {4,0,6},{4,1,6},{4,2,6},{4,3,6},
			  {4,0,7},{4,1,7}}

	};
	motion.Create(anim);
}

void CShoalSardine::Update(float wx, float wy)
{
	if (!showFlg)return;

	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
	pos.x -= moveSpeed.x;

	//警告線
	int scRight = wx + g_pGraphics->GetTargetWidth(); //画面の右端
	//画面外にいる時、警告線を表示　画面内に入ったら警告線を消す
	if (scRight < pos.x)
	{
		warningLineShow = true;
	}
	else
	{
		warningLineShow = false;
	}

	motion.AddTimer(CUtilities::GetFrameSecond());
}

void CShoalSardine::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.RenderScale(pos.x - wx, pos.y - wy,1.0f,motion.GetSrcRect());
	
	//警告線の表示
	CRectangle rect = GetRect();
	if (warningLineShow)
	{
		CGraphicsUtilities::RenderFillRect(0,rect.Top - wy,
			g_pGraphics->GetTargetWidth(), rect.Bottom - wy, MOF_ARGB(100,255,0,0));
	}

}

void CShoalSardine::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CShoalSardine::Release()
{
	Texture.Release();
	motion.Release();
}