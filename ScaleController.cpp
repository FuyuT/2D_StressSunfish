#include "ScaleController.h"


ScaleController::ScaleController()
{
}

ScaleController::~ScaleController()
{
}

/*************************************************************************//*!
		@brief			�摜�̊g��k���A�j���[�V����
		@param			���摜�̃X�P�[���l
						�傫���̍ő�l
						�傫���̍ŏ��l
						�g��k���̃X�s�[�h

		@return			�g��k�������X�P�[���l
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
		@brief			�摜�̏k���A�j���[�V����
		@param			���摜�̃X�P�[���l
						�傫���̍ŏ��l
						�g��k���̃X�s�[�h

		@return			�k�������X�P�[���l
*//**************************************************************************/
float ScaleController::ScaleShrinkControll(float scale, float mini, float speed)
{
	if (scale >= mini)
		scale -= speed;
	return scale;
}

/*************************************************************************//*!
		@brief			�摜�̊g��k���`��
		@param			�摜�̃|�C���^
						�摜��X���W
						�摜��Y���W
						�摜�̃X�P�[���l

		@return			
*//**************************************************************************/
void ScaleController::ScaleRender(CTexture* tx, int posX, int posY , float scale)
{
	tx->RenderScale(posX + tx->GetWidth() / 2, posY + tx->GetHeight() / 2, scale , TEXALIGN_CENTERCENTER);
}
