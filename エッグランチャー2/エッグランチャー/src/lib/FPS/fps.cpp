#include <DxLib.h>
#include "fps.h"

#define  FRAME_RATE (60)
#define  FRAME_RATE_MILLI_SECOND (1000 / FRAME_RATE)

//FPSを表示するのに使用するデータがまとまった集合体
typedef struct {
	float m_frameRate;//今のフレームレートを保存
	int m_nowTime;//現在時間
	int m_prevTime;//ひとつ前の時間
	int m_prevDrawTime;//一つ目の描画したPC時間
	int m_count;//カウント用
}FpsData;

static FpsData g_fps;//実際にfps表示に使用する変数

//--------------------------------
//		変数関連初期化
//--------------------------------
void Fps::InitFps()
{
	g_fps.m_frameRate = 0.0f;
	g_fps.m_prevTime = g_fps.m_prevDrawTime = GetNowCount();//ここで現在のカウントを取得しておく
	g_fps.m_nowTime = 0;
	g_fps.m_count = 0;
}
//------------------------------
//FPS表示関数
//------------------------------
void Fps::PrintFps()
{
	//まずはカウントを増やす
	g_fps.m_count++;
	//現在の時間を取得
	g_fps.m_nowTime = GetNowCount();
	//前回の時間と今回の時間の差を取得
	int difTime = g_fps.m_nowTime - g_fps.m_prevDrawTime;
	//差異が1秒以上あれば計算開始（１秒に一回フレームレートの表示を開始）
	if (difTime >= 1000) 
	{
		//ある程度正常に動いていたら、m_countは６０になっているはず
		float frameCount = (float)(g_fps.m_count * 1000);
		//表示するfpsを更新
		g_fps.m_frameRate = frameCount / difTime;
		//カウントは０に初期化
		g_fps.m_count = 0;
		//ひとつ前の時間を更新
		g_fps.m_prevDrawTime = g_fps.m_nowTime;
	}
	//文字の表示　引数は「横の位置」「縦の位置」「色」「文字」
	DrawFormatString(1180, 32, GetColor(255, 0, 0), "FPS:%.2f", g_fps.m_frameRate);

}



bool Fps::IsNextFrame()
{
	g_fps.m_nowTime = GetNowCount();

	int difTime = g_fps.m_nowTime - g_fps.m_prevDrawTime;

	if (difTime >= FRAME_RATE_MILLI_SECOND)
	{
		return true;
	}
	else return false;
}

void Fps::StepFps()
{
	g_fps.m_prevTime = g_fps.m_nowTime;
}