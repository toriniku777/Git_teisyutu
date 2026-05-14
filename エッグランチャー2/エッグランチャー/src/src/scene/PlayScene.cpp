#include "PlayScene.h"
#include "../Sistem/SoundManeger.h"
#include "../../lib/Fade/fade.h"
#include <DxLib.h>



//--------------------
//コンストラクタ
//--------------------
PlayScene::PlayScene()
{
	//最初はデータ初期化
	m_state = INIT();
}
//--------------------
//デストラクタ
//--------------------
PlayScene::~PlayScene()
{
	//安全のためにデータ破棄処理呼び出し
	Exit();
}

//--------------------
//初期化
//--------------------
int PlayScene::Loop()
{
	//ゲームが終了したかを外部に伝えるため
	int result = -1;


	switch (m_state)
	{
	case PlayScene::INIT:
		Init();
		
		m_state = PlayScene::LOAD;//次へ進む
		break;

	case PlayScene::LOAD:
		Load();
		Fade::RequestFadeIn();
		//ゲーム本編のBGMを鳴らす
		SoundManeger::Play(SoundManeger::BGM_GAME,DX_PLAYTYPE_LOOP);
		m_state = PlayScene::STARTWAIT;//次へ進む
		break;

	case PlayScene::STARTWAIT:
		Fade::RequestFadeIn();
		if (Fade::IsEndFadeOut())
		{
			m_state = PlayScene::MAIN;
		}
		break;

	case PlayScene::MAIN:
		
		Step();
		break;

	case PlayScene::ENDWAIT:
		Fade::RequestFadeOut();
		if (Fade::IsEndFadeOut())
		{
			m_state = PlayScene::END;
		}
		break;

	case PlayScene::END:
		Exit();
		//すべての音楽を止めて次へ
		SoundManeger::AllStop();
		Fade::RequestFadeIn();
		m_state = PlayScene::INIT;//次へ進む
		result = 0;
		break;
	
	}
	//本編が終了したかを外部に伝えるため
	return result;
}

void PlayScene::Draw()
{
	m_field.Draw();

	m_player.Draw();
	m_shot.Draw();
	m_enemy.Draw();
}

void PlayScene::Init()
{

	m_player.Init();
	m_shot.Init();
	m_camera.Init();
	m_enemy.Init();
	m_field.Init();
}

void PlayScene::Load()
{
	m_player.Load();
	m_shot.Load();
	m_enemy.Load();
	m_field.Load();
}

void PlayScene::Step()
{
	//各種計算処理を実行
	m_player.SetCameraRot(m_camera.GetCameraRot());
	m_player.Step(m_shot);

	m_shot.Step();
	m_enemy.Step(m_player.GetPosition());
	m_field.Step();
	m_camera.Step(m_player.GetPosition(), m_player.GetRotateY());

	if (CheckHitKey(KEY_INPUT_C))
	{
		m_camera.ChangeCamera(CameraManeger::ID_DEBUG);
	}
	if (CheckHitKey(KEY_INPUT_V))
	{
		m_camera.ChangeCamera(CameraManeger::ID_PLAY);
	}

	//当たり判定処理
	CollisionManeger::CheckHitShotToEnemy(m_shot, m_enemy);
	CollisionManeger::CheckHitPlayerToEnemy(m_player, m_enemy);
	CollisionManeger::CheckHitPlayerToField(m_player, m_field);
	//プレイヤーの生存フラグが消えたらゲーム終了へ
	if (m_player.isActive() == false)
	{
		m_state = ENDWAIT;
	}

	//すべての結果を反映させる
	m_player.Update();
	m_shot.Update();
	m_enemy.Update();
	m_field.Update();
	m_camera.Update();
}


void PlayScene::Exit()
{
	m_player.Exit();
	m_shot.Exit();
	m_enemy.Exit();
	m_field.Exit();
}