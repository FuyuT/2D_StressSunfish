#pragma once
#include "PopUpWindowBase.h"
#include "Player.h"
class CResultWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CFont		distanceFont;
	CTexture	popUpTexture;
	CTexture	buttonNextTexture;

	CTexture	trophyTexture;
	CTexture	trophyTexture2;
	CTexture	trophyTexture3;

	const int			buttonNextPosX = 1400;
	const int			buttonNextPosY = 850;
	const int			trophyTexturePosX = 1400;
	const int			trophyTexturePosY = 220;

	char		meter[10];
public:
	CResultWindow();
	~CResultWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect() {
		return CRectangle(buttonNextPosX, buttonNextPosY, buttonNextPosX + buttonNextTexture.GetWidth(), buttonNextPosY + buttonNextTexture.GetHeight());
	};
};

