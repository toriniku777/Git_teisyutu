#include "SoundManeger.h"


//staticメンバ変数はここで書く作業が必要
vector<int>SoundManeger::m_hndl;

//---------------------
//初期化
//---------------------
void SoundManeger::Init()
{
   //中身を空にする
    m_hndl.clear();
}


//---------------------
//データ関連のロード
//---------------------
void SoundManeger::Load()
{
    const char* filePath[SOUND_NUM] = {
        "Data/Sound/bgm00.mp3",
        "Data/Sound/se_plshot.mp3",
        "Data/Sound/se_explore.mp3"
    };
     
    for (int i = 0; i < SOUND_NUM; i++)
    {
        int hndl = LoadSoundMem(filePath[i]);
        m_hndl.push_back(hndl);
    }
}

//---------------------
//終了処理
//---------------------
void SoundManeger::Exit()
{
    for (int i = 0; i<m_hndl.size(); i++)
    {
        if (m_hndl[i] != -1)
        {
            DeleteSoundMem(m_hndl[i]);
            m_hndl[i] = -1;
       }
    }

}

//---------------------
//毎フレーム呼ぶ処理
//---------------------
bool SoundManeger::Play(tagID id,
    int type, bool isStart)
{
   int rat= PlaySoundMem(m_hndl[id], type, isStart);
   if (rat == -1)return false;
   else return true;
}

//---------------------
//更新したデータを反映させる
//---------------------
void SoundManeger::Stop (tagID id)
{
    StopSoundMem(m_hndl[id]);
}

//---------------------
//描画処理
//---------------------
void SoundManeger::AllStop()
{
    for (int i = 0; i < m_hndl.size(); i++)
    {
        StopSoundMem(m_hndl[i]);
    }
}

bool SoundManeger::IsPlay(tagID id)
{
   int result = CheckSoundMem(m_hndl[id]);
   if (result == 1)return true;
   else return false;
}