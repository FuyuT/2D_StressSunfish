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

	const int			buttonConfigPosX = 850;
	const int			buttonConfigPosY = 500;
	const int			buttonRetryPosX = 850;
	const int			buttonRetryPosY = 600;
	const int			buttonTitlePosX = 850;
	const int			buttonTitlePosY = 700;
	const int			buttonReturnGamePosX = 850;
	const int			buttonReturnGamePosY = 800;

public:
	CPoseWindow();
	~CPoseWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
};

