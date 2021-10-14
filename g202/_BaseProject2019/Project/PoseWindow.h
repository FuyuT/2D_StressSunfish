#pragma once
#include "PopUpWindowBase.h"
class CPoseWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonConfigTexture;
	CTexture	buttonRetryTexture;
	CTexture	buttonTitleTexture;
	CTexture	buttonReturnGameTexture;

	int			buttonConfigPosX = 850;
	int			buttonConfigPosY = 500;
	int			buttonRetryPosX = 850;
	int			buttonRetryPosY = 600;
	int			buttonTitlePosX = 850;
	int			buttonTitlePosY = 700;
	int			buttonReturnGamePosX = 850;
	int			buttonReturnGamePosY = 800;

public:
	CPoseWindow();
	~CPoseWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
};

