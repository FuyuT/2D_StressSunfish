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

