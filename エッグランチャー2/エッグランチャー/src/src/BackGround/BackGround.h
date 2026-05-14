#pragma once
#include <DxLib.h>



enum {
	//GROUND,
	SKY,
	SIBAHU1,
	SIBAHU2,
	SIBAHU3,
	SIBAHU4,
	SIBAHU5,
	SIBAHU6,
	SIBAHU7,
	SIBAHU8,
	SIBAHU9,
	SIBAHU10,
	SIBAHU11,
	SIBAHU12,
	ISU1,
	ISU2,
	TUKUE,
	DAIDOKORO,
	IE,

	OBJECT_NUM
};

class BackGround
{
private:
	

	int m_hndl[OBJECT_NUM];				// モデルハンドル
	float m_skyRotY=0;
	float m_Maxtime;
	float m_Timer;
	VECTOR m_rot;

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
