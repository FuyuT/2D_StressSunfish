#pragma once
#include "ObstacleBase.h"
class CTurtle : public CObstacleBase
{
private:

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
		return CRectangle(pos.x, pos.y, pos.x + Texture.GetWidth(), pos.y + Texture.GetHeight());
	}

};

