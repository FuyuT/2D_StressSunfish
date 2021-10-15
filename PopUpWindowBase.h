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
	//�{�^���擾�p�ϐ�
	//1������
	//2���j���[��ʂ֑J��
	//3�^�C�g����ʂ֑J��
	//4�ݒ��ʂɑJ��
	int     buttonResult;

public:
	CPopUpWindowBase() {}
	virtual ~CPopUpWindowBase() {}
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}
	//�Q�b�^�[
	int GetButtonResult() { return buttonResult; }
	short GetNextPopUp() { return nextPopUp; }
	bool IsEnd() { return endFlg; }

};

