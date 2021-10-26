#pragma once
#include "PopUpWindowBase.h"
class CTrophyWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonBackTexture;
	CTexture	trophyTexture;

	int			buttonBackPosX = 250;
	int			buttonBackPosY = 200;
	int			trophyTexturePosX = 815;
	int			trophyTexturePosY = 350;
public:
	CTrophyWindow();
	~CTrophyWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect() {
		return CRectangle(buttonBackPosX, buttonBackPosY, buttonBackPosX + buttonBackTexture.GetWidth(), buttonBackPosY + buttonBackTexture.GetHeight());
	};
};

