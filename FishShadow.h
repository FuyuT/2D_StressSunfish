#pragma once
#include "ObstacleBase.h"

enum FISHSHADOW_NO{
	FISHSHADOW_NOT_SHOW,
	SARDINESHADOW,
	SWORDFISHSHADOW,
	TUNASHADOW
};
class CFishShadow:public CObstacleBase
{
private:
	#define MAX_MOVE_SPEED  5.0f
	CTexture SardineShadow;
	CTexture SwordFishShadow;
	CTexture TunaShadow;
	short    fishShadowNo;
public:
	CFishShadow();
	~CFishShadow();
	bool Load();
	void Initialize();
	void Update(float wx, float wy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();

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
	void SetSpeed(float speed)
	{
		moveSpeed.x = speed;
	}
	void SetFishShadowNo(int no)
	{
		fishShadowNo = no;
	}
};

