#pragma once
#include "ObstacleBase.h"
#define  WATERFLOW_RECT_TOP_ADJ 0
#define  WATERFLOW_RECT_LEFT_ADJ 0
#define  WATERFLOW_RECT_RIGHT_ADJ 500
#define  WATERFLOW_RECT_BUTTOM_ADJ 300
class CWaterFlow : public CObstacleBase
{
private:
	CSpriteMotionController motion;

public:
	CWaterFlow();
	~CWaterFlow();
	bool Load()override;
	void Initialize()override;
	void Update(float wx, float wy)override;
	void Render(float wx, float wy)override;
	void RenderDebug(float wx, float wy)override;
	void Release()override;
	CRectangle GetRect() {
		return CRectangle(pos.x + WATERFLOW_RECT_LEFT_ADJ, pos.y + WATERFLOW_RECT_TOP_ADJ,
			pos.x + WATERFLOW_RECT_RIGHT_ADJ, pos.y +  WATERFLOW_RECT_BUTTOM_ADJ);
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

