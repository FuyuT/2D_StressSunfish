#pragma once
#include "SceneBase.h"
class CSceneGame : public CSceneBase
{
private:
public:
	CSceneGame();
	~CSceneGame();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

