#pragma once
#include "PopUpWindowBase.h"
class CContinueWindow : public CPopUpWindowBase
{
private:
	CTexture	popUpTexture;
	CTexture	buttonContinueTexture;
	CTexture	buttonMenuTexture;
	CTexture	buttonTitleTexture;
	CTexture	textTexture;

	const int			textPosX = 570;
	const int			textPosY = 250;
	const int			buttonPosX = 660;
	const int			buttonContinuePosY = 425;
	float				buttonContinueScale = 1.0f;
	const int			buttonMenuPosY = 575;
	float				buttonMenuScale = 1.0f;
	const int			buttonTitlePosY = 725;
	float				buttonTitleScale = 1.0f;

public:
	CContinueWindow();
	~CContinueWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void MouseCollision(int posX, int posY) override;
	CRectangle GetRect(int i);
};

