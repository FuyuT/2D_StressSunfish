#pragma once
#include "ObstacleBase.h"
#define  CRAB_RECT_TOP_ADJ -50
#define  CRAB_RECT_LEFT_ADJ -50
#define  CRAB_RECT_RIGHT_ADJ -90
#define  CRAB_RECT_BUTTOM_ADJ -90

class CFoodCrab : public CObstacleBase
{
private:
	
public:
	CFoodCrab();
	~CFoodCrab();
	bool Load()override;
	void Initialize()override;
	void Update(float wx, float wy)override;
	void Render(float wx, float wy)override;
	void RenderDebug(float wx, float wy)override;
	void Release()override;
	CRectangle GetRect() {
		return CRectangle(pos.x + CRAB_RECT_LEFT_ADJ, pos.y + CRAB_RECT_TOP_ADJ,
			pos.x + Texture.GetWidth() + CRAB_RECT_RIGHT_ADJ, pos.y + Texture.GetHeight() + CRAB_RECT_BUTTOM_ADJ);
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

