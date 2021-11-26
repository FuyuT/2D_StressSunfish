#pragma once
#include "ObstacleBase.h"
#define  SHRIMP_RECT_TOP_ADJ -50
#define  SHRIMP_RECT_LEFT_ADJ -65
#define  SHRIMP_RECT_RIGHT_ADJ -90
#define  SHRIMP_RECT_BUTTOM_ADJ -110
class CFoodShrimp : public CObstacleBase
{
private:

public:
	CFoodShrimp();
	~CFoodShrimp();
	bool Load()override;
	void Initialize()override;
	void Update(float wx, float wy)override;
	void Render(float wx, float wy)override;
	void RenderDebug(float wx, float wy)override;
	void Release()override;
	CRectangle GetRect() {
		return CRectangle(pos.x + SHRIMP_RECT_LEFT_ADJ, pos.y + SHRIMP_RECT_TOP_ADJ,
			pos.x + Texture.GetWidth() + SHRIMP_RECT_RIGHT_ADJ, pos.y + Texture.GetHeight() + SHRIMP_RECT_BUTTOM_ADJ);
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

