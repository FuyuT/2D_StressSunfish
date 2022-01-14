#pragma once
#include "PopUpWindowBase.h"
#include "Player.h"

class CCheckCauseOfDeathWindow : public CPopUpWindowBase
{
private:
	CTexture	popUpTexture;
	CTexture	buttonBackTexture;
	CTexture	causeOfDeathTexture;

	//É{É^Éìç¿ïW
	const int			buttonBackPosX = 150;
	const int			buttonBackPosY = 100;
	float				buttonBackScale = 1.0f;

	const int			causeOfDeathTexturePosX = 750;
	const int			causeOfDeathTexturePosY = 340;
public:
	CCheckCauseOfDeathWindow();
	~CCheckCauseOfDeathWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void MouseCollision(int posX, int posY) override;
	CRectangle GetRect() {
		return CRectangle(buttonBackPosX, buttonBackPosY, buttonBackPosX + buttonBackTexture.GetWidth(), buttonBackPosY + buttonBackTexture.GetHeight());
	};
};

