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
	const int			buttonPosX = 680;
	const int			buttonConfigPosY = 350;
	float				buttonConfigScale = 0.9f;
	const int			buttonRetryPosY = 485;
	float				buttonRetryScale = 0.9f;
	const int			buttonTitlePosY = 620;
	float				buttonTitleScale = 0.9f;
	const int			buttonReturnGamePosY = 755;
	float				buttonReturnGameScale = 0.9f;

	const float			buttonScaleMini = 0.9f;
	const float			buttonScaleMax = 0.95f;

public:
	CPoseWindow();
	~CPoseWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void MouseCollision(int posX, int posY) override;
	CRectangle GetRect(int i);
};

