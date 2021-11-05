#pragma once
#include "PopUpWindowBase.h"

class CCheckCauseOfDeathWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonBackTexture;
	CTexture	causeOfDeathTexture;

	int			buttonBackPosX = 250;
	int			buttonBackPosY = 200;
	int			causeOfDeathTextureTexturePosX = 715;
	int			causeOfDeathTextureTexturePosY = 350;
public:
	CCheckCauseOfDeathWindow();
	~CCheckCauseOfDeathWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect() {
		return CRectangle(buttonBackPosX, buttonBackPosY, buttonBackPosX + buttonBackTexture.GetWidth(), buttonBackPosY + buttonBackTexture.GetHeight());
	};
};

