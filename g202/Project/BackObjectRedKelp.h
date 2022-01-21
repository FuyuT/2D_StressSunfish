#pragma once
#include "Mof.h"
#include "Utility.h"

class CBackObjectRedKelp
{
private:
	CTexture tex;
	int posTotalNo;
	Vector2 pos;
	//アニメーション
	CSpriteMotionController motion;
public:
	CBackObjectRedKelp();
	~CBackObjectRedKelp();
	bool Load(const CTexture& tex, Vector2 pos, int frameNo, int randomMin, int randomMax);
	void Initialize();
	void Update(const float& backGroundWidth, const float& scrollX);
	void Render(const float& backGroundWidth, const float& scrollX, const float& scrollY, const float renderScale);
	void Release();
};

