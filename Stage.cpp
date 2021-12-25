#include "Stage.h"
#include "Utility.h"
Stage::Stage() :
	skyTex(),
	scrollValueX(0.0f),
	scrollValueY(0.0f),
	enemyCount(0),
	enemyTexture(),
	enemyNo(0) {
}

Stage::~Stage() {
}

bool Stage::Load() {
	//�w�i�摜
	if (!skyTex.Load("BackGround\\BackGround_1.png")) return false;
	if (!backWaveTex.Load("BackGround\\BackGround_2.png")) return false;
	if (!frontWaveTex.Load("BackGround\\BackGround_3.png")) return false;
	if (!distantBackGroundTex.Load("BackGround\\BackGround_4.png"))	return false;
	if (!insideBackGroundTex.Load("BackGround\\BackGround_5.png")) return false;
	if (!closeBackGroundTex.Load("BackGround\\BackGround_6.png")) return false;

	if (!ObjectKelp.Load())return false;
	return true;
}

void Stage::Initialize(/*ENEMYSTART* pSt, int cnt*/) {	
	scrollValueX = 0;
	backWavePos.x = 0;
	backWavePos.y = 0;
	backWaveSpeed.x = 0;
	backWaveSpeed.y = 0;
	backWaveScrollValueX = 0;
	backWaveTurnFlg = false;
	frontWavePos.x = 0;
	frontWavePos.y = 0;
	frontWaveScrollValueX = 0;

	ObjectKelp.Initialize();
}

void Stage::WaveUpdate(const CRectangle& rec, const float& hsw)
{
	//�g�𓮂���
	//��i�̔g
	//�E�ړ�
	backWaveScrollValueX += BACK_WAVE_SPEED;

	//�㉺�ړ�
	if (!backWaveTurnFlg && backWavePos.y > -100)
	{
		backWaveSpeed.y = -3;
	}
	else if (backWavePos.y < 0)
	{
		backWaveSpeed.y = 0;
		backWaveTurnFlg = true;
	}

	if (backWaveTurnFlg && backWavePos.y < 0)
	{
		backWaveSpeed.y = 3;
	}
	else if (backWavePos.y > 100)
	{
		backWaveTurnFlg = false;
	}
	backWavePos.y += backWaveSpeed.y;

	//�O�ʂ̔g
	//���ړ�
	frontWaveScrollValueX += FRONT_WAVE_SPEED;
	if (rec.Right - scrollValueX > hsw)
	{
		frontWaveScrollValueX += ((rec.Right - scrollValueX) - hsw) * FRONT_WAVE_ADJUSTMENT_SPEED;
	}
}

void Stage::Update(/*Enemy* ene, int ecnt*/CPlayer& pl) {

	//�ǉ�
	//�X�N���[��
	CRectangle prec = pl.GetRect();
	//�X�N���[����
	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	//�X�e�[�W�̕��l���̋��E��
	float hsw = sw * 0.3f;
	float hsh = sh * 0.4f;
	//�X�e�[�W�S�̂̕� �Ƃ肠�����摜�̕���
	float stgh = skyTex.GetHeight();
	
	WaveUpdate(prec,hsw);

	//�E
	if (prec.Right - scrollValueX > hsw)
	{
		scrollValueX += (prec.Right - scrollValueX) - hsw;
	}
	//��
	if (prec.Top - scrollValueY < hsh)
	{
		scrollValueY -= hsh - (prec.Top - scrollValueY);
		if (scrollValueY <= 0)
		{
			scrollValueY = 0;
		}
	}
	//��
	if (prec.Bottom - scrollValueY > sh - hsh)
	{
		scrollValueY += (prec.Bottom - scrollValueY) - (sh - hsh);
		if (scrollValueY >= stgh - sh)
		{
			scrollValueY = stgh - sh;
		}
	}

	//�w�i�̃I�u�W�F�N�g
	ObjectKelp.Update(closeBackGroundTex.GetWidth(), scrollValueX);

}

void Stage::Scroll(CTexture tex, float scrollSpeedX, float scrollSpeedY)
{
	//ScrollSpeed�͑傫���قǃX�N���[�����x���Ȃ�
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int w = tex.GetWidth();
	int h = tex.GetHeight();
	for (float y = ((int)(-scrollValueY * scrollSpeedY) % h) - h; y < sch; y += h)
	{
		for (float x = ((int)(-scrollValueX * scrollSpeedX) % w) - w; x < scw; x += w)
		{
			tex.Render(x, y);
		}
	}
}

void Stage::WaveRender()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int w = backWaveTex.GetWidth();
	int h = backWaveTex.GetHeight();
	////��ƉE�ɓ����g�@��i
	for (float x = ((int)-backWaveScrollValueX % w) - w; x < scw; x += w)
	{
		backWaveTex.Render(x, backWavePos.y - scrollValueY);
	}
	//���ɓ����g �O�i
	w = frontWaveTex.GetWidth();
	h = frontWaveTex.GetHeight();
	for (float x = ((int)-frontWaveScrollValueX % w) - w; x < scw; x += w)
	{
		frontWaveTex.Render(x, frontWavePos.y - scrollValueY);
	}

}

void Stage::BackGroundRender() {
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();

	int w = skyTex.GetWidth();
	int h = skyTex.GetHeight();
	Scroll(skyTex, 1, 1);
	WaveRender(); //�����g
	Scroll(distantBackGroundTex, 0.25, 1);
	Scroll(insideBackGroundTex, 0.5, 1);
}

void Stage::ForeGroundRender()
{
	Scroll(closeBackGroundTex, 1, 1);
}


void Stage::Render() {
	BackGroundRender();
	ObjectKelp.Render(closeBackGroundTex.GetWidth(), scrollValueX, scrollValueY);
}


void Stage::Release() {
	skyTex.Release();
	backWaveTex.Release();
	frontWaveTex.Release();
	distantBackGroundTex.Release();
	insideBackGroundTex.Release();
	closeBackGroundTex.Release();
	enemyTexture.Release();

	ObjectKelp.Release();
}
