#include "Mof.h"
#pragma once
enum FISHSHADOW_NO{
	FISHSHADOW_NOT_SHOW,
	SARDINESHADOW,
	SWORDFISHSHADOW,
	TUNASHADOW
};
class CFishShadow
{
private:
	CTexture SardineShadow;
	CTexture SwordFishShadow;
	CTexture TunaShadow;
	short    fishShadowNo;
public:
	CFishShadow();
	~CFishShadow();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release();
};

