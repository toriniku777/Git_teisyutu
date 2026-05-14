#pragma once

enum tagSound {
	BGID_TITLE,			//タイトル画面のBGM
	BGID_GAME,			//ゲーム本編所のBGM
	SEID_EXPLOSION,		//爆発効果音

	SOUND_NUM			//BGM,SEの総数
};

//音楽全体の管理用構造体
typedef struct {
	int m_hnd[SOUND_NUM];		//サウンドハンドル
}SOUND_MANAGER;

//サウンドデータの初期化関数
void InitSound();

//サウンド読み込み関数
void LoadSound();

//終了前に行う必要がある処理関数
void ExitSound();

//音楽再生
//@soundID　　：上記enumのどれかを渡す
void RequestSound(int soundID, int type);

//音楽停止
//@soundID  　：上記enumのどれかを渡す
void StopSound(int soundID);

//すべての音楽停止
void StopAllSound();