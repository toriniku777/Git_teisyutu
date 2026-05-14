#include "SceneManeger.h"
#include "../Sistem/SoundManeger.h"
#include "../../lib/Input/input.h"
#include "../../lib/FPS/fps.h"
#include "../../lib/Fade/fade.h"

//-----------------
//コンストラクタ
//-----------------
SceneManeger::SceneManeger()
{
	//最初のシーンを設定
	m_sceneID = TITLE;

	
	SoundManeger::Init();
	Input::Init();
	Fps::InitFps();

	SoundManeger::Load();

	Fps::StepFps();

	m_hndl = -1;
	if (m_hndl == -1)
	{
		m_hndl =LoadGraph("Data/Back/title.jpg");
		m_hndl2 = LoadGraph("Data/Back/result.jpg");
	}
}

SceneManeger::~SceneManeger()
{
	SoundManeger::Exit();
}

//--------------------
//初期化
//--------------------
int SceneManeger::Loop()
{
	//ゲームが終了したかを外部に伝えるため
	int res = -1;
	Input::Update();
	switch (m_sceneID)
	{
	case SceneManeger::TITLE:
		
		Fade::RequestFadeIn();
		if (Input::IsInputTrg(KEY_SHOT))
		{
			Fade::RequestFadeOut();
			if (Fade::IsEndFadeOut())
			{
				m_sceneID = SceneManeger::GAME;//次へ進む
			}
			
		}
		
		
		break;

	case SceneManeger::GAME:
		if (m_play.Loop() != -1)
		{
			Fade::RequestFadeIn();
				m_sceneID = SceneManeger::RESULT;//次へ進む
		
		}
		
		break;

	case SceneManeger::RESULT:
		Fade::RequestFadeOut();

		if (Input::IsInputTrg(KEY_SHOT))
		{
			
			m_sceneID = SceneManeger::TITLE;//次へ進む
		}
		
		break;


	}
	return res;
}

//--------------------
//更新処理
//--------------------
void SceneManeger::Draw()
{
	switch (m_sceneID)
	{
	case SceneManeger::TITLE:
		DrawRotaGraph(1280.0f / 2, 720.0f / 2, 1.0f, 0.0f, m_hndl, TRUE);
		break;

	case SceneManeger::GAME:
		m_play.Draw();
		break;

	case SceneManeger::RESULT:
		DrawRotaGraph(1280.0f / 2, 720.0f / 2, 1.0f, 0.0f, m_hndl2, TRUE);
		break;
	}
	Fps::PrintFps();

}
