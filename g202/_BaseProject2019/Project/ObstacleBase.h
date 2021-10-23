#pragma once
#include "Mof.h"
class CObstacleBase
{
protected:
	CTexture Texture;
	Vector2 initPos;
	Vector2 pos;
	Vector2 moveSpeed;
	bool    showFlg;
public:
	CObstacleBase() :
		pos(0, 0),
		moveSpeed(0, 0),
		showFlg(false)
	{};
	virtual ~CObstacleBase() {}
	virtual bool Load() { return true; }
	virtual void Initialize() {}
	virtual void Update(float wx, float wy) {}
	virtual void Render(float wx, float wy) {}
	virtual void RenderDebug(float wx, float wy) {}
	virtual void Release() {}
};

