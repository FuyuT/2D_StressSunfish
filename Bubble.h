#pragma once
#include "ObstacleBase.h"
class CBubble : public CObstacleBase
{
private:
	#define  BUBBLE_RECT_TOP_ADJ 0
	#define  BUBBLE_RECT_LEFT_ADJ 0
	#define  BUBBLE_RECT_RIGHT_ADJ 0
	#define  BUBBLE_RECT_BUTTOM_ADJ 0

public:
	CBubble();
	~CBubble();
	bool Load()override;
	void Initialize()override;
	void Update(float wx, float wy)override;
	void Render(float wx, float wy)override;
	void RenderDebug(float wx, float wy)override;
	void Release()override;
	CRectangle GetRect() {
		return CRectangle(pos.x + BUBBLE_RECT_LEFT_ADJ, pos.y + BUBBLE_RECT_TOP_ADJ,
			pos.x + Texture.GetWidth() + BUBBLE_RECT_RIGHT_ADJ, pos.y + Texture.GetHeight() + BUBBLE_RECT_BUTTOM_ADJ);
	}
	bool GetShow()
	{
		return showFlg;
	}
	void SetShow(bool flg)
	{
		showFlg = flg;
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

