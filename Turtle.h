#pragma once
#include "ObstacleBase.h"


class CTurtle : public CObstacleBase
{
private:
	#define  TURTLE_RECT_TOP_ADJ 150
	#define  TURTLE_RECT_LEFT_ADJ 0
	#define  TURTLE_RECT_RIGHT_ADJ 400
	#define  TURTLE_RECT_BOTTOM_ADJ 350
	//アニメーション
	CSpriteMotionController motion;

public:
	CTurtle();
	~CTurtle();
	bool Load()override;
	void Initialize()override;
	void Update(float wx, float wy)override;
	void Render(float wx, float wy)override;
	void RenderDebug(float wx, float wy)override;
	void Release()override;
	CRectangle GetRect() {
		return CRectangle(pos.x + TURTLE_RECT_LEFT_ADJ, pos.y + TURTLE_RECT_TOP_ADJ,
			pos.x + TURTLE_RECT_RIGHT_ADJ, pos.y + TURTLE_RECT_BOTTOM_ADJ);
	}
	bool GetShow()
	{
		return showFlg;
	}
	float GetPosX() { return pos.x; }
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

