#pragma once
#include "Shot.h"

//プレイヤーの弾の最大数
static const int PL_SHOT_NUM = 1000;

//弾全体を管理するクラス
class ShotManeger
{
private:

	Shot m_playerShot[PL_SHOT_NUM];


public:
	//コンストラクタ・デストラクタ
	ShotManeger();
	

	//初期化
	void Init();

	//データ関連のロード
	void Load();

	//終了処理
	void Exit();

	//毎フレーム呼ぶ処理
	void Step();

	//カメラの更新
	void Update();

	//描画処理
	void Draw();

	//弾をリクエスト
	//@pos:どこから発射するか
	//@speed:どの方向に飛んでくか
	//@return:生成成功か失敗か
	void RequestPlayerShot(const VECTOR& pos, const VECTOR& speed);

	//弾1発分の情報取得
	//@id:配列番号
	Shot& GetShot(int id) { return m_playerShot[id]; }
};
