#include "Box.h"

#define OBJECT_NUM (4)
//定義関連
//-------------------------------



//---------------------
//初期化
//---------------------
void Box::Init()
{
        m_hndl = -1;
}

//---------------------
//データ関連のロード
//---------------------
void Box::Load()
{
    if (m_hndl = -1)
    {
        m_hndl = MV1LoadModel("Data/Model/Box/Box.x");
    }
    m_boxPos[0] = VGet(-100.0f, 1.0f, 100.0f);
    m_boxPos[1] = VGet(100.0f, 1.0f, 100.0f);
    m_boxPos[2] = VGet(-100.0f, 1.0f, -100.0f);
    m_boxPos[3] = VGet(100.0f, 1.0f, -100.0f);
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        m_copyHndl[i] = MV1DuplicateModel(m_hndl);
        MV1SetPosition(m_copyHndl[i], m_boxPos[i]);	//3Dモデルの位置を設定
    }

    VECTOR scale = { 1.0f,1.0f,1.0f };
    MV1SetScale(m_hndl, scale);
}

//---------------------
//終了処理
//---------------------
void Box::Exit()
{
   
        if (m_hndl = -1)
        {
            MV1DeleteModel(m_hndl);
            m_hndl = -1;
        }
}

//---------------------
//毎フレーム呼ぶ処理
//---------------------
void Box::Step()
{
   
    //天球回転用
    //m_skyRotY += 0.0001;
}

//---------------------
//更新したデータを反映させる
//---------------------
void Box::Update()
{
    //VECTOR rot = { 0.0f,m_skyRotY ,0.0f };
    //MV1SetRotationXYZ(m_hndl[SKY], rot);

}

//---------------------
//描画処理
//---------------------
void Box::Draw()
{
   
        MV1DrawModel(m_hndl);
   
}
