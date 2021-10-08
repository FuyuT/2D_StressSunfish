#include "Stage.h"

Stage::Stage() :
	texture(),
	scroll(0.0f) {
}

Stage::~Stage() {
}

bool Stage::Load() {
	if (texture.Load(NULL)) {
		return false;
	}
	return true;
}

//void Stage::Initialize() {
//	scroll = 0;
//}

//void Stage::Update() {
//	scroll += SCROLL_SPEED;
//}

void Stage::Render() {
	int w = texture.GetWidth();
	int sch = g_pGraphics->GetTargetWidth();
	for (float x = ((int)scroll % w) - w; x < sch; x += w) {
		texture.Render(0.0f, w);
	}
}

void Stage::Release() {
	texture.Release();
}
