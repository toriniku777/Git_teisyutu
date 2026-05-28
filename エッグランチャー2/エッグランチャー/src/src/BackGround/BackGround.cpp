#include "BackGround.h"

//定義関連
static const char* BackGround_MODEL_PATH[] =
{ 
"Data/Model/sky/sky.mv1",
"Data/Model/field/sibahuu.x",
"Data/Model/field/saku.x"
};
//-------------------------------



//---------------------
//初期化
//---------------------
void BackGround::Init()
{
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        m_hndl[i] = -1;
    }

   
}

//---------------------
//データ関連のロード
//---------------------
void BackGround::Load()
{
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        if (m_hndl[i] = -1)
        {
            m_hndl[i] = MV1LoadModel(BackGround_MODEL_PATH[i]);
        }
    }
    VECTOR scale[OBJECT_NUM] =
    {
        //天球、芝生、柵
       {100.0f,100.0f,100.0f},{1500 ,1.0f,1500.0f },{1.0f,1.0f,1.0f }
    };

    VECTOR posision[OBJECT_NUM] =
    {
        //天球、芝生、柵
       {0.0f,0.0f,0.0f},{0.0f,-2.0f,0.0f },{0.0f,0.0f,2000.0f }

    };

    VECTOR rotate[OBJECT_NUM] =
    {
        //天球、芝生、柵  
       {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,1.57f,0.0f }

    };

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        //MV1SetupCollInfo(m_hndl[i]);
        MV1SetScale(m_hndl[i],scale[i]);
        MV1SetPosition(m_hndl[i], posision[i]);
        MV1SetRotationXYZ(m_hndl[i], rotate[i]);
    }
}

//---------------------
//終了処理
//---------------------
void BackGround::Exit()
{
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        if (m_hndl[i] = -1)
        {
            MV1DeleteModel(m_hndl[i]);
            m_hndl[i] = -1;
        }
      
    }

}

//---------------------
//毎フレーム呼ぶ処理
//---------------------
void BackGround::Step()
{
    //天球回転用
    m_skyRotY += 0.0001;
}

//---------------------
//更新したデータを反映させる
//---------------------
void BackGround::Update()
{
    VECTOR skyrot = { 0.0f,m_skyRotY ,0.0f};
    MV1SetRotationXYZ(m_hndl[SKY], skyrot);
   
}

//---------------------
//描画処理
//---------------------
void BackGround::Draw()
{
    for (int i = 0; i < OBJECT_NUM; i++)
    {
        MV1DrawModel(m_hndl[i]);
    }
}




