#include "Enemy.h"
#include "../Sistem/SoundManeger.h"
#include "../player/player.h"
#include "../shot/Shot.h"
#include <math.h>

#define GRAVITY (0.5f)
#define	JUMP_POWER	( 8.0f )

//#define DEBUG
extern Player m_pl;
//定義関連

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };//モデル角度
static const float SIN_Y_MAX = 5.0;
static const float SIN_X_MAX = 0.1;


#define DEBUG
//-------------------------------

//--------------------
//コンストラクタ
//--------------------
Enemy::Enemy()
{
    ////初期化
    //m_pos = m_speed = ZERO;
    //m_hndl = -1;
    //m_isActive = false;//最初は表示しない

    Init();
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
    m_jump = 0.0f;
    m_groundtouch = false;
    m_state = CKNSTATE_NORMAL;
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

    m_pos.y += m_jump;
    

    switch (m_state)
    {
    case Enemy::CKNSTATE_NORMAL:

        break;

    case Enemy::CKNSTATE_HIT:
        m_jump = JUMP_POWER;
        m_groundtouch = false;
        m_state = CKNSTATE_FLAY;
        m_gravity = GRAVITY;
        m_pos.y += 3.0f;

        printfDx("x:%f\n",m_speed.x);
        printfDx("y:%f\n", m_speed.y);
        printfDx("z:%f\n", m_speed.z);



    case Enemy::CKNSTATE_FLAY:

        m_speed = { m_speed.x / 50.0f,m_speed.y ,m_speed.z / 50.0f };
        m_speed = { m_speed.x * 43.0f,m_speed.y ,m_speed.z * 43.0f };

        m_pos = VAdd(m_pos, m_speed);

        if (m_pos.y > 1.0f) {
            m_jump -= m_gravity;
        }
        else {
            m_pos.y = 0.0f;
            m_jump = 0.0f;
            m_groundtouch = true;
        }

        if (m_groundtouch == true)
        {
            m_state = CKNSTATE_NORMAL;
        }
        

        break;

    case Enemy::PLSTATE_NUM:

        break;
   
        break;
    }
    //if (m_isActive) 
    //{
    //    VECTOR v1 = { 0.01f,10.01f,0.01f };//回転速度

    //    //上がり下がり移動
    //    m_rot.y += SIN_X_MAX;
    //    m_pos.y += sinf(m_rot.y) * SIN_Y_MAX;
    //    MATRIX mat1, mat2, mat3, mat4;
    //    mat1 = MGetTranslate(m_pos);
    //    mat3 = MGetRotY(v1.y);
    //    mat1 = MMult(mat1, mat3);
    //    m_pos.x = mat1.m[3][0];
    //    m_pos.y = mat1.m[3][1];
    //    m_pos.z = mat1.m[3][2];
    //}

   

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

        DrawFormatString(20, 80, GetColor(255, 255, 0), "P_pos.x:%.2f", m_pos.x);
        DrawFormatString(20, 100, GetColor(255, 255, 0), "P_pos.y:%.2f", m_pos.y);
        DrawFormatString(20, 120, GetColor(255, 255, 0), "P_pos.z:%.2f", m_pos.z);
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

void Enemy::HitCalc(VECTOR shotspeed)
{
    SoundManeger::Play(SoundManeger::SE_EXPLOSION);
    ////生存フラグを消す
    //m_isActive = false;
    m_speed = shotspeed;
    m_state = CKNSTATE_HIT;
}