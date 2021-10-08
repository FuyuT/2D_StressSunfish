#include "Enemy.h"

Enemy::Enemy() :
	texture(NULL),
	posX(0.0f),
	posY(0.0f),
	speedX(0.0f),
	speedY(0.0f),
	show(false) {

}

Enemy::~Enemy() {
}

void Enemy::Initialize() {
	posX = 1800;
	posY = 1000;
	speedX = 1;
	speedY = 0;
	show = true;
}

void Enemy::Start(float px, float py) {
	posX = px - texture->GetWidth();
	posY = py - texture->GetHeight() * 0.5f;
	speedX = 1;
	speedY = 0;
	show = true;
}

void Enemy::Update() {
	if (!show) {
		return;
	}
	posX -= speedX;
	/*
	if (posY >= g_pGraphics->GetTargetWidth()) {
		show = false;
	}
	*/
}

void Enemy::Render(float wx, float wy) {
	if (!show) {
		return;
	}
	CGraphicsUtilities::RenderFillRect(
		GetRect().Left - wx,
		GetRect().Top - wy,
		GetRect().Right - wx,
		GetRect().Bottom - wy,
		MOF_COLOR_RED); 

	//texture->Render(posX, posY);
}
