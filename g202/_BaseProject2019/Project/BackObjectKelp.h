#pragma once
#include "Mof.h"
#include "Utility.h"
class CBackObjectKelp
{
private:
	int imageTotalNo;
	int useImageTotalNo;
	CTexture* imageArray;
	int* sameImageTotalNo;
	float** imagePosX;
	float** imagePosY;
	//アニメーション
	CSpriteMotionController motion;

public:
	CBackObjectKelp();
	~CBackObjectKelp();
	bool Load();
	void Initialize();
	void Update(const float& backGroundWidth, const float& scrollX);
	void Render(const float& backGroundWidth, const float& scrollX, const float& scrollY);
	void Release();
};

