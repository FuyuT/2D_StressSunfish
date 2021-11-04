#include "SceneTutorial.h"
CFont FontPopRumCute;
CFont f1;
CSceneTutorial::CSceneTutorial()
{
}

CSceneTutorial::~CSceneTutorial()
{
}

bool CSceneTutorial::Load()
{
	if (!stg.Load())return false;
	if (!ui.Load())return false;
	if (!pl.Load())return false;
	if (!obs.Load())return false;
	if (!messageWindowImg.Load("MessageWindow.png"))return false;
	if (!TextLoad())return false;
	//fontの作成
	FontPopRumCute.Create(64, "MS　ゴシック");
	f1.Create(64, "MS　明朝");
	//FontPopRumCute.Create(64, "	ポプらむ☆キュート");
	
	return true;
}

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

void CSceneTutorial::Initialize()
{
	stg.Initialize();
	pl.Initialize();
	ui.Initialize();
	fBufferOffset = 0;
	mShowDelay = 0;
	messegeEndFlg = false;
	
}

void CSceneTutorial::Update()
{
	stg.Update(pl);
	pl.Update();
	ui.Update();
	MessageUpdate();
}

void CSceneTutorial::MessageUpdate()
{
	//文字列が終了(改行の次に改行がある)したら、ENTERで次の説明へ
	if(fBuffer[fBufferOffset] == '\n' && fBuffer[fBufferOffset + 1] == '\n')
	{
		messegeEndFlg = true;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			for (int n = 0; n < MESSAGE_ARRAY_BYTE; n++)
			{
				fLineBuffer[n]= NULL;
			}
			fBufferOffset++; //テキストを分けている改行は表示文字に入れないので、飛ばす
			messegeEndFlg = false;
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

void CSceneTutorial::Render()
{
	stg.Render();
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetBodyTemp(), pl.GetTemperature());
	pl.Render(stg.GetScrollX(), stg.GetScrollY());
	messageWindowImg.Render(MESSAGE_WINDOW_POS_X, MESSAGE_WINDOW_POS_Y);
	CGraphicsUtilities::RenderString(FIRST_MESSAGE_POS_X, FIRST_MESSAGE_POS_Y, fLineBuffer);
	if (messegeEndFlg)
	{
		CGraphicsUtilities::RenderString(1200, 980, "Spaceを押して次へ→");
	}
}

void CSceneTutorial::RenderDebug()
{
	pl.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
}

void CSceneTutorial::Release()
{
	stg.Release();
	ui.Release();
	pl.Release();
	messageWindowImg.Release();
	free(fBuffer);
}
