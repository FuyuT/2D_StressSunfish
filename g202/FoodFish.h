#pragma once
#include "ObstacleBase.h"
#define  FISH_RECT_TOP_ADJ 30
#define  FISH_RECT_LEFT_ADJ 10
#define  FISH_RECT_RIGHT_ADJ -15
#define  FISH_RECT_BUTTOM_ADJ -30
class CFoodFish : public CObstacleBase
{
private:

public:
	CFoodFish();
	~CFoodFish();
	bool Load()override;
	void Initialize()override;
	void Update(float wx, float wy)override;
	void Render(float wx, float wy)override;
	void RenderDebug(float wx, float wy)override;
	void Release()override;
	CRectangle GetRect(){
		return CRectangle(pos.x + FISH_RECT_LEFT_ADJ, pos.y + FISH_RECT_TOP_ADJ,
			pos.x + Texture.GetWidth() + FISH_RECT_RIGHT_ADJ, pos.y + Texture.GetHeight() + FISH_RECT_BUTTOM_ADJ);
	}
	void SetShow(bool flg)
	{
		showFlg = flg;
	}
	bool GetShow()
	{
		return showFlg;
	}
	void SetPosx(int posx)
	{
		pos.x = posx;
	}
	void SetPosy(int posy)
	{
		pos.y = posy;
	}
};

