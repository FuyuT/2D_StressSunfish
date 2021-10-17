#include"FoodFish.h"

CFoodFish::CFoodFish()
{
}

CFoodFish::~CFoodFish()
{
}

bool CFoodFish::Load()
{
	if (!Texture.Load("Obstacle\\Fish.png"))return false;

	return true;
}

//初期化
void CFoodFish::Initialize()
{
	pos.x = 1000;
	pos.y = 500;
	moveSpeed.x = 2.0f;
	showFlg = true;
}

void CFoodFish::Update(float wx, float wy)
{
	if (!showFlg)return;
	//移動
	pos.x -= moveSpeed.x;
	//スクリーンから出たらshowFlgをfalse
	if (pos.x + Texture.GetWidth() <= wx)showFlg = false;
}

void CFoodFish::Render(float wx, float wy)
{
	if (!showFlg)return;
	Texture.Render(pos.x - wx,pos.y - wy);
}

void CFoodFish::RenderDebug(float wx, float wy)
{
	if (!showFlg)return;
	CRectangle rect = GetRect();
	CGraphicsUtilities::RenderRect(rect.Left - wx, rect.Top - wy, rect.Right - wx, rect.Bottom - wy, MOF_COLOR_RED);

}

void CFoodFish::Release()
{
	Texture.Release();
}
