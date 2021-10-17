#include "Stage.h"

Stage::Stage() :
	texture(),
	scrollValueX(0.0f),
	scrollValueY(0.0f),
	enemyStart(NULL),
	enemyCount(0),
	enemyTexture(),
	enemyNo(0) {
}

Stage::~Stage() {
}

bool Stage::Load() {
	//�ǉ�
	if (texture.Load("SeaTexture.png")) 
	{
		return false;
	}

	if (!enemyTexture.Load("�E�~�K�� ����.png")) {
		return false;
	}
	if (!enemyTexture.Load("�E�~�K�� ���t.png")) {
		return false;
	}
	return true;
}

void Stage::Initialize(/*ENEMYSTART* pSt, int cnt*/) {
	//	scroll = 0;

	/*
	enemyNo = 0;
	enemyStart = pSt;
	enemyCount = cnt;
	*/
	Load();
}

void Stage::Update(Enemy* ene, /*int ecnt*/CPlayer& pl) {

	//�ǉ�
	//�X�N���[��
	CRectangle prec = pl.GetRect();
	//�X�N���[����
	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	//�X�e�[�W�̕��l���̋��E��
	float hsw = sw * 0.7f;
	float hsh = sh * 0.4f;
	//�X�e�[�W�S�̂̕� �Ƃ肠�����摜�̕���
	//float stgw = texture.GetWidth();
	float stgh = texture.GetHeight();

	//��
	if (prec.Left - scrollValueX < hsw)
	{
		//���E��hsw���i�񂾒l���AscrolValue�ɓ����
		scrollValueX -= hsw - (prec.Left - scrollValueX);
		if (scrollValueX <= 0)
		{
			scrollValueX = 0;
		}
	}
	//�E
	if (prec.Right - scrollValueX > sw - hsw)
	{
		scrollValueX += (prec.Right - scrollValueX) - (sw - hsw);
		/*
		if (scrollValueX >= 99999 - sw)
		{
			scrollValueX = 99999 - sw;
		}
		*/
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

	if (g_pInput->IsKeyPush(MOFKEY_U))
	{
		ene[0].SetTexture(&enemyTexture);
		ene[0].Start(g_pGraphics->GetTargetWidth() + scrollValueX, 1000, 3);
	}

	//if (enemyNo < enemyCount && scroll >= enemyStart[enemyNo].scroll) {
	//	for (int i = 0; i < ecnt; i++) {
	//		if (ene[i].GetShow()) {
	//			continue;
	//		}
	//		ene[i].SetTexture(&enemyTexture);
	//		ene[i].Start(enemyStart[enemyNo].posX, 0, enemyStart[enemyNo].type);
	//		break;
	//	}
	//	enemyNo++;
	//}
}

void Stage::Render() {

	//�ǉ�
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	//texture.Render(-scrollValueX, -scrollValueY);

	int w = texture.GetWidth();
	int h = texture.GetHeight();
	//int sch = g_pGraphics->GetTargetWidth();
	for (float y = ((int)-scrollValueY % h) - h; y < sch; y += h)
	{
		for (float x = ((int)-scrollValueX % w) - w; x < scw; x += w)
		{
			texture.Render(x, y);
		}
	}

	/*
	for (float x = ((int)scrollValueX % w) + w; x > sch; x -= w) {
		texture.Render(-scrollValueX - x, -scrollValueY);
	}
	*/
}

void Stage::Release() {
	texture.Release();
	enemyTexture.Release();
}
