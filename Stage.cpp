#include "Stage.h"

Stage::Stage() :
	texture(),
	scroll(0.0f),
	enemyStart(NULL),
	enemyCount(0),
	enemyTexture(),
	enemyNo(0) {
}

Stage::~Stage() {
}

bool Stage::Load() {
	if (texture.Load(NULL)) {
		return false;
	}
	if (!enemyTexture.Load("ÉEÉ~ÉKÉÅ ÉâÉt.png")) {
		return false;
	}
	return true;
}

void Stage::Initialize(ENEMYSTART* pSt, int cnt) {
//	scroll = 0;
	enemyNo = 0;
	enemyStart = pSt;
	enemyCount = cnt;

	Load();
}

void Stage::Update(Enemy* ene, int ecnt) {
	//scroll += SCROLL_SPEED;
	
	if (enemyNo < enemyCount && scroll >= enemyStart[enemyNo].scroll) {
		for (int i = 0; i < ecnt; i++) {
			if (ene[i].GetShow()) {
				continue;
			}
			ene[i].SetTexture(&enemyTexture);
			ene[i].Start(enemyStart[enemyNo].posX, 0,enemyStart[enemyNo].type);
			break;
		}
		enemyNo++;
	}
}

void Stage::Render() {
	int w = texture.GetWidth();
	int sch = g_pGraphics->GetTargetWidth();
	for (float x = ((int)scroll % w) - w; x < sch; x += w) {
		texture.Render(0.0f, w);
	}
}

void Stage::Release() {
	texture.Release();
	enemyTexture.Release();
}
