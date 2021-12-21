#include "Fade.h"

CFade::CFade() :
	texture(),
	motion(),
	fadeOutEndFlg(false),
	startFlg(false)
{
}

CFade::~CFade()
{
}

void CFade::Load()
{
	if (texture.Load("bubbleFade.png"))
	{
		return;
	}
}

void CFade::Initialize()
{
	SpriteAnimationCreate anim[] = {
		//6か4どっちにしよ
		/*{
			"フェードアウト",
			0,0,
			480,270,
			FALSE,{{6,0,0},{6,1,0},{6,2,0},{6,3,0},{6,4,0},{6,5,0},
				   {6,0,1},{6,1,1},{6,2,1},{6,3,1},{6,4,1},{6,5,1},
				   {6,0,2},{6,1,2},{1,2,2}}
		},
		{
			"フェードイン",
			0,0,
			480,270,
			FALSE,{{6,3,2},{6,4,2},{6,5,2},
				   {6,0,3},{6,1,3},{6,2,3},{6,3,3},{6,4,3},{6,5,3},
				   {6,0,4},{6,1,4},{6,2,4},{6,3,4},{6,4,4},{6,5,4}}
		},*/
		{
			"フェードアウト",
			0,0,
			480,270,
			FALSE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
				   {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
				   {4,0,2},{4,1,2},{1,2,2}}
		},
		{
			"フェードイン",
			0,0,
			480,270,
			FALSE,{{4,3,2},{4,4,2},{4,5,2},
				   {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
				   {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}
		},
	};
	motion.Create(anim, FADE_MOTION_COUNT);

	fadeOutEndFlg = false;
	startFlg = false;
	//FadeIn();

}

void CFade::Update()
{

	if (motion.IsEndMotion())
	{
		if (motion.GetMotionNo() == FADE_MOTION_OUT)
		{
			fadeOutEndFlg = true;
		}
	}

	//アニメーションの更新
	motion.AddTimer(CUtilities::GetFrameSecond());
}

void CFade::Render()
{
	texture.RenderScale(-300, 0, 5.0f, motion.GetSrcRect());
}

void CFade::Release()
{
	texture.Release();
}
