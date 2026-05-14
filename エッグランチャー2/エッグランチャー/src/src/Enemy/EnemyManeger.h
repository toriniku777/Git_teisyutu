#pragma once
#include "Enemy.h"

//敵の最大数
static const int ENEMY_NUM = 1;

//敵全体を管理するクラス
class EnemyManeger
{
private:
	int m_waitCount;//敵が出るまでの時間
	Enemy m_enemy[ENEMY_NUM];

public:
	//コンストラクタ・デストラクタ
	EnemyManeger();


	//初期化
	void Init();

	//データ関連のロード
	void Load();

	//終了処理
	void Exit();

	//毎フレーム呼ぶ処理
	void Step(VECTOR PlayerPos);

	//カメラの更新
	void Update();

	//描画処理
	void Draw();

	//敵をリクエスト
	void Request();

	//弾1発分の情報取得
		//@id:配列番号
	Enemy& GetEnemy(int id) { return m_enemy[id]; }
};