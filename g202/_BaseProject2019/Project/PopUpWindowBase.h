#pragma once
#include	"Mof.h"
#include "SceneTrophyCollection.h"
#include "ScaleController.h"
#include "ResourceFont.h"

constexpr int popUpPosX = 200;
constexpr int popUpPosY = 50;

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
	//�t�H���g
	CResourceFont font;
	LPMofChar fontAdd = "Text\\PopRumCute.otf";
	LPMofChar fontName = "�|�v��ށ��L���[�g";

	ScaleController	scaleController;
	bool endFlg = false;
	short	nextPopUp;
	//�����������Ă܂���@�\����Ȃ�
	int     buttonResult;
	int		deathResult;
	//�V�K����t���O
	bool	newGetDeathFlg;
	bool	newGetTrophyFlg;
	int		numberOfTrophy[3];
	int		distance;

	//�X�P�[���p�萔
	const float		scaleSpeed = 0.002f;
	const float		scaleMax = 1.05f;
	const float		scaleMini = 1.0f;
	//�{�^���I��p�ϐ�
	int	buttonSelect;
public:
	CPopUpWindowBase() {}
	virtual ~CPopUpWindowBase() {}
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}
	//�Q�b�^�[
	int	  GetButtonResult() { return buttonResult; }
	short GetNextPopUp() { return nextPopUp; }
	//
	void  SetButtonResult(int setButtonResult) { buttonResult = setButtonResult; }
	void  SetDethResult(int setDeathResult) { deathResult = setDeathResult; }
	void  SetNewGetDeath(bool setNewGetDeathFlg) { newGetDeathFlg = setNewGetDeathFlg; }
	void  SetNewGetTrophy(bool setNewGetTrophyFlg) {newGetTrophyFlg = setNewGetTrophyFlg ; }
	//�g���t�B�[�|�b�v�A�b�v�p�@3�܂ŕۑ����Ď擾�ł���悤�ɂ���B
	void SetNumberOfTrophy(int *trophy) {
		for (int i = 0; i < 3; i++)
		{
			numberOfTrophy[i] =trophy[i];
		}
	}
	void SetDistance(int i) { distance = i; };
	bool IsEnd() { return endFlg; }

};

