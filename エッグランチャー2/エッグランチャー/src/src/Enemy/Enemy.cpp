#include "Enemy.h"
#include "../Sistem/SoundManeger.h"
#include "../player/player.h"
#include <math.h>

//#define DEBUG
extern Player m_pl;
//定義関連

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };
static const float SIN_Y_MAX = 5.0;
static const float SIN_X_MAX = 0.1;

#define MOVESPEED = 1.0f;
#define DEBUG
//-------------------------------

//--------------------
//コンストラクタ
//--------------------
Enemy::Enemy()
{
    //初期化
    m_pos = m_speed = ZERO;
    m_hndl = -1;
    m_isActive = false;//最初は表示しない
}

//---------------------
//デストラクタ
//---------------------
Enemy::~Enemy()
{

    Exit();
}

//---------------------
//初期化
//---------------------
void Enemy::Init()
{
   m_pos = m_speed = ZERO;
    m_radius = 40.0f;
    m_scale = { 5.0f,5.0f,5.0f };
    m_rot = ZERO;
    m_hndl = -1;
    m_isActive = false;//最初は表示しない

}


//---------------------
//データ関連のロード
//---------------------
void Enemy::Load(int orginHndl)
{
    if (m_hndl == -1)
    {
        m_hndl = MV1DuplicateModel(orginHndl);
    }
}

//---------------------
//終了処理
//---------------------
void Enemy::Exit()
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
void Enemy::Step(VECTOR PlayerPos)
{
    //呼び出されていない場合は終了
    if (!m_isActive)return;

    if (m_isActive) {
        VECTOR v1 = { 0.01f,0.01f,0.01f };
        //VECTOR v2 = VSub(m_pos, PlayerPos);
        //VECTOR v3 = VCross(v1, v2);
        //v3 = VNorm(v3);
        //v3 = VScale(v3, 3.0f);
        //m_pos = VAdd(m_pos, v3);

        //上がり下がり移動
      /*  m_rot.y += SIN_X_MAX;
        m_pos.y += sinf(m_rot.y) * SIN_Y_MAX;
        MATRIX mat1, mat2, mat3, mat4;
        mat1 = MGetTranslate(m_pos);
        mat3 = MGetRotY(v1.y);
        mat1 = MMult(mat1, mat3);
        m_pos.x = mat1.m[3][0];
        m_pos.y = mat1.m[3][1];
        m_pos.z = mat1.m[3][2];*/


    }

    /*左に回る
    else if (CheckHitKey(KEY_INPUT_LEFT)) {
        VECTOR v1 = { 0.0f,0.5f,0.0f };
        VECTOR v2 = VSub(m_pos, PlayerPos);
        VECTOR v3 = VCross(v2, v1);
        v3 = VNorm(v3);
        v3 = VScale(v3, 3.0f);
        m_pos = VAdd(m_pos, v3);
    }*/

    //int x =  PlayerPos.x;
    //int z =  PlayerPos.z;
    //m_speed.x = x - m_pos.x;
    //m_speed.y = 0.0f;
    //m_speed.z = z - m_pos.z;
    //m_rot.y = atan2(-m_speed.x, -m_speed.z);
    ////方向ベクトルの長さを計算
    //m_speed.x = -sinf(m_rot.y);
    //m_speed.y = 0.0f;
    //m_speed.z = -cosf(m_rot.y);
    //m_pos = VAdd(m_pos, m_speed);

}

//---------------------
//更新したデータを反映させる
//---------------------
void Enemy::Update()
{
 
    //座標を設定する
    MV1SetPosition(m_hndl, m_pos);
    MV1SetScale(m_hndl, m_scale);
    MV1SetRotationXYZ(m_hndl, m_rot);
   
}

//---------------------
//描画処理
//---------------------
void Enemy::Draw()
{
    if (m_isActive)
    {
        MV1DrawModel(m_hndl);

#ifdef DEBUG
        //当たり判定を目視できる
        DrawSphere3D(GetCenter(), m_radius, 16, GetColor(255, 0, 0),
            GetColor(255, 0, 0), false);
#endif // DEBUG

    }
}

bool Enemy::Request(const VECTOR& pos, const VECTOR& speed)
{
    //すでに発射されている敵は生成失敗
    if (m_isActive)return false;

    //必要な情報を渡していく
    m_isActive = true;
    m_pos = pos;
    m_speed = speed;
    return true;
}

VECTOR Enemy::GetCenter()
{
    //基本は物体の球の判定の位置
    VECTOR res = m_pos;
    //高さだけ足元から玉の半径分上げる
    res.y += m_radius-20.0;

    return res;
}

void Enemy::HitCalc()
{
    SoundManeger::Play(SoundManeger::SE_EXPLOSION);
    //生存フラグを消す
    m_isActive = false;
}