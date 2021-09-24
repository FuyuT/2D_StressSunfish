#pragma once
#include "SceneBase.h"

class CSceneStressCollection : public CSceneBase
{
private:
public:
	CSceneStressCollection();
	~CSceneStressCollection();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

