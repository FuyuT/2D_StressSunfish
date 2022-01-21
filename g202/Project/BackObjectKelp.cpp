#include "BackObjectKelp.h"

CBackObjectKelp::CBackObjectKelp()
{
}

CBackObjectKelp::~CBackObjectKelp()
{
}

bool CBackObjectKelp::Load(const CTexture& tex, int posTotalNo, Vector2 pos, int frameNo, int randomMin, int randomMax)
{
	//�摜���Q�ƂŎ擾
	this->tex = tex;
	//�ő吔
	this->posTotalNo = posTotalNo;
	//�ʒu��ǂݍ���
	this->pos = pos;

	if (frameNo < 0)
	{
		frameNo = CUtilities::Random(randomMin,randomMax);
	}
	SpriteAnimationCreate anim = {
	"�����",
	0,0,
	600,337.5,
	TRUE,{{frameNo,0,0},{frameNo,1,0},{frameNo,2,0},{frameNo,3,0},{frameNo,4,0},
		  {frameNo,0,1},{frameNo,1,1},{frameNo,2,1},{frameNo,3,1},{frameNo,4,1},
		  {frameNo,0,2},{frameNo,1,2},{frameNo,2,2},{frameNo,3,2},{frameNo,4,2},
		  {frameNo,0,3},{frameNo,1,3},{frameNo,2,3},{frameNo,3,3},{frameNo,4,3},
		  {frameNo,0,4},{frameNo,1,4},{frameNo,2,4},{frameNo,3,4},{frameNo,4,4},
		  {frameNo,0,5},{frameNo,1,5},{frameNo,2,5},{frameNo,3,5},{frameNo,4,5}}
	};
	motion.Create(anim);

	return true;
}

void CBackObjectKelp::Initialize()
{
}

void CBackObjectKelp::Update(const float& backGroundWidth, const float& scrollX)
{
	CRectangle rect = motion.GetSrcRect();
	//�w�i�I�u�W�F�N�g�̃X�N���[���i�Ĕz�u�j
	for (int n = 0; n < posTotalNo; n++)
	{
		if (pos.x + (rect.Right - rect.Left) < scrollX)
		{
			pos.x += backGroundWidth;
		}
	}

	motion.AddTimer(CUtilities::GetFrameSecond());
}

void CBackObjectKelp::Render(const float& backGroundWidth, const float& scrollX, const float& scrollY, const float renderScale)
{
	CRectangle rect = motion.GetSrcRect();

	//�e�L�X�g����ǂݍ��񂾉摜��`��(���z�j
	//��ʔ͈͓��̉摜�̂ݕ`��
	if (pos.x + (rect.Right - rect.Left) > scrollX && scrollX + g_pGraphics->GetTargetWidth() > -scrollX + pos.x)
	{
		tex.RenderScale(-scrollX + pos.x, -scrollY + pos.y, renderScale, motion.GetSrcRect());
	}
}

void CBackObjectKelp::Release()
{
	tex.Release();
	motion.Release();
}
