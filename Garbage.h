#pragma once
#include "ObstacleBase.h"

enum GARBAGE_NO {
	GARBAGE_NOT_SHOW,
	GARBAGE_SHOES,
	GARBAGE_TIRE,
	GARBAGE_BAG
};
class CGarbage : public CObstacleBase
{
private:
	#define		DECELERATE_SPEED		0.3f
	#define MAX_MOVE_SPEED  5.0f
	#define  SHOES_RECT_TOP_ADJ 10
	#define  SHOES_RECT_LEFT_ADJ 15
	#define  SHOES_RECT_RIGHT_ADJ -15
	#define  SHOES_RECT_BUTTOM_ADJ -10
	#define  TIRE_RECT_TOP_ADJ 10
	#define  TIRE_RECT_LEFT_ADJ 15
	#define  TIRE_RECT_RIGHT_ADJ 120
	#define  TIRE_RECT_BUTTOM_ADJ 110
	#define  BAG_RECT_TOP_ADJ 10
	#define  BAG_RECT_LEFT_ADJ 15
	#define  BAG_RECT_RIGHT_ADJ -15
	#define  BAG_RECT_BUTTOM_ADJ -10
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
		switch (garbageNo)
		{
		case GARBAGE_SHOES:
			return CRectangle(pos.x + SHOES_RECT_LEFT_ADJ, pos.y + SHOES_RECT_TOP_ADJ,
				pos.x + garbageShoes.GetWidth() + SHOES_RECT_RIGHT_ADJ, pos.y + garbageShoes.GetHeight() + SHOES_RECT_BUTTOM_ADJ);
			break;
		case GARBAGE_TIRE:
			return CRectangle(pos.x + TIRE_RECT_LEFT_ADJ, pos.y + TIRE_RECT_TOP_ADJ,
				pos.x + garbageShoes.GetWidth() + TIRE_RECT_RIGHT_ADJ, pos.y + garbageShoes.GetHeight() + TIRE_RECT_BUTTOM_ADJ);
			break;
		case GARBAGE_BAG:
			return CRectangle(pos.x + BAG_RECT_LEFT_ADJ, pos.y + BAG_RECT_TOP_ADJ,
				pos.x + garbageShoes.GetWidth() + BAG_RECT_RIGHT_ADJ, pos.y + garbageShoes.GetHeight() + BAG_RECT_BUTTOM_ADJ);
			break;
		default:
			break;
		}
		
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
	void SetGarbageNo(int no)
	{
		garbageNo = no;
	}
};

