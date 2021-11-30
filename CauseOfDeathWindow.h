#pragma once
#include "PopUpWindowBase.h"
#include "Player.h"
class CCauseOfDeathWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	deathTextTexture;
	CTexture	buttonNextTexture;
	CTexture	caseOfDethTexture;
	CTexture	newGetTexture;

	const int			buttonNextPosX = 1400;
	const int			buttonNextPosY = 850;
	float				buttonNextScale = 1.0f;
	const int			causeOfDeathTexturePosX = 725;
	const int			causeOfDeathTexturePosY = 370;
	const int			deathTextPosX = 830;
	const int			deathTextPosY = 210;

public:
	CCauseOfDeathWindow();
	~CCauseOfDeathWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect() {
		return CRectangle(buttonNextPosX, buttonNextPosY, buttonNextPosX + buttonNextTexture.GetWidth(), buttonNextPosY + buttonNextTexture.GetHeight());
	};
};

