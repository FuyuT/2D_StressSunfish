#pragma once
#include	"Mof.h"

//�V�[���̗�
enum tag_POPUPNO {
	POPUPNO_QUIT,
	POPUPNO_CAUSEOFDEATH,
	POPUPNO_CONTINUE,
	PUPUPNO_BACKTOTITLE,
	PUPUPNO_POSE,
	POPUPNO_RESULT,
	POPUPNO_RETRY,
	PUPUPNO_TROPHY,
};

class CPopUpWindowBase
{
protected:
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

