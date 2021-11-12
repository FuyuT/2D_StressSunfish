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
	if (!Texture.Load("Obstacle\\mure.png"))return false;

	return true;
}

void CShoalSardine::Initialize()
{
	pos.x = 1000;
	pos.y = 1500;
	moveSpeed.x = 20.0f;
	warningLineShow = true;
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
}

void CShoalSardine::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.Render(pos.x - wx, pos.y - wy);
	
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
}