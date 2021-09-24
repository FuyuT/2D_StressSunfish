#pragma once
#include "SceneBase.h"

class CSceneGameMenu : public CSceneBase
{
private:
	bool flgTutorial = false;
public:
	CSceneGameMenu();
	~CSceneGameMenu();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;

	//�Q�b�^�[
	bool GetTutorialFlg(){ return flgTutorial; }
};

