#include "Camera.h"
#include <math.h>

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };

//--------------------
//コンストラクタ
//--------------------
PlayCamera::PlayCamera()
{
	m_camPos = ZERO;
	m_targetPos = ZERO;
	m_upVec = ZERO;
}

//--------------------
//初期化
//--------------------
void PlayCamera::Init()
{
	m_camPos = ZERO;
	m_targetPos = ZERO;
	m_upVec = { 0.0f,1.0f,0.0f };
	m_CamaraRot = { 0.0f,0.0f,0.0f };
}


void PlayCamera::Step(VECTOR forcus, float rotY)
{
	

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_CamaraRot.y += 0.05;
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_CamaraRot.y -= 0.05;
	}

	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_CamaraRot.x += 0.05;
	}

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_CamaraRot.x -= 0.05;
	}

	//現在のカメラの位置からキャラクターの位置までの方向ベクトルを取得
	VECTOR Dir = VSub(m_camPos, forcus);
	Dir.y = 0.0f;

	//今回は長さが重要なので、先ほど計算したベクトルから長さを計算
	float Len = VSize(Dir);

	//長さを求めたので、方向ベクトルは正規化してしまう
	Dir = VNorm(Dir);

	

	// 行列計算でカメラ位置を求める-----------------------------
	VECTOR ChikinPos = forcus;
	VECTOR matDefault = { 0.0f, 50.0f, -500.0f };

	MATRIX matResult;
	MATRIX matDefPos = MGetTranslate(matDefault);
	MATRIX matRotX = MGetRotX(m_CamaraRot.x);
	MATRIX matRotY = MGetRotY(m_CamaraRot.y);
	MATRIX matChikinPos = MGetTranslate(ChikinPos);


	matResult = MMult(matDefPos, matRotX);
	matResult = MMult(matResult, matRotY);
	matResult = MMult(matResult, matChikinPos);
	m_camPos = VGet(matResult.m[3][0], matResult.m[3][1], matResult.m[3][2]);
	

	SetCameraPositionAndTarget_UpVecY(m_camPos, ChikinPos);

	//最後の共通部分の処理
	//注視点はプレイヤーの上半身辺り
	m_targetPos = forcus;
	m_targetPos.y += 20.0f;

}

void PlayCamera::Update()
{
	SetCameraPositionAndTargetAndUpVec(m_camPos, m_targetPos, m_upVec);
}







//static const VECTOR ZERO = { 0.0f,0.0f,0.0f };
//
////--------------------
////コンストラクタ
////--------------------
//PlayCamera::PlayCamera()
//{
//	m_camPos = ZERO;
//	m_targetPos = ZERO;
//	m_upVec = ZERO;
//}
//
////--------------------
////初期化
////--------------------
//void PlayCamera::Init()
//{
//	m_camPos = ZERO;
//	m_targetPos = ZERO;
//	m_upVec = { 0.0f,1.0f,0.0f };
//	m_CamaraRot = { 0.0f,0.0f,0.0f };
//}
//
//
//void PlayCamera::Step(VECTOR forcus, float rotY)
//{
//
//
//	if (CheckHitKey(KEY_INPUT_RIGHT))
//	{
//		m_CamaraRot.y += 0.05;
//	}
//
//	if (CheckHitKey(KEY_INPUT_LEFT))
//	{
//		m_CamaraRot.y -= 0.05;
//	}
//
//	if (CheckHitKey(KEY_INPUT_UP))
//	{
//		m_CamaraRot.x += 0.05;
//	}
//
//	if (CheckHitKey(KEY_INPUT_DOWN))
//	{
//		m_CamaraRot.x -= 0.05;
//	}
//
//	//現在のカメラの位置からキャラクターの位置までの方向ベクトルを取得
//	VECTOR Dir = VSub(m_camPos, forcus);
//	Dir.y = 0.0f;
//
//	//今回は長さが重要なので、先ほど計算したベクトルから長さを計算
//	float Len = VSize(Dir);
//
//	//長さを求めたので、方向ベクトルは正規化してしまう
//	Dir = VNorm(Dir);
//
//
//
//	// 行列計算でカメラ位置を求める-----------------------------
//	VECTOR ChikinPos = forcus;
//	VECTOR matDefault = { 0.0f, 60.0f, -200.0f };
//
//	MATRIX matResult;
//	MATRIX matDefPos = MGetTranslate(matDefault);
//	MATRIX matRotX = MGetRotX(m_CamaraRot.x);
//	MATRIX matRotY = MGetRotY(m_CamaraRot.y);
//	MATRIX matChikinPos = MGetTranslate(ChikinPos);
//
//
//	matResult = MMult(matDefPos, matRotX);
//	matResult = MMult(matResult, matRotY);
//	matResult = MMult(matResult, matChikinPos);
//	m_camPos = VGet(matResult.m[3][0], matResult.m[3][1], matResult.m[3][2]);
//
//
//	SetCameraPositionAndTarget_UpVecY(m_camPos, ChikinPos);
//
//	//最後の共通部分の処理
//	//注視点はプレイヤーの上半身辺り
//	m_targetPos = forcus;
//	m_targetPos.y += 20.0f;
//
//}
//
//void PlayCamera::Update()
//{
//	SetCameraPositionAndTargetAndUpVec(m_camPos, m_targetPos, m_upVec);
//}