#include "SceneTutorial.h"
#include "SceneConfig.h"
#include "PoseWindow.h"
#include "BackToTitleWindow.h"
#include "RetryWindow.h"

CPopUpWindowBase* nowPopUpTutorial = NULL;
//GameAppで遷移すると設定画面からゲームシーンに戻った際にゲームシーンが初期化されるため、
//ここで宣言し、ゲームシーンの上から設定画面を表示するようにする。
CSceneConfig sceneConfigT;

CSceneTutorial::CSceneTutorial():
	fBuffer(NULL),
	fBufferOffset(0),
	mShowDelay(0),
	messageEndFlg(false),
	tutorialStep(0),
	poseFlg(false)
{
}

CSceneTutorial::~CSceneTutorial()
{
}

////////////////////////////
// メソッド
////////////////////////////

//テキストの読込み
bool CSceneTutorial::TextLoad()
{
	//テキストファイルを開く
	FILE* fp = fopen("Text\\Tutorial.txt", "rt");
	if (fp == NULL)
	{
		return false;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);  //fpの位置をファイルの終端へ
	long fSize = ftell(fp);  //ファイルの読み書き位置を取得、位置で容量を求める
	fseek(fp, 0, SEEK_SET);  //fpの位置をファイルの先頭へ
	//ファイルの容量文のメモリをmallocで動的に確保
	fBuffer = (char*)malloc(fSize + 1);  //終端に\0を含めるため、+1
	//バッファにファイルを全て読み込む
	fSize = fread(fBuffer, 1, fSize, fp);
	fBuffer[fSize] = '\0';
	//ファイルを閉じる
	fclose(fp);
	return true;
}

//フォントの読込み
void CSceneTutorial::FontLoad()
{
	//fontの作成
	font.Load(fontAdd, fontName);
	font.Create(38, fontName);
}

//メッセージの更新
void CSceneTutorial::MessageUpdate()
{
	//文字列が終了(改行の次に改行がある)したら、SPACEで次の説明へ
	if(fBuffer[fBufferOffset] == '\n' && fBuffer[fBufferOffset + 1] == '\n')
	{
		messageEndFlg = true;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			if (tutorialStep == TutorialStep::Task_Complete)
			{
				bubbleFade.FadeOut();
				nextSceneTemp = SCENENO_GAME;

				tutorialStep = TutorialStep::Task_End;
				//nextScene = SCENENO_GAME;
				//endFlg = true;
			}
			else if (tutorialStep != pl.GetTaskCompleteStep())
			{
				for (int n = 0; n < MESSAGE_ARRAY_BYTE; n++)
				{
					fLineBuffer[n] = NULL;
				}
				fBufferOffset++; //テキストを分けている改行は表示文字に入れないので、飛ばす
				messageEndFlg = false;
				//チュートリアルの段階を一つ進める 最後のタスクが終わっていたら、タスクを完了状態にする
				if (tutorialStep == TutorialStep::Task_Action)
				{
					tutorialStep = TutorialStep::Task_Complete;
				}
				else
				{
					tutorialStep += 1;
				}
			}
		}
	}
	//文字列の終端まで文字を追加していく
	else if (fBuffer[fBufferOffset] != '\0')
	{
		int nl = strlen(fLineBuffer);
		//改行の場合、表示文字列を改行する
		if (fBuffer[fBufferOffset] == '\n')
		{
			//行間が欲しいので2回改行している
			fLineBuffer[nl++] = '\n';
			fLineBuffer[nl++] = '\n';
			fLineBuffer[nl] = '\0';
			fBufferOffset++;
		}
		else
		{
			//一定時間ごとに一文字ずつfLineBufferにいれていく
			mShowDelay++;
			if (mShowDelay >= MESSAGE_DELAY_FRAME)
			{
				mShowDelay = 0;
				if (IsDBCSLeadByte(fBuffer[fBufferOffset]))			//全角文字判定
				{
					//全角文字の場合２バイト分で一文字になる (文字コードShift_JIS)
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl] = '\0';
				}
				else                                      			//半角の場合
				{
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl] = '\0';
				}
			}
		}
	}
}

//メッセ―ジの描画
void CSceneTutorial::MessageRender()
{
	messageWindowImg.Render(MESSAGE_WINDOW_POS_X, MESSAGE_WINDOW_POS_Y);
	font.RenderString(FIRST_MESSAGE_POS_X, FIRST_MESSAGE_POS_Y, fLineBuffer);
	if (messageEndFlg && tutorialStep == TutorialStep::Task_Complete)
	{
		font.RenderString(1000, 960, "Spaceを押してゲームを開始する");
	}
	else if (messageEndFlg && tutorialStep != pl.GetTaskCompleteStep())
	{
		font.RenderString(1000, 960, "Spaceを押して次へ→");
	}
	else if (messageEndFlg && tutorialStep == pl.GetTaskCompleteStep())
	{
		font.RenderString(1000, 960, "タスクをこなそう！");
	}
}


////////////////////////////
// 制御機構
////////////////////////////

bool CSceneTutorial::Load()
{
	if (!stg.Load())return false;
	if (!ui.Load())return false;
	if (!pl.Load())return false;
	if (!obs.Load())return false;
	if (!messageWindowImg.Load("MessageWindow.png"))return false;
	if (!TextLoad())return false;
	//フォントの読込み
	FontLoad();
	bubbleFade.Load();
	return true;
}

void CSceneTutorial::Initialize()
{
	stg.Initialize();
	pl.Initialize();
	ui.Initialize();
	obs.Initialize();
	fBufferOffset = 0;
	mShowDelay = 0;
	messageEndFlg = false;
	tutorialStep = TutorialStep::Task_Movement;
	pl.SetSoundManager(*cSound);
	bubbleFade.Initialize();
	sceneConfigT.SetSoundManager(*cSound);
	//ポップアップ
	popUpFlg = false;
	poseFlg = false;
	configFlg = false;
}

void CSceneTutorial::Update()
{
	//todo:ポーズ画面表示に変更　現在Enterでメニューに戻る
	//if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	//{
	//	nextScene = SCENENO_GAMEMENU;
	//	endFlg = true;
	//}

	//フェード処理
	bubbleFade.Update();
	bubbleFade.FadeIn();

	//設定表示
	//ゲームに戻るボタンを押した時
	//ゲーム画面に戻ったらconfigFlgをfalse
	if (!sceneConfigT.GetGamePlayFlg())
	{
		configFlg = false;
		bubbleFade.FadeIn();
	}
	else
	{
		bubbleFade.Initialize();
	}
	if (configFlg)
	{
		sceneConfigT.Update();
	}

	//スクロール
	if (!poseFlg)
	{
		stg.Update(pl);
	}

	if (bubbleFade.GetFade())
	{
		return;
	}
	if (bubbleFade.GetFadeOutEnd())
	{
		if (nextSceneTemp == SCENENO_CONFIG)
		{
			configFlg = true;
			sceneConfigT.SetGamePlayFlg();
			sceneConfigT.Load();
			sceneConfigT.Initialize();
		}
		else
		{
			if (nowPopUpTutorial != nullptr)
			{
				nowPopUpTutorial->Release();
			}

			if (nextSceneTemp == SCENENO_GAME)
			{
				//リトライ、もしくはコンティニューボタンが押されたら初期化
				Initialize();
				return;
			}
			else
			{
				endFlg = true;
			}
		}

		//シーンの遷移
		nextScene = nextSceneTemp;
		return;
	}
	//Rでポーズ画面
	if (g_pInput->IsKeyPush(MOFKEY_R) && !popUpFlg)
	{
		nowPopUpTutorial = new CPoseWindow;
		nowPopUpTutorial->SetSoundManager(*cSound);
		nowPopUpTutorial->Initialize();
		popUpFlg = true;
		poseFlg = true;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_R) && popUpFlg&& !configFlg)
	{
		nowPopUpTutorial->Release();
		nowPopUpTutorial = NULL;
		popUpFlg = false;
		poseFlg = false;
	}

	//設定表示
	//ゲーム画面に戻ったらconfigFlgをfalse
	if (!sceneConfigT.GetGamePlayFlg())   //ゲームに戻るボタンを押した時
		configFlg = false;

	if (configFlg)
	{
		sceneConfigT.Update();
	}
	if (popUpFlg && !configFlg)
	{
		PopUpController();
	}
	//ポーズ画面を開いていたら、閉じるまで更新しない
	if (poseFlg)return;

	ui.Update(Event_None);
	for (int i = 0; i < 5; i++)
	{
		pl.Collision(obs, i, true, tutorialStep);
	}
	pl.Update(true, tutorialStep,Event_None);
	obs.Update(pl.GetDistance(), pl.GetPosX(), stg.GetScrollX(), stg.GetScrollY(),tutorialStep, Event_None);
	MessageUpdate();


}

void CSceneTutorial::Render()
{
	stg.Render();
	pl.Render(stg.GetScrollX(), stg.GetScrollY());
	obs.Render(stg.GetScrollX(), stg.GetScrollY());
	
	//最前面の岩背景
	stg.ForeGroundRender();
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetTemperature(), pl.GetDistance(), pl.GetJump(), pl.GetEat(), true, Event_None,pl.GetPosY(), stg.GetScrollY());
	MessageRender();

	//現在のタスク一覧表示
	if (tutorialStep >= TutorialStep::Task_Movement)
	{
		font.RenderString(10, 100, MOF_COLOR_BLACK, "┃\n┃\n┃\n┃\n");

		if (!pl.GetMoveUpTask())
			font.RenderString(40, 100, MOF_COLOR_BLACK, "□ [W]で上に移動");
		else if (pl.GetMoveUpTask())
			font.RenderString(40, 100, MOF_COLOR_BLACK, "■ [W]で上に移動");

		if (!pl.GetMoveDownTask())
			font.RenderString(40, 140, MOF_COLOR_BLACK, "□ [S]で下に移動");
		else if (pl.GetMoveDownTask())
			font.RenderString(40, 140, MOF_COLOR_BLACK, "■ [S]で下に移動");
	}
	if(tutorialStep >= TutorialStep::Task_Action)
	{
		font.RenderString(10, 180, MOF_COLOR_BLACK, "┃\n┃\n┃");

		if (!pl.GetJumpTask())
			font.RenderString(40, 180, MOF_COLOR_BLACK, "□ [ENTER]でジャンプ");
		else if (pl.GetJumpTask())
			font.RenderString(40, 180, MOF_COLOR_BLACK, "■ [ENTER]でジャンプ");

		if (!pl.GetEatTask())
			font.RenderString(40, 220, MOF_COLOR_BLACK, "□ [ENTER]でエサを食べる");
		else if (pl.GetEatTask())
			font.RenderString(40, 220, MOF_COLOR_BLACK, "■ [ENTER]でエサを食べる");
	}

	if (tutorialStep < TutorialStep::Task_Complete)
	{
		font.RenderString(10, 60, MOF_COLOR_BLACK, "□ チュートリアルを完了する");
	}
	else
	{
		font.RenderString(10, 60, MOF_COLOR_BLACK, "■ チュートリアルを完了する");
	}
	
	//ポップアップ描画
	if (popUpFlg)
	{
		nowPopUpTutorial->Render();
	}
	if (configFlg)
	{
		sceneConfigT.Render();
	}

	//todo:デバッグ用 あとで消す（ポーズ画面使えるように変更した後）
	//font.RenderStringScale(800, 50, 2.0f, MOF_COLOR_BLACK, "デバッグ用");
	//font.RenderStringScale(800, 100, 2.0f, MOF_COLOR_BLACK,"Enterでゲームメニューに戻る");

	bubbleFade.Render();

}

void CSceneTutorial::RenderDebug()
{
	pl.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
	obs.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
}

void CSceneTutorial::Release()
{
	stg.Release();
	ui.Release();
	pl.Release();
	obs.Release();
	messageWindowImg.Release();
	free(fBuffer);

	if (nowPopUpTutorial != NULL)
	{
		nowPopUpTutorial->Release();
		if (nowPopUpTutorial)
		{
			delete nowPopUpTutorial;
			nowPopUpTutorial = NULL;
		}
	}
}

void CSceneTutorial::PopUpController()
{
	nowPopUpTutorial->Update();
	if (nowPopUpTutorial->GetButtonResult() == 1)
	{
		//リトライ、もしくはコンティニューボタンが押されたら初期化
		//Initialize();
		nextSceneTemp = SCENENO_TUTORIAL;
		bubbleFade.FadeOut();
	}
	else if (nowPopUpTutorial->GetButtonResult() == 2)
	{
		//メニューボタンが押されたらメニュー画面に遷移
		//nextScene = SCENENO_GAMEMENU;
		//endFlg = true;
		nextSceneTemp = SCENENO_GAMEMENU;
		bubbleFade.FadeOut();
	}
	else if (nowPopUpTutorial->GetButtonResult() == 3)
	{
		//タイトルボタンが押されたらタイトル画面に遷移
		//nextScene = SCENENO_TITLE;
		//endFlg = true;
		nextSceneTemp = SCENENO_TITLE;
		bubbleFade.FadeOut();
	}
	else if (nowPopUpTutorial->GetButtonResult() == 4)
	{
		//設定が押されたら設定画面を表示
		nextScene = SCENENO_CONFIG;
		//nextSceneTemp = SCENENO_CONFIG;
		//bubbleFade.FadeOut();

		configFlg = true;
		sceneConfigT.SetGamePlayFlg();
		sceneConfigT.Load();
		sceneConfigT.Initialize();
		//設定の処理だけポップアップの消去を行わないので、ここでbuttonResultを初期化
		nowPopUpTutorial->SetButtonResult(0);

	}
	else if (nowPopUpTutorial->GetButtonResult() == 5)
	{
		//ゲームに戻るが押されたら
		poseFlg = false;
	}


	//ポップアップの変更
	if (nowPopUpTutorial->IsEnd())
	{
		//次のポップアップの取得
		short nextPopUp = nowPopUpTutorial->GetNextPopUp();
		//古いポップアップの消去
		nowPopUpTutorial->Release();
		delete nowPopUpTutorial;
		//次のポップアップ番号に応じてポップアップを初期化
		switch (nextPopUp)
		{
		case POPUPNO_POSE:
			nowPopUpTutorial = new CPoseWindow;
			nowPopUpTutorial->Initialize();
			nowPopUpTutorial->SetSoundManager(*cSound);
			break;
		case POPUPNO_BACKTOTITLE:
			nowPopUpTutorial = new CBackToTitleWindow;
			nowPopUpTutorial->Initialize();
			nowPopUpTutorial->SetSoundManager(*cSound);
			break;
		case POPUPNO_RETRY:
			nowPopUpTutorial = new CRetryWindow;
			nowPopUpTutorial->Initialize();
			nowPopUpTutorial->SetSoundManager(*cSound);
			break;
		case NULL:
			nowPopUpTutorial = NULL;
			popUpFlg = false;
			break;
		}
	}
}
