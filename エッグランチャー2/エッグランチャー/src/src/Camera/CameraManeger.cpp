#include "CameraManeger.h"
#include <DxLib.h>



//--------------------
//コンストラクタ
//--------------------
CameraManeger::CameraManeger()
{
	m_ID = ID_PLAY;
}

//--------------------
//初期化
//--------------------
void CameraManeger::Init()
{
	//それぞれのカメラの初期化
	m_play.Init();
	m_debug.Init();
	SetCameraNearFar(1.0f, 5000.0f);
}

void CameraManeger::Step(VECTOR forcus, float rotY)
{
	
	switch (m_ID)
	{
		//ゲームのメインカメラ
	case ID_PLAY:
		m_play.Step(forcus, rotY);
		break;
		//デバック用のカメラ
	case ID_DEBUG:
		m_debug.Step();
		break;
	}
}

void CameraManeger::Update()
{
	switch (m_ID)
	{
		//ゲームのメインカメラ
	case ID_PLAY:
		m_play.Update();
		break;
		//デバック用のカメラ
	case ID_DEBUG:
		m_debug.Update();
		break;
	}
}