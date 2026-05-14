#pragma once
#include <DxLib.h>

class Box
{
private:
	
	int m_hndl;
	int m_copyHndl[4];
	VECTOR m_boxPos[4];
	

public:

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

