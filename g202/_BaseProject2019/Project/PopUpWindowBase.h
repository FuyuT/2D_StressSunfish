#pragma once
#include	"Mof.h"

//�V�[���̗�
enum tag_POPUPNO {
	POPUPNO_QUIT,
	POPUPNO_CAUSEOFDEATH,
	POPUPNO_CONTINUE,
	POPUPNO_BACKTOTITLE,
	POPUPNO_POSE,
	POPUPNO_RESULT,
	POPUPNO_RETRY,
	POPUPNO_TROPHY,
};

class CPopUpWindowBase
{
protected:
	int popUpPosX = 200;
	int popUpPosY = 50;
	bool endFlg = false;
	short	nextPopUp;

public:
	CPopUpWindowBase() {}
	virtual ~CPopUpWindowBase() {}
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}
	//�Q�b�^�[
	short GetNextPopUp() { return nextPopUp; }
	bool IsEnd() { return endFlg; }

};

