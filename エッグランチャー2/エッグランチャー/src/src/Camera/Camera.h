#pragma once
#include <DxLib.h>

class PlayCamera
{
private:
	VECTOR m_camPos;		//カメラの視点
	VECTOR m_targetPos;	//カメラの注視点
	VECTOR m_upVec;		//カメラの上方向

	//追加
	VECTOR m_CamaraRot;	//カメラの回転率


public:
	//コンストラクタ
	PlayCamera();

	//初期化
	void Init();
	
	//カメラの座標計算
	//@foucus:プレイヤーの座標
	//@rotY:プレイヤーの角度
	void Step(VECTOR forcus, float rotY);

	//カメラの更新
	void Update();

	//追加
	//カメラの回転率を渡す
	VECTOR GetCameraRot() { return m_CamaraRot; }
};
