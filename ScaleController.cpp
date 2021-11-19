#include "ScaleController.h"


ScaleController::ScaleController()
{
}

ScaleController::~ScaleController()
{
}


float ScaleController::ScaleControll(float scale, float max, float mini, float speed)
{
	if (scale <= max && scaleFlg)
		scale += speed;
	else
		scaleFlg = false;

	if (scale >= mini && !scaleFlg)
		scale -= speed;
	else
		scaleFlg = true;

	return scale;
}
