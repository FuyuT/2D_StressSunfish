#include "SwordFish.h"

CSwordFish::CSwordFish()
{
}

CSwordFish::~CSwordFish()
{
}

bool CSwordFish::Load()
{
	if (!Texture.Load("Obstacle\\kajikianim.png"))return false;
	if (!keikokuTexture.Load("Obstacle\\gyogunanim2.png"))return false;

	SpriteAnimationCreate anim = {
		"泳ぐ",
		0,0,
		306,306,
		TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
			  {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
			  {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2},{4,5,2},
			  {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
			  {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}

	};
	SpriteAnimationCreate keikoku_anim[] = {
		"警告",
		0,0,
		480,86,
		FALSE,{{4,0,0},{4,0,1},{4,0,2},{4,0,3},{4,0,4},{4,0,5},{4,0,6},{4,0,7},{4,0,8},{4,0,9},{4,0,10},{4,0,11},{4,0,12}}
		,
		"空",
		0,0,
		0,0,
		FALSE,{{4,0,0}}
	};

	motion.Create(anim);
	keikokumotion.Create(keikoku_anim, 2);


	return true;
}

void CSwordFish::Initialize()
{
	pos.x = 1000;
	pos.y = 1500;
	showFlg = false;
	moveSpeed.x = 25.0f;
	keikokumotion.ChangeMotion(0, false);
	motion.AddTimer(CUtilities::GetFrameSecond());
}

void CSwordFish::Update(float wx, float wy)
{
	if (!showFlg)return;

	//警告線
	int scRight = wx + g_pGraphics->GetTargetWidth(); //画面の右端

	keikokumotion.ChangeMotion(0, false);
	if (!keikokumotion.IsEndMotion()) {
		pos.x = scRight;
	}
	else
	{

		pos.x -= moveSpeed.x;
	}

	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
	if (!showFlg)
	{
		keikokumotion.ChangeMotion(1, false);
	}

	motion.AddTimer(CUtilities::GetFrameSecond());
	keikokumotion.AddTimer(CUtilities::GetFrameSecond());
}

void CSwordFish::Render(float wx, float wy)
{

	if (!showFlg)return;
	if (!keikokumotion.IsEndMotion()) {
		keikokuTexture.RenderScale(0, pos.y - wy, 4.0f, 3.0f, keikokumotion.GetSrcRect());
	}
	else
	{
		Texture.RenderScale(pos.x - wx + 10, pos.y - wy, 1.0f, motion.GetSrcRect());
	}

}

void CSwordFish::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CSwordFish::Release()
{
	Texture.Release();
	motion.Release();
	keikokumotion.Release();
}
