#include "BackObjectGreenKelp.h"

CBackObjectGreenKelp::CBackObjectGreenKelp()
{
}

CBackObjectGreenKelp::~CBackObjectGreenKelp()
{
}

bool CBackObjectGreenKelp::Load(const CTexture& tex, Vector2 pos, int frameNo, int randomMin, int randomMax)
{
	//画像を参照で取得
	this->tex = tex;
	//位置を読み込み
	this->pos = pos;
	//アニメーション
	if (frameNo < 0)
	{
		frameNo = CUtilities::Random(randomMin,randomMax);
	}
	SpriteAnimationCreate anim = {
	"みどりこんぶ",
	0,0,
	600,337.5,
	TRUE,{{frameNo,0,0},{frameNo,1,0},{frameNo,2,0},{frameNo,3,0},{frameNo,4,0},
		  {frameNo,0,1},{frameNo,1,1},{frameNo,2,1},{frameNo,3,1},{frameNo,4,1},
		  {frameNo,0,2},{frameNo,1,2},{frameNo,2,2},{frameNo,3,2},{frameNo,4,2},
		  {frameNo,0,3},{frameNo,1,3},{frameNo,2,3},{frameNo,3,3},{frameNo,4,3},
		  {frameNo,0,4},{frameNo,1,4},{frameNo,2,4},{frameNo,3,4},{frameNo,4,4},
		  {frameNo,0,5},{frameNo,1,5},{frameNo,2,5},{frameNo,3,5},{frameNo,4,5}}
	};
	motion.Create(anim);

	return true;
}

void CBackObjectGreenKelp::Initialize()
{

}

void CBackObjectGreenKelp::Update(const float& backGroundWidth, const float& scrollX)
{
	//背景オブジェクトのスクロール（再配置）
	//for (int n = 0; n < posTotalNo; n++)
	//{
	//	if (pos.x + tex.GetWidth() < scrollX)
	//	{
	//		pos.x += backGroundWidth;
	//	}
	//}

	motion.AddTimer(CUtilities::GetFrameSecond());

}

void CBackObjectGreenKelp::Render(const float& backGroundWidth, const float& scrollX, const float& scrollY, const float renderScale)
{
	//テキストから読み込んだ画像を描画(昆布）
    //画面範囲内の画像のみ描画
	tex.RenderScale(-scrollX + pos.x, -scrollY + pos.y, renderScale, motion.GetSrcRect());
	if (pos.x + tex.GetWidth() > scrollX && scrollX + g_pGraphics->GetTargetWidth() > -scrollX + pos.x)
	{
	}
}

void CBackObjectGreenKelp::Release()
{
	tex.Release();
	motion.Release();
}
