#pragma once
#include "../player/player.h"
#include "../Camera/CameraManeger.h"
#include "../Shot/ShotManeger.h"
#include "../Enemy/EnemyManeger.h"
#include "../Collision/CollisionManeger.h"
#include "../BackGround/BackGround.h"
#include "../../lib/Input/input.h"
#include "../Box/Box.h"
#include <DxLib.h>

//ゲーム本編を管理するクラス
class PlayScene
{
private:
	//ゲーム処理の流れ
	enum tagScene {
		INIT,	//データ初期化
		LOAD,	//データ読み込み
		STARTWAIT,
		MAIN,	//ゲーム本編実行
		ENDWAIT,
		END,	//終了前のデータ破棄
	};
	ShotManeger m_shot;
	Player m_player;			//プレイヤー
	CameraManeger m_camera;		//カメラ
	EnemyManeger m_enemy;		//敵
	tagScene m_state;			//現在の状態遷移
	BackGround m_field;			//背景

public:
	//コンストラクタ
	PlayScene();
	~PlayScene();

	//実行処理
	int Loop();

	//描画処理
	void Draw();

private:

	//初期化
	void Init();

	//データロード
	void Load();
	
	//メイン処理
	void Step();

	//終了前処理
	void Exit();

};
