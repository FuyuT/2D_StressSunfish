#include "FishShadow.h"

CFishShadow::CFishShadow()
{
}

CFishShadow::~CFishShadow()
{
}

bool CFishShadow::Load()
{
	if (!SardineShadow.Load("BackGround\\iwasi kage.png"))return false;
	if (!SwordFishShadow.Load("BackGround\\カジキ 影.png"))return false;
	if (!TunaShadow.Load("BackGround\\マグロ 影.png"))return false;
	return false;
}

void CFishShadow::Initialize()
{
}

void CFishShadow::Update()
{
}

void CFishShadow::Render()
{
}

void CFishShadow::RenderDebug()
{
}

void CFishShadow::Release()
{
}
