#pragma once
#include "Camera.h"
#include "DebugCamera.h"

class CameraManeger
{
public:
	//カメラのタイプ
	enum tagCAMERA_ID
	{
		ID_PLAY,
		ID_DEBUG,

		ID_NUM
	};

private:
	PlayCamera m_play;
	DebugCamera m_debug;
	tagCAMERA_ID m_ID;

public:
	//コンストラクタ
	CameraManeger();

	//初期化
	void Init();

	//@foucus:プレイヤーの座標
	//@rotY:プレイヤーの角度
	void Step(VECTOR forcus, float rotY);

	//カメラの更新
	void Update();

	//カメラのタイプ切り替え
	void ChangeCamera(tagCAMERA_ID id) { m_ID = id; }

	//カメラのタイプ取得
	tagCAMERA_ID GetID() { return m_ID; }

	//追加
	//カメラの回転率
	VECTOR GetCameraRot() { return m_play.GetCameraRot(); }
};