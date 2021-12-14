#pragma once
#include "PopUpWindowBase.h"
#include "Player.h"
#include "ResourceFont.h"

class CResultWindow : public CPopUpWindowBase
{
private:
	CResourceFont font;
	LPMofChar fileAdd = "Text\\PopRumCute.otf";
	LPMofChar fontName = "ポプらむ☆キュート";

	CFont		distanceFont;
	CTexture	popUpTexture;
	CTexture	buttonNextTexture;
	CTexture	resultTexture;
	CTexture	newGetTexture;

	CTexture	trophyTexture;
	CTexture	trophyTexture2;
	CTexture	trophyTexture3;

	const int			buttonNextPosX = 1400;
	const int			buttonNextPosY = 850;
	float				buttonNextScale = 1.0f;
	const int			trophyTexturePosX = 1400;
	const int			trophyTexturePosY = 220;
	const int			resultTextPosX = 800;
	const int			resultTextPosY = 250;

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

