#pragma once
#include "Mof.h"
#include "Timer.h"

class CBlinking
{
private:
	//�_�ł����
	int count;
	//�_�ł��鑬��
	int speed;

	float alpha;
	int effectCount;
	int countCheck;

	bool fadeIn;
	bool fadeOut;

public:
	CBlinking();
	~CBlinking();
	void Update();

	//�_�ł���񐔂̎w��(�t�F�[�h�C���A�t�F�[�h�A�E�g���Z�b�g��1��)
	void SetBlinkingCount(int blinkingCount) { count = blinkingCount; }
	//�_�ł��鑬���̎w��(�w�肵�������̔����̑����Ńt�F�[�h�C�����A�����̑����Ńt�F�[�h�A�E�g����)
	void SetBlinkingSpeed(int blinkingSpeed) { speed = blinkingSpeed; }
	//true������Ɠ_�ł��Ȃ���\�������
	void SetInStart(bool startFlg) { fadeIn = startFlg; }
	
	float GetAlpha() { return alpha; }
};

