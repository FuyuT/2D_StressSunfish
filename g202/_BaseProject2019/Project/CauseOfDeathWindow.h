#pragma once
#include "PopUpWindowBase.h"
#include "Player.h"
#include "ResourceFont.h"

class CCauseOfDeathWindow : public CPopUpWindowBase
{
private:
	CTexture	popUpTexture;
	CTexture	deathTextTexture;
	CTexture	buttonNextTexture;
	CTexture	caseOfDethTexture;
	CTexture	newGetTexture;

	float				causeOfDeathScaleSpeed = 0.1f;
	float				popUpScale = 2.0f;;
	const int			buttonNextPosX = 1400;
	const int			buttonNextPosY = 850;
	float				buttonNextScale = 2.0f;
	bool				buttonNextScaleFlg;
	const int			causeOfDeathTexturePosX = 725;
	const int			causeOfDeathTexturePosY = 370;
	float				causeOfDeathTextureScale = 2.0f;
	const int			deathTextPosX = 830;
	const int			deathTextPosY = 210;
	float				deathTextScale = 2.0f;



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

