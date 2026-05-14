#include "Shot.h"
#include <math.h>

//#define DEBUG
//定義関連
static const float SHOT_SPEED = 1.0f;
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };
//-------------------------------

//--------------------
//コンストラクタ
//--------------------
Shot::Shot()
{
    //初期化
    m_pos = m_speed = ZERO;
    m_hndl = -1;
    m_isActive = false;//最初は表示しない
}

//---------------------
//デストラクタ
//---------------------
Shot::~Shot()
{

    Exit();
}

//---------------------
//初期化
//---------------------
void Shot::Init()
{
    m_pos = m_speed = ZERO;
    m_radius = 5.0f;
    m_hndl = -1;
    m_isActive = false;//最初は表示しない
}


//---------------------
//データ関連のロード
//---------------------
void Shot::Load(int orginHndl)
{
    if (m_hndl == -1)
    {
        m_hndl = MV1DuplicateModel(orginHndl);
    }
}

//---------------------
//終了処理
//---------------------
void Shot::Exit()
{
    if (m_hndl != -1)
    {
        MV1DeleteModel(m_hndl);
        m_hndl = -1;
    }

}

//---------------------
//毎フレーム呼ぶ処理
//---------------------
void Shot::Step()
{
    //呼び出されていない場合は終了
    if (!m_isActive)return;

    //現在の座標に速度を加算する
    m_speed.y += -0.05f;
    m_pos = VAdd(m_pos, m_speed);

    m_activeTime += 0.1;

    if (m_activeTime >= 15.0)
    {
        m_isActive = false;
        m_activeTime = 0.0;
    }
    ////範囲外に出たら弾を削除
    //float length = 300.0f;
    //if (m_pos.x< -length || m_pos.x>length
    //    || m_pos.z< -length || m_pos.z>length)
    //{
    //    m_isActive = false;
    //}
   
    //卵回転用
    m_eggRotX += 0.1;
}

//---------------------
//更新したデータを反映させる
//---------------------
void Shot::Update()
{
    //座標を設定する
    MV1SetPosition(m_hndl, m_pos);
    VECTOR rot = { m_eggRotX ,0.0f ,0.0f };
    MV1SetRotationXYZ(m_hndl, rot);
}

//---------------------
//描画処理
//---------------------
void Shot::Draw()
{
    if (m_isActive)
    {
        MV1DrawModel(m_hndl);

#ifdef DEBUG
        //当たり判定を目視できる
        DrawSphere3D(GetCenter(), m_radius, 16, GetColor(255, 0, 0),
            GetColor(255, 0, 0), FALSE);
#endif // DEBUG

    }
}

bool Shot::Request(const VECTOR& pos, const VECTOR& speed)
{
    //すでに発射されている弾は生成失敗
    if (m_isActive)return false;

    //必要な情報を渡していく
    m_isActive = true;
    m_pos = pos;
    m_speed = speed;
    return true;
}

VECTOR Shot::GetCenter()
{
    //基本は物体の球の判定の位置
    VECTOR res = m_pos;
   

    return res;
}

void Shot::HitCalc()
{
    //生存フラグを消す
    m_isActive = false;
}