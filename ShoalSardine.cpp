#include "ShoalSardine.h"

CShoalSardine::CShoalSardine() 
{

}

CShoalSardine::~CShoalSardine()
{

}

bool CShoalSardine::Load()
{
	if (!Texture.Load("Obstacle\\mureanim.png"))return false;
	if (!keikokuTexture.Load("Obstacle\\gyogunanim2.png"))return false;

	return true;
}

void CShoalSardine::Initialize()
{
	pos.x = 1000;
	pos.y = 1500;
	moveSpeed.x = 20.0f;



	SpriteAnimationCreate anim = {
		"âjÇÆ",
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

	SpriteAnimationCreate keikoku_anim = {
		"åxçê",
		0,0,
		480,86,
		FALSE,{{4,0,0},{4,0,1},{4,0,2},{4,0,3},{4,0,4},{4,0,5},{4,0,6},{4,0,7},{4,0,8},{4,0,9},{4,0,10},{4,0,11},{4,0,12}}
	};

	motion.Create(anim);
	keikokumotion.Create(keikoku_anim);
	
	keikokumotion.AddTimer(CUtilities::GetFrameSecond());
}

void CShoalSardine::Update(float wx, float wy)
{
	if (!showFlg)return;

	//ÉXÉNÉäÅ[ÉìÇ©ÇÁèoÇΩÇÁshowFlgÇfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;

	//åxçêê¸
	int scRight = wx + g_pGraphics->GetTargetWidth(); //âÊñ ÇÃâEí[
	
	bool i;
	i = keikokumotion.ChangeMotion(1);
	if (i) 
	{
		pos.x = wx -  scRight;
		
	}
	else 
	{
		pos.x -= moveSpeed.x;
	}

	motion.AddTimer(CUtilities::GetFrameSecond());
	keikokumotion.AddTimer(CUtilities::GetFrameSecond());
	keikokumotion.ChangeMotion(0);
}

void CShoalSardine::Render(float wx, float wy)
{
	if (!showFlg)return;
	if (!keikokumotion.IsEndMotion()) {
		keikokuTexture.RenderScale(0, pos.y - wy, 4.0f, 1.0f, keikokumotion.GetSrcRect());
	}

		Texture.RenderScale(pos.x - wx, pos.y - wy, 1.0f, motion.GetSrcRect());
	
	
	//åxçêê¸ÇÃï\é¶
	/*CRectangle rect = GetRect();
	if (warningLineShow)
	{
		CGraphicsUtilities::RenderFillRect(0,rect.Top - wy,
			g_pGraphics->GetTargetWidth(), rect.Bottom - wy, MOF_ARGB(100,255,0,0));
	}
	*/

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
	keikokumotion.Release();
}