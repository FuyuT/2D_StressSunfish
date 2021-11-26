#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "ObstacleManager.h"
#include "Ui.h"
#include "Stage.h"

class CSceneGame : public CSceneBase
{
private:
	CPlayer pl;
	Stage stg;
	CObstacleManager cObstacle;
	CUi ui;

	int playerX = 100;
	int playerY = 100;

	int distancePlayer = 0;

	Vector2 moveSpeed;
	/*CTexture backGroundTexture;*/
	CTexture playerTexture;

	/*float scrollValueX;
	float scrollValueY;*/

	//��Q��
	int posX;
	int posY;
	CTexture seaTurtleTexture;
	bool deadFlag;

	//�ݒ��ʃt���O
	bool configFlg = false;
	//�|�[�Y��ʃt���O
	bool poseFlg;
	//�V�K����t���O
	bool newGetTrophy;
	bool newGetDeth;
	//�g���t�B�[�p�z��
	int	numberOfTrophy[3];
	//�J�n�t���O
	bool startFlg;

public:
	CSceneGame();
	~CSceneGame();
	void PlayBGM() override;
	bool Load()override;
	void Initialize() override;
	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void Release() override;

	CRectangle GetRect() {
		return CRectangle(playerX, playerY, playerX + playerTexture.GetWidth() , playerY + playerTexture.GetHeight());
	};
		/*
	//�ǉ�
	float GetScrollX()
	{
		return scrollValueX;
	};
	float GetScrollY()
	{
		return scrollValueY;
	}
	*/
	/*CRectangle GetRect() {
		return CRectangle(playerX, playerY, playerX + playerTexture.GetWidth() , playerY + playerTexture.GetHeight());
	};*/

	/*CRectangle GetRect()
	{
		return CRectangle(
			ePosX,
			ePosY,
			ePosX + 100,
			ePosY + 100
		);
	}
	int GetType()
	{
		return 0;
	}*/


	void PopUpController();
	void CaseOfDethController();
	void TrophyController();
};

