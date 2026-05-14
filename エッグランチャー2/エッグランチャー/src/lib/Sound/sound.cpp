#include	"sound.h"
#include	<DxLib.h>

//ドー度する予定の音楽パスを管理
static const char* SOUND_PATH[SOUND_NUM] = {
	"Data/sound/title.mp3",				//タイトル画面のBGM
	"Data/sound/bgm00.mp3",				//ゲーム本編のBGM
	"Data/sound/se_explore.mp3",		//爆発効果音
};

//グローバル変数を作成
SOUND_MANAGER g_soundManager;

//----------------------
//サウンドデータの初期化関数
//----------------------
void InitSound()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		g_soundManager.m_hnd[i] = -1;
	}
}

//--------------------------------
//サウンド画像読み込み関数
//--------------------------------
void LoadSound()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		if (g_soundManager.m_hnd[i] == -1)
		{
			//パスは既に定義されているものをループして読み込みする
			g_soundManager.m_hnd[i] = LoadSoundMem(SOUND_PATH[i]);
		}
	}
}

//------------------------------
//終了前に行う必要がある処理関数
//------------------------------
void ExitSound()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		if (g_soundManager.m_hnd[i] != -1)
		{
			DeleteSoundMem(g_soundManager.m_hnd[i]);
			g_soundManager.m_hnd[i] = -1;
		}
	}
}

//------------------------------
//音楽再生
//------------------------------
void RequestSound(int soundID, int type)
{
	PlaySoundMem(g_soundManager.m_hnd[soundID], type);
}

//------------------------------
//音楽停止
//------------------------------
void StopSound(int soundID)
{
	StopSoundMem(g_soundManager.m_hnd[soundID]);
}

//------------------------------
//すべての音楽停止
//------------------------------
void StopAllSound()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		//とりあえずすべてをループして終了する
		StopSound(i);
	}
}