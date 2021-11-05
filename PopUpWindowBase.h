#pragma once
#include	"Mof.h"
#include "SceneTrophyCollection.h"

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
	//�����������Ă܂���@�\����Ȃ�
	int     buttonResult;
	int		dethResult;
	//�V�K����t���O
	bool	newGetDethFlg;
	bool	newGetTrophyFlg;
	int		numberOfTrophy[3];
public:
	CPopUpWindowBase() {}
	virtual ~CPopUpWindowBase() {}
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}
	//�Q�b�^�[
	int	  GetButtonResult() { return buttonResult; }
	void  SetButtonResult(int setButtonResult) { buttonResult = setButtonResult; }
	void  SetDethResult(int setDethResult) { dethResult = setDethResult; }
	void  SetNewGetDeth(bool setNewGetDethFlg) { newGetDethFlg = setNewGetDethFlg; }
	void  SetNewGetTrophy(bool setNewGetTrophyFlg) {newGetTrophyFlg = setNewGetTrophyFlg ; }
	//�g���t�B�[�|�b�v�A�b�v�p�@3�܂ŕۑ����Ď擾�ł���悤�ɂ���B
	void  SetNumberOfTrophy(int trophy[3]) {for (int i = 0; i < 3; i++) { numberOfTrophy[i] = trophy[i]; }}

	short GetNextPopUp() { return nextPopUp; }
	bool IsEnd() { return endFlg; }

};

