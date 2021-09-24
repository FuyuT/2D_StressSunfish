#pragma once
#include "SceneBase.h"

class CSceneConfig :public CSceneBase
{
private:
public:
	CSceneConfig();
	~CSceneConfig();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

