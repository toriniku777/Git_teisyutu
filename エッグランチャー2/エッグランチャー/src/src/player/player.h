#pragma once
#include <DxLib.h>
#include "../Shot/ShotManeger.h"

class Player
{
private:
	enum ChikinChenge {
		CHIKIN_NORMAL,		// 
		CHIKIN_LEG,		    //
		CHIKIN_KUCHIBASHI,  //
		CHIKIN_ARM,			//

		CHIKIN_NUM			// 状態の総数
	};
	// プレイヤーの状態を表す列挙型
	enum tagPlayerState {
		PLSTATE_NORMAL,		// 待機・移動状態
		PLSTATE_JUMP,		// ジャンプ状態
	

		PLSTATE_NUM			// 状態の総数
	};

	

	// プレイヤーの情報をまとめた構造体
		VECTOR m_pos;			// 座標
		VECTOR m_rot;			// 回転角度
		VECTOR m_speed;			// 移動速度
		VECTOR m_scale;
		tagPlayerState m_state;	// 現在の状態
		float m_radius;			// 物体の半径
		bool m_isActive;		// 生存フラグ
		int m_hndl;				// モデルハンドル
		
		//追加
		VECTOR m_CameraRot;		//カメラの回転率
public:
	//コンストラクタ・デストラクタ
	Player();
	~Player();

	//初期化
	//@vPos:座標
	//@vRot:回転角度
	void Init();
	void Init(VECTOR vPos, VECTOR vRot);

	//データ関連のロード
	void Load();

	//終了処理
	void Exit();

	//毎フレーム呼ぶ処理
	void Step(ShotManeger& shot);

	//カメラの更新
	void Update();

	//描画処理
	void Draw();

	//生存情報取得
	bool isActive() { return m_isActive; }
	void SetAction(bool active) { m_isActive = active; }

	//プレイヤー座標の取得
	VECTOR GetPosition() { return m_pos; }
	float GetRotateY(){ return m_rot.y; }

	void SetPosition(VECTOR pos) { m_pos = pos; }

	//当たり判定の半径サイズを取得
	float GetRadius() { return m_radius; }

	VECTOR GetCenter();

	//ヒット後の処理
	void HitCalc();

	//追加
	//カメラの回転率を設定
	void SetCameraRot(VECTOR _CameraRot) { m_CameraRot = _CameraRot; }
};