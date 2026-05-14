#include "DebugCamera.h"
#include <math.h>

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };

//カメラの回転速度
static const float ROT_SPEED = 0.1f;
//カメラの速さ
static const float MOVE_SPEED = 5.0f;


//--------------------
//コンストラクタ
//--------------------
DebugCamera::DebugCamera()
{
	m_pos = ZERO;
	m_rot = ZERO;
	
}

//--------------------
//初期化
//--------------------
void DebugCamera::Init()
{
	m_pos = ZERO;
	m_rot = ZERO;
}


void DebugCamera::Step()
{
	//カメラの回転処理-------------------
	//上下回転
	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_rot.x -= ROT_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_rot.x += ROT_SPEED;
	}

	//左右回転
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_rot.y += ROT_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_rot.y -= ROT_SPEED;
	}
	//-----------------------------------

	//カメラの移動処理-------------------
	if (CheckHitKey(KEY_INPUT_W))
	{
		//カメラの角度がオール０の時に進む速度
		VECTOR defaultDir = { 0.0f, 0.0f, MOVE_SPEED };
		//上記を行列に変換
		MATRIX dir = MGetTranslate(defaultDir);
		//X軸回転行列
		MATRIX rotX = MGetRotX(m_rot.x);
		//Y軸回転行列
		MATRIX rotY = MGetRotY(m_rot.y);
		//各行列を合成していく
		MATRIX res = MMult(dir, rotX);
		res = MMult(res, rotY);

		//行列から移動情報だけを取り出す
		VECTOR move;
		move.x = res.m[3][0];
		move.y = res.m[3][1];
		move.z = res.m[3][2];
		//計算結果をカメラの現在の座標に足す
		m_pos = VAdd(m_pos, move);
	}
	
	//-----------------------------------
}

//カメラの更新
void DebugCamera::Update()
{
	SetCameraPositionAndAngle(m_pos, m_rot.x, m_rot.y,m_rot.z);
}