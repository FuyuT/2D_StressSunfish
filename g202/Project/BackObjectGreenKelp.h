#pragma once
#include "Mof.h"
#include "Utility.h"

class CBackObjectGreenKelp
{
private:
	CTexture tex;
	int posTotalNo;
	Vector2 pos;
	//�A�j���[�V����
	CSpriteMotionController motion;
public:
	CBackObjectGreenKelp();
	~CBackObjectGreenKelp();
	bool Load(const CTexture& tex, Vector2 pos, int frameNo, int randomMax);
	void Initialize();
	void Update(const float& backGroundWidth, const float& scrollX);
	void Render(const float& backGroundWidth, const float& scrollX, const float& scrollY, const float renderScale);
	void Release();
};

