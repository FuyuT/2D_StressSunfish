#pragma once
#include "ObstacleBase.h"
#define  SHOALSARDINE_RECT_TOP_ADJ 150
#define  SHOALSARDINE_RECT_LEFT_ADJ 0
#define  SHOALSARDINE_RECT_RIGHT_ADJ -0
#define  SHOALSARDINE_RECT_BUTTOM_ADJ -150

class CShoalSardine :public CObstacleBase
{
private:
	bool warningLineShow;
public:
	CShoalSardine();
	~CShoalSardine();
	bool Load()override;
	void Initialize()override;
	void Update(float wx, float wy)override;
	void Render(float wx, float wy)override;
	void RenderDebug(float wx, float wy)override;
	void Release()override;
	CRectangle GetRect() {
		return CRectangle(pos.x + SHOALSARDINE_RECT_LEFT_ADJ, pos.y + SHOALSARDINE_RECT_TOP_ADJ,
			pos.x + Texture.GetWidth() + SHOALSARDINE_RECT_RIGHT_ADJ, pos.y + Texture.GetHeight() + SHOALSARDINE_RECT_BUTTOM_ADJ);
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

