#pragma once
#include <DxLib.h>

class Enemy
{
private:

	// 敵の情報をまとめた構造体
	VECTOR m_pos;			// 座標
	VECTOR m_speed;			// 移動速度
	VECTOR m_rot;
	VECTOR m_scale;
	float m_radius;			// 物体の半径
	int m_hndl;				// モデルハンドル
	bool m_isActive;		// 生存フラグ

public:
	//コンストラクタ・デストラクタ
	Enemy();
	~Enemy();

	//初期化
	void Init();

	//データ関連のロード
	void Load(int orginHndl);

	//終了処理
	void Exit();

	//毎フレーム呼ぶ処理
	void Step(VECTOR PlayerPos);

	//データの更新
	void Update();

	//描画処理
	void Draw();

	//弾をリクエスト
	//@pos:どこから発射するか
	//@speed:どの方向に飛んでくか
	//@return:生成成功か失敗か
	bool Request(const VECTOR& pos, const VECTOR& speed);

	//生存情報取得
	bool isActive() { return m_isActive; }
	void SetAction(bool active) { m_isActive = active; }

	//座標取得
	VECTOR GetPosition() { return m_pos; }

	//当たり判定の半径サイズを取得
	float GetRadius() { return m_radius; }

	VECTOR GetCenter();

	//ヒット後の処理
	void HitCalc();
};
