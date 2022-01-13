#include "SchoolTuna.h"

CSchoolTuna::CSchoolTuna()
{
}

CSchoolTuna::~CSchoolTuna()
{
}

bool CSchoolTuna::Load()
{
	if (!Texture.Load("Obstacle\\maguroanim.png"))return false;
	if (!keikokuTexture.Load("Obstacle\\gyogunanim2.png"))return false;

	SpriteAnimationCreate anim = {
		"泳ぐ",
		0,0,
		454.5,450,
		TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},{4,6,0},{4,7,0},
			  {4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},{4,6,0},{4,7,0},{4,8,0},
			  {4,2,0},{4,3,0},{4,4,0},{4,5,0},{4,6,0},{4,7,0},{4,8,0},{4,9,0},
			  {4,3,0},{4,4,0},{4,5,0},{4,6,0},{4,7,0},{4,8,0}}

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

void CSchoolTuna::Initialize()
{
	pos.x = 1000;
	pos.y = 1500;
	showFlg = false;
	moveSpeed.x = 13.0f;
	keikokumotion.ChangeMotion(0, false);
	motion.AddTimer(CUtilities::GetFrameSecond());
	showFlg = false;
}

void CSchoolTuna::Update(float wx, float wy)
{
	if (!showFlg)return;

	//警告線
	int scRight = wx + g_pGraphics->GetTargetWidth(); //画面の右端

	keikokumotion.ChangeMotion(0, false);
	if (!keikokumotion.IsEndMotion())
	{
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

void CSchoolTuna::Render(float wx, float wy)
{

	if (!showFlg)return;
	if (!keikokumotion.IsEndMotion())
	{
		keikokuTexture.RenderScale(0, pos.y - wy, 4.0f, 3.5f, keikokumotion.GetSrcRect());
	}
	else
	{
		Texture.RenderScale(pos.x - wx, pos.y - wy, 1.0f, motion.GetSrcRect());
	}
}

void CSchoolTuna::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);
}

void CSchoolTuna::Release()
{
	Texture.Release();
	motion.Release();
	keikokumotion.Release();
}
