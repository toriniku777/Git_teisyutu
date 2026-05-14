#pragma once
#include <DxLib.h>

class DebugCamera
{
private:
	VECTOR m_pos;		//カメラの視点
	VECTOR m_rot;		//カメラの回転角度
	

public:
	//コンストラクタ
	DebugCamera();

	//初期化
	void Init();
	
	//カメラの座標計算
	
	void Step();

	//カメラの更新
	void Update();
};

