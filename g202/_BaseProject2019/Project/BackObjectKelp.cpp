#include "BackObjectKelp.h"

CBackObjectKelp::CBackObjectKelp()
{
}

CBackObjectKelp::~CBackObjectKelp()
{
}

bool CBackObjectKelp::Load()
{
	//�A�j���[�V�����摜
	if (!CUtility::EditDataLoad("Text\\konbu_test.txt", imageTotalNo, useImageTotalNo, imageArray, sameImageTotalNo, imagePosX, imagePosY))return false;
	SpriteAnimationCreate anim = {
	"�����",
	0,0,
	200,200,
	TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},{4,5,0},
		  {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},{4,5,1},
		  {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2},{4,5,2},
		  {4,0,3},{4,1,3},{4,2,3},{4,3,3},{4,4,3},{4,5,3},
		  {4,0,4},{4,1,4},{4,2,4},{4,3,4},{4,4,4},{4,5,4}}
	};
	motion.Create(anim);

	return true;
}

void CBackObjectKelp::Initialize()
{
	CUtility::EditDataPosInitialize("Text\\konbu_test.txt", imageTotalNo, useImageTotalNo, sameImageTotalNo, imagePosX, imagePosY);
}

void CBackObjectKelp::Update(const float& backGroundWidth, const float& scrollX)
{
	//�w�i�I�u�W�F�N�g�̃X�N���[���i�Ĕz�u�j
	for (int imageNo = 0; imageNo < imageTotalNo; imageNo++)
	{
		for (int sameTexNo = 0; sameTexNo < sameImageTotalNo[imageNo]; sameTexNo++)
		{
			if (imagePosX[imageNo][sameTexNo] + imageArray[imageNo].GetWidth() < scrollX)
			{
				imagePosX[imageNo][sameTexNo] += backGroundWidth;
			}
		}
	}

	motion.AddTimer(CUtilities::GetFrameSecond());
}

void CBackObjectKelp::Render(const float& backGroundWidth, const float& scrollX, const float& scrollY)
{
	//�e�L�X�g����ǂݍ��񂾉摜��`��(���z�j
	for (int imageNo = 0; imageNo < imageTotalNo; imageNo++)
	{
		for (int sameTexNo = 0; sameTexNo < sameImageTotalNo[imageNo]; sameTexNo++)
		{
			//��ʔ͈͓��̉摜�̂ݕ`��
			if (imagePosX[imageNo][sameTexNo] + imageArray[imageNo].GetWidth() > scrollX && scrollX + g_pGraphics->GetTargetWidth() > -scrollX + imagePosX[imageNo][sameTexNo])
			{
				imageArray[imageNo].Render(-scrollX + imagePosX[imageNo][sameTexNo], -scrollY + imagePosY[imageNo][sameTexNo], motion.GetSrcRect());
			}
		}
	}
}

void CBackObjectKelp::Release()
{
	for (int imageNo = 0; imageNo < imageTotalNo; imageNo++)
	{
		imageArray[imageNo].Release();
	}

	for (int n = 0; n < useImageTotalNo; n++)
	{
		delete[] imagePosX[n];
		delete[] imagePosY[n];
	}
	delete[] imagePosX;
	delete[] imagePosY;

	motion.Release();
}
