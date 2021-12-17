 /*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"SceneTitle.h"
#include	"SceneGame.h"
#include	"SceneGameMenu.h"
#include	"SceneConfig.h"
#include	"SceneStressCollection.h"
#include	"SceneTrophyCollection.h"
#include	"SceneTutorial.h"

#include	"SoundManager.h"
CSoundManager cSound(false,false);
//シーンクラス
CSceneBase* nowScene = NULL;

//デバッグ用
bool debugShowFlg = false;
/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//リソースディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");
	cSound.Load();
	//シーンの初期化
	nowScene = new CSceneTitle;
	nowScene->SetSoundManager(cSound);
	nowScene->Load();
	nowScene->Initialize();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();

	//デバッグ用
	if (g_pInput->IsKeyPush(MOFKEY_0))
	{
		if (debugShowFlg) debugShowFlg = false;
		else if(!debugShowFlg) debugShowFlg = true;
	}

	//画面遷移
	nowScene->Update();
	if (nowScene->IsEnd())
	{
		//次のシーンの取得
		short nextScene = nowScene->GetNextScene();		
		//古いシーンの消去
		delete nowScene;
		//次のシーン番号に応じてシーンを作って初期化
		switch (nextScene)
		{
		case SCENENO_TITLE:
			nowScene = new CSceneTitle;
			break;
		case SCENENO_GAME:
			nowScene = new CSceneGame;
			break;
		case SCENENO_GAMEMENU:
			nowScene = new CSceneGameMenu;
			break;
		case SCENENO_CONFIG:
			nowScene = new CSceneConfig;
			break;
		case SCENENO_STRESSCOLLECTION:
			nowScene = new CSceneStressCollection;
			break;
		case SCENENO_TROPHY:
			nowScene = new CSceneTrophyCollection;
			break;
		case SCENENO_TUTORIAL:
			nowScene = new CSceneTutorial;
			break;
		}
		if (!nowScene->Load())return false;
		nowScene->SetSoundManager(cSound);
		nowScene->Initialize();
	}


	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
	
	//シーンの描画
	nowScene->Render();
	if (debugShowFlg)
	{
		nowScene->RenderDebug();
	}
	//サウンド
	//if (!cSound.GetMuteBGM())
	//{
	//	CGraphicsUtilities::RenderString(100, 500, "muteじゃない");
	//}
	//else
	//{
	//	CGraphicsUtilities::RenderString(100, 500, "mute中");
	//}

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	nowScene->Release();
	if (nowScene)
	{
		delete nowScene;
		nowScene = NULL;
	}
	cSound.Release();
	return TRUE;
}