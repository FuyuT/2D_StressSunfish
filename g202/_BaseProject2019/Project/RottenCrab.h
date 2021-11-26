#pragma once
#include "ObstacleBase.h"
#define  ROTTENHORSEMACKEREL_RECT_TOP_ADJ -50
#define  ROTTENHORSEMACKEREL_RECT_LEFT_ADJ -50
#define  ROTTENHORSEMACKEREL_RECT_RIGHT_ADJ -90
#define  ROTTENHORSEMACKEREL_RECT_BUTTOM_ADJ -90

class CRottenCrab : public CObstacleBase
{

private:

public:
	CRottenCrab();
	~CRottenCrab();
	bool Load()override;
	void Initialize()override;
	void Update(float wx, float wy)override;
	void Render(float wx, float wy)override;
	void RenderDebug(float wx, float wy)override;
	void Release()override;
	CRectangle GetRect() {
		return CRectangle(pos.x + ROTTENHORSEMACKEREL_RECT_LEFT_ADJ, pos.y + ROTTENHORSEMACKEREL_RECT_TOP_ADJ,
			pos.x + Texture.GetWidth() + ROTTENHORSEMACKEREL_RECT_RIGHT_ADJ, pos.y + Texture.GetHeight() + ROTTENHORSEMACKEREL_RECT_BUTTOM_ADJ);
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

