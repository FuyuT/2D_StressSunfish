#pragma once
#include "SceneBase.h"

class CSceneTitle : public CSceneBase
{
private:
	CTexture	buttonTexture;
public:
	CSceneTitle();
	~CSceneTitle();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

