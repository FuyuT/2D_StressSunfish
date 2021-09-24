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
	posX = 0;
	posY = 0;
	speedX = 0;
	speedY = 0;
	show = false;
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
	posX += speedX;
	if (posY >= g_pGraphics->GetTargetWidth()) {
		show = false;
	}
}

void Enemy::Render() {
	if (show) {
		return;
	}
	texture->Render(posX, posY);
}
