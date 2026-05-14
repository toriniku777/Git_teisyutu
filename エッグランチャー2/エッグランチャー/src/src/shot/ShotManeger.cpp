#include "ShotManeger.h"
#include "../Sistem/SoundManeger.h"
#include <math.h>

//定義関連
static const char PLSHOT_MODEL_PATH[] = { "Data/Model/Shot/卵.x" };
//-------------------------------

//--------------------
//コンストラクタ
//--------------------
ShotManeger::ShotManeger()
{

}


//---------------------
//初期化
//---------------------
void ShotManeger::Init()
{
    for (int i = 0; i < PL_SHOT_NUM; i++)
    {
        m_playerShot[i].Init();
    }
}


//---------------------
//データ関連のロード
//---------------------
void ShotManeger::Load()
{
    int hndl = MV1LoadModel(PLSHOT_MODEL_PATH);
    for (int i = 0; i < PL_SHOT_NUM; i++)
    {
        m_playerShot[i].Load(hndl);
    }
    MV1DeleteModel(hndl);
}

//---------------------
//終了処理
//---------------------
void ShotManeger::Exit()
{
    for (int i = 0; i < PL_SHOT_NUM; i++)
    {
        m_playerShot[i].Exit();
    }

}

//---------------------
//毎フレーム呼ぶ処理
//---------------------
void ShotManeger::Step()
{
    for (int i = 0; i < PL_SHOT_NUM; i++)
    {
        m_playerShot[i].Step();
    }

}

//---------------------
//更新したデータを反映させる
//---------------------
void ShotManeger::Update()
{
    for (int i = 0; i < PL_SHOT_NUM; i++)
    {
        m_playerShot[i].Update();
    }
}

//---------------------
//描画処理
//---------------------
void ShotManeger::Draw()
{
    for (int i = 0; i < PL_SHOT_NUM; i++)
    {
        m_playerShot[i].Draw();
    }
}

void ShotManeger::RequestPlayerShot(const VECTOR& pos, const VECTOR& speed)
{
    for (int i = 0; i < PL_SHOT_NUM; i++)
    {
        
        if (m_playerShot[i].Request(pos, speed))
        {
            SoundManeger::Play(SoundManeger::SE_PLSHOT);
            break;
        }
    }
}