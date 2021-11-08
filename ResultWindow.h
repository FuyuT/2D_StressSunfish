#pragma once
#include "PopUpWindowBase.h"
class CResultWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonNextTexture;

	CTexture	trophyTexture;
	CTexture	trophyTexture2;
	CTexture	trophyTexture3;

	int			buttonNextPosX = 1500;
	int			buttonNextPosY = 850;
	int			trophyTexturePosX = 815;
	int			trophyTexturePosY = 350;
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

