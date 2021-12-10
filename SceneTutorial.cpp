#include "SceneTutorial.h"
CSceneTutorial::CSceneTutorial():
	fBuffer(NULL),
	fBufferOffset(0),
	mShowDelay(0),
	messageEndFlg(false),
	tutorialStep(0)
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
	font.Create(26, fontName);
}

//メッセージの更新
void CSceneTutorial::MessageUpdate()
{
	//文字列が終了(改行の次に改行がある)したら、ENTERで次の説明へ
	if(fBuffer[fBufferOffset] == '\n' && fBuffer[fBufferOffset + 1] == '\n')
	{
		messageEndFlg = true;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			if (tutorialStep == TutorialStep::Task_Complete)
			{
				tutorialStep = TutorialStep::Task_End;
				nextScene = SCENENO_GAME;
				endFlg = true;
			}
			else if (tutorialStep != pl.GetTaskCompleteStep())
			{
				for (int n = 0; n < MESSAGE_ARRAY_BYTE; n++)
				{
					fLineBuffer[n] = NULL;
				}
				fBufferOffset++; //テキストを分けている改行は表示文字に入れないので、飛ばす
				messageEndFlg = false;
				//チュートリアルの段階を一つ進める
				tutorialStep += 1;
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
		CGraphicsUtilities::RenderString(1200, 980, "Spaceを押してゲームを開始する");
	}
	else if (messageEndFlg && tutorialStep != pl.GetTaskCompleteStep())
	{
		CGraphicsUtilities::RenderString(1200, 980, "Spaceを押して次へ→");
	}
	else if (messageEndFlg && tutorialStep == pl.GetTaskCompleteStep())
	{
		CGraphicsUtilities::RenderString(1200, 980, "タスクをこなそう！");
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
	tutorialStep = 0;
}

void CSceneTutorial::Update()
{
	stg.Update(pl);
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
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetTemperature(), pl.GetDistance(), pl.GetJump(), pl.GetEat(), true, Event_None);
	MessageRender();

	//現在のタスク一覧表示
	if (tutorialStep >= TutorialStep::Task_Movement)
	{
		CGraphicsUtilities::RenderString(10, 280, MOF_COLOR_BLACK, "┃\n┃\n┃\n┃\n");

		if (!pl.GetMoveUpTask())
			CGraphicsUtilities::RenderString(40, 280, MOF_COLOR_BLACK, "□ [W]で上に移動");
		else if (pl.GetMoveUpTask())
			CGraphicsUtilities::RenderString(40, 280, MOF_COLOR_BLACK, "■ [W]で上に移動");

		if (!pl.GetMoveDownTask())
			CGraphicsUtilities::RenderString(40, 320, MOF_COLOR_BLACK, "□ [S]で下に移動");
		else if (pl.GetMoveDownTask())
			CGraphicsUtilities::RenderString(40, 320, MOF_COLOR_BLACK, "■ [S]で下に移動");
	}
	if(tutorialStep >= TutorialStep::Task_Action)
	{
		CGraphicsUtilities::RenderString(10, 360, MOF_COLOR_BLACK, "┃\n┃\n┃");

		if (!pl.GetJumpTask())
			CGraphicsUtilities::RenderString(40, 360, MOF_COLOR_BLACK, "□ [A]でジャンプ");
		else if (pl.GetJumpTask())
			CGraphicsUtilities::RenderString(40, 360, MOF_COLOR_BLACK, "■ [A]でジャンプ");

		if (!pl.GetEatTask())
			CGraphicsUtilities::RenderString(40, 400, MOF_COLOR_BLACK, "□ [A]でエサを食べる");
		else if (pl.GetEatTask())
			CGraphicsUtilities::RenderString(40, 400, MOF_COLOR_BLACK, "■ [A]でエサを食べる");
	}

	if (tutorialStep != TutorialStep::Task_Complete)
	{
		CGraphicsUtilities::RenderString(10, 240, MOF_COLOR_BLACK, "□ チュートリアルを完了する");
	}
	else
	{
		CGraphicsUtilities::RenderString(10, 240, MOF_COLOR_BLACK, "■ チュートリアルを完了する");
	}
	

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
}
