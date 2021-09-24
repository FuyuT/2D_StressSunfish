#pragma once
#include "SceneBase.h"

class CSceneTrophyCollection : public CSceneBase
{
private:
public:
	CSceneTrophyCollection();
	~CSceneTrophyCollection();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	};

