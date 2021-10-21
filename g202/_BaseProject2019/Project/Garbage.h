#pragma once
#include "ObstacleBase.h"
class CGarbage : public CObstacleBase
{
private:
	bool turnFlg;
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

