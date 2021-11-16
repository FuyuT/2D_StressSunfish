#pragma once
#include "PopUpWindowBase.h"
#include "Player.h"
class CCauseOfDeathWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonNextTexture;
	CTexture	caseOfDethTexture;

	const int			buttonNextPosX = 1400;
	const int			buttonNextPosY = 850;
	const int			causeOfDeathTexturePosX = 725;
	const int			causeOfDeathTexturePosY = 350;
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

