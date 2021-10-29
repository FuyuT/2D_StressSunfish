#pragma once
#include "ObstacleBase.h"
#define		DECELERATE_SPEED		0.3f
#define MAX_MOVE_SPEED  5.0f
#define  GARBAGE_RECT_TOP_ADJ 10
#define  GARBAGE_RECT_LEFT_ADJ 15
#define  GARBAGE_RECT_RIGHT_ADJ -15
#define  GARBAGE_RECT_BUTTOM_ADJ -10

enum GARBAGE_NO {
	GarbageShoes,
	GarbageTire,
	GarbageBag
};
class CGarbage : public CObstacleBase
{
private:
	CTexture	garbageShoes;
	CTexture	garbageTire;
	CTexture	garbageBag;
	short garbageNo;
	bool moveUpFlg;
public:
	CGarbage();
	~CGarbage();
	bool Load()override;
	void Initialize()override;
	void Update(float wx, float wy)override;
	void Render(float wx, float wy)override;
	void RenderDebug(float wx, float wy)override;
	void Release()override;
	CRectangle GetRect() {
		return CRectangle(pos.x + GARBAGE_RECT_LEFT_ADJ, pos.y + GARBAGE_RECT_TOP_ADJ,
			pos.x + garbageShoes.GetWidth() + GARBAGE_RECT_RIGHT_ADJ, pos.y + garbageShoes.GetHeight() + GARBAGE_RECT_BUTTOM_ADJ);
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

