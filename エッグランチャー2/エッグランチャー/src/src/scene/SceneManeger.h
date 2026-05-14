#pragma once
#include "PlayScene.h"

class SceneManeger {
private:
	//ゲーム中に使用する各シーン
	enum tagScene {
		TITLE,		//タイトル画面
		GAME,		//ゲーム本編
		RESULT		//リザルト画面
	};

	//各種シーンの変数を用意
	PlayScene m_play;
	tagScene m_sceneID;		//今のシーンはどれか

	int m_hndl;
	int m_hndl2;


public:
	//コンストラクタ
	SceneManeger();
	~SceneManeger();
	//実行
	int Loop();
	//描画
	void Draw();
};