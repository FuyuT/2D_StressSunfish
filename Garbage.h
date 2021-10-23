#pragma once
#include "ObstacleBase.h"
#define		DECELERATE_SPEED		0.3f
#define MAX_MOVE_SPEED  5.0f

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
		return CRectangle(pos.x, pos.y, pos.x + Texture.GetWidth(), pos.y + Texture.GetHeight());
	}

};

