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

	bool start;

public:
	CBlinking();
	~CBlinking();
	void Initialize();
	void Update();

	//�_�ł���񐔂̎w��(�t�F�[�h�C���A�t�F�[�h�A�E�g���Z�b�g��1��)
	void SetBlinkingCount(int blinkingCount) { count = blinkingCount; }
	//�_�ł��鑬���̎w��(�w�肵�������̔����̑����Ńt�F�[�h�C�����A�����̑����Ńt�F�[�h�A�E�g����)
	void SetBlinkingSpeed(int blinkingSpeed) { speed = blinkingSpeed; }
	//true������Ɠ_�ł��Ȃ���\�������
	void SetInStart(bool startFlg) { start = startFlg; }
	//�_�ł����񐔂�Ԃ�(0����J�E���g)
	int GetCount() { return countCheck; }
	//���݂̏�Ԃ�Ԃ�
	bool GetFadeIn() { return fadeIn; }
	bool GetFadeOut() { return fadeIn; }

	float GetAlpha() { return alpha; }
};

