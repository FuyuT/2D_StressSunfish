#pragma once
#include "PopUpWindowBase.h"
#include "Player.h"

class CCheckCauseOfDeathWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonBackTexture;
	CTexture	causeOfDeathTexture;

	const int			buttonBackPosX = 150;
	const int			buttonBackPosY = 100;
	float				buttonBackScale = 1.0f;
	const int			causeOfDeathTexturePosX = 725;
	const int			causeOfDeathTexturePosY = 350;
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

