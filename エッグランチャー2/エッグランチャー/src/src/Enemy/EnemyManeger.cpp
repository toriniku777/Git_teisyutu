#include "EnemyManeger.h"
#include <math.h>

//定義関連
static const char ENEMY_MODEL_PATH[] = { "Data/Model/mato/フライパン.x" };
static const int WAIT_TIME = 100;
//-------------------------------

//--------------------
//コンストラクタ
//--------------------
EnemyManeger::EnemyManeger()
{

}


//---------------------
//初期化
//---------------------
void EnemyManeger::Init()
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        m_enemy[i].Init();
    }
}


//---------------------
//データ関連のロード
//---------------------
void EnemyManeger::Load()
{
    int hndl = MV1LoadModel(ENEMY_MODEL_PATH);
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        m_enemy[i].Load(hndl);
    }
    MV1DeleteModel(hndl);
}

//---------------------
//終了処理
//---------------------
void EnemyManeger::Exit()
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        m_enemy[i].Exit();
    }

}

//---------------------
//毎フレーム呼ぶ処理
//---------------------
void EnemyManeger::Step(VECTOR PlayerPos)
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        m_enemy[i].Step(PlayerPos);
        
    }
    m_waitCount--;
        if (m_waitCount <= 0)
        {
            Request();
            m_waitCount = WAIT_TIME;
        }

}

//---------------------
//更新したデータを反映させる
//---------------------
void EnemyManeger::Update()
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        m_enemy[i].Update();
    }
}

//---------------------
//描画処理
//---------------------
void EnemyManeger::Draw()
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        m_enemy[i].Draw();
    }
}

void EnemyManeger::Request()
{

    VECTOR pos = { 0.0,0.0,200.0 };//{ (float)GetRand(600) - 300.0f,20.0f,200.0f };
    //VECTOR pos2 = { (float)GetRand(600) - 300.0f,20.0f,-200.0f };
    VECTOR speed = { 0,-1.0,1.0 };

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (m_enemy[i].Request(pos, speed)) break;

    }

    /*for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (m_enemy[i].Request(pos2, speed)) break;

    }*/
}