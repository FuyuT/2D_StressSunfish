#pragma once
#include "PopUpWindowBase.h"
class CPoseWindow : public CPopUpWindowBase
{
private:
	CTexture	textTexture;
	CTexture	popUpTexture;
	CTexture	buttonConfigTexture;
	CTexture	buttonRetryTexture;
	CTexture	buttonTitleTexture;
	CTexture	buttonReturnGameTexture;

	const int			textPosX = 790;
	const int			textPosY = 215;
	const int			buttonConfigPosX = 650;
	const int			buttonConfigPosY = 350;
	const int			buttonRetryPosX = 650;
	const int			buttonRetryPosY = 485;
	const int			buttonTitlePosX = 650;
	const int			buttonTitlePosY = 620;
	const int			buttonReturnGamePosX = 650;
	const int			buttonReturnGamePosY = 755;

public:
	CPoseWindow();
	~CPoseWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
};

