#include "ScaleController.h"


ScaleController::ScaleController()
{
}

ScaleController::~ScaleController()
{
}

/*************************************************************************//*!
		@brief			画像の拡大縮小アニメーション
		@param			元画像のスケール値
						大きさの最大値
						大きさの最小値
						拡大縮小のスピード

		@return			拡大縮小したスケール値
*//**************************************************************************/
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

/*************************************************************************//*!
		@brief			画像の縮小アニメーション
		@param			元画像のスケール値
						大きさの最小値
						拡大縮小のスピード

		@return			縮小したスケール値
*//**************************************************************************/
float ScaleController::ScaleShrinkControll(float scale, float mini, float speed)
{
	if (scale >= mini)
		scale -= speed;
	return scale;
}

/*************************************************************************//*!
		@brief			画像の拡大縮小描画
		@param			画像のポインタ
						画像のX座標
						画像のY座標
						画像のスケール値

		@return			
*//**************************************************************************/
void ScaleController::ScaleRender(CTexture* tx, int posX, int posY , float scale)
{
	tx->RenderScale(posX + tx->GetWidth() / 2, posY + tx->GetHeight() / 2, scale , TEXALIGN_CENTERCENTER);
}
