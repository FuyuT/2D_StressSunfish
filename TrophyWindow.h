#pragma once
#include "PopUpWindowBase.h"
class CTrophyWindow : public CPopUpWindowBase
{
private:
	CTexture	popUpTexture;
	CTexture	buttonBackTexture;
	CTexture	trophyTexture;

	const int			buttonBackPosX = 150;
	const int			buttonBackPosY = 100;
	float				buttonBackScale = 1.0f;
	const int			trophyTexturePosX = 815;
	const int			trophyTexturePosY = 375;
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

