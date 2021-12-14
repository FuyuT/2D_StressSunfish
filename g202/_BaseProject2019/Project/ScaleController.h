#pragma once
#include "mof.h"

class ScaleController
{
private:
	bool scaleFlg = true;

public:
	ScaleController();
	~ScaleController();
	float ScaleControll(float scale ,float max ,float mini , float speed);
	float ScaleShrinkControll(float scale, float mini, float speed);
	void ScaleRender(CTexture* tx , int posX, int posY , float scale);
};

