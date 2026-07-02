#pragma once
#include <DxLib.h>



enum {
	SKY,
	SIBAHU,
	SAKU1,
	SAKU2,
	SAKUSUKE1,
	

	OBJECT_NUM
};

class BackGround
{
private:
	

	int m_hndl[OBJECT_NUM];				// モデルハンドル
	float m_skyRotY=0;
	float m_Maxtime;
	float m_Timer;

public:

	
	int GetHndl(int i) { return m_hndl[i]; }

	void Init();

	//データ関連のロード
	void Load();

	//終了処理
	void Exit();

	//毎フレーム呼ぶ処理
	void Step();

	//カメラの更新
	void Update();

	//描画処理
	void Draw();

	
};
