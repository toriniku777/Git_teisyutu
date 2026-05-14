#include "BackGround.h"

//定義関連
static const char* BackGround_MODEL_PATH[] =
{ 
"Data/Model/sky/sky.mv1",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/sibahuu.x",
"Data/Model/field/椅子.x",
"Data/Model/field/椅子.x",
"Data/Model/field/机.x",
"Data/Model/field/台所.x",
"Data/Model/field/いえ.x"
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
        //天球、芝生、芝生、芝生、芝生
       {20.0f,20.0f,20.0f},{10.0f,1.0f,10.0f },{10.0f,1.0f,10.0f },{ 10.0f,1.0f,10.0f },{ 10.0f,1.0f,10.0f },
         //芝生、芝生、芝生、芝生、芝生
        { 10.0f,1.0f,10.0f },{ 10.0f,1.0f,10.0f },{ 10.0f,1.0f,10.0f },{ 10.0f,1.0f,10.0f },{ 10.0f,1.0f,10.0f },
          //天球、芝生、芝生、椅子、椅子
         { 10.0f,1.0f,10.0f },{ 10.0f,1.0f,10.0f },{ 10.0f,1.0f,10.0f },{ 1.0f,1.0f,1.0f },{ 1.0f,1.0f,1.0f },
           //机、台所、家
          { 1.0f,1.0f,1.0f },{ 1.0f,1.0f,1.0f },{ 1.0f,1.0f,1.0f }
    };

    VECTOR posision[OBJECT_NUM] =
    {
        //天球、芝生、芝生、芝生、芝生
       {0.0f,0.0f,0.0f},{0.0f,-2.0f,0.0f },{145.0f,-2.0f,0.0f },{-145.0f,-2.0f,0.0f },{0.0f,-2.0f,145.0f },
         //芝生、芝生、芝生、芝生、芝生
        {0.0f,-2.0f,-145.0f },{145.0f,-2.0f,145.0f },{-145.0f,-2.0f,-145.0f },{-145.0f,-2.0f,145.0f },{145.0f,-2.0f,-145.0f },
          //芝生、芝生、芝生、椅子、椅子
         {290.0f,-2.0f,-145.0f },{290.0f,-2.0f,0.0f },{290.0f,-2.0f,145.0f },{210.0f,0.2f,0.0f },{-70.0f,0.2f,0.0f },
           //机、台所、家
          {70.0f,0.0f,0.0f },{200.0f,0.0,700.0f},{0.0f,0.0f,0.0f}

    };

    VECTOR rotate[OBJECT_NUM] =
    {
        //天球、芝生、芝生、芝生、芝生
       {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},
         //芝生、芝生、芝生、芝生、芝生
        {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},
          //芝生、芝生、芝生、椅子、椅子
         {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,3.14f,0.0f},
           //机、台所、家
          {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}

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




