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

	const int			buttonBackPosX = 250;
	const int			buttonBackPosY = 200;
	const int			causeOfDeathTextureTexturePosX = 815;
	const int			causeOfDeathTextureTexturePosY = 350;
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

