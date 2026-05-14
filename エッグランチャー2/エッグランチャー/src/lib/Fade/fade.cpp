#include	"fade.h"
#include	<DxLib.h>

#define		FADE_SPEED (10)			//フェード速度
#define		FADE_SIZE_X (1280)		//フェード画面の横幅
#define		FADE_SIZE_Y (720)		//フェード画面の縦幅

//フェードの各種状態
enum tagFadeState
{
	FADE_NON,			//フェードなし
	FADE_IN,			//フェードイン中（徐々に画面が出現）
	FADE_OUT,			//フェードアウト中（徐々に画面が消える）
	FADE_OUT_WAIT,		//フェードアウト後の真っ暗状態
};

//フェード処理用構造体
typedef struct {
	tagFadeState m_state;		//現在のフェード状況
	int m_count;				//フェード時間のカウント
	bool m_fadeflg;
}FADE_DATA;

FADE_DATA g_fade;

//---------------------------
//フェード初期化
//---------------------------
void Fade::InitFade()
{
	g_fade.m_state = FADE_NON;
	g_fade.m_count = 0;
	g_fade.m_fadeflg = false;
}

//---------------------------
//フェード更新処理
//---------------------------
void Fade::StepFade()
{
	//状態に合せて行動変化
	//実際に処理をするのは下記の二つだけ
	switch (g_fade.m_state)
	{
	case FADE_IN:

		//徐々に数字を増やして明るくする
		g_fade.m_count -= FADE_SPEED;
		if (g_fade.m_count <= 0)
		{
			g_fade.m_count = 0;
			g_fade.m_state = FADE_NON;
		}
		break;

	case FADE_OUT:

		//徐々に数字を増やして暗くする
		g_fade.m_count += FADE_SPEED;
		if (g_fade.m_count >= 255)
		{
			g_fade.m_count = 255;
			g_fade.m_state = FADE_OUT_WAIT;
		}
		break;
	}
}

//---------------------------
//フェード用の画像描画
//---------------------------
void Fade::DrawFade()
{
	//黒画像を描画
	switch (g_fade.m_state)
	{
	case FADE_IN:
	case FADE_OUT:
	case FADE_OUT_WAIT:

		//まずはここでアルファ値をセットする
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_fade.m_count);

		//フェード用の黒い四角を表示
		DrawBox(0, 0, FADE_SIZE_X, FADE_SIZE_Y,
			GetColor(0, 0, 0), TRUE);

		//ほかの画像に影響を出さないよう、初期設定に戻す
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		break;

	}
}


//---------------------------
//フェードインリクエスト
//---------------------------
void Fade::RequestFadeIn()
{
	if(g_fade.m_fadeflg)return;

	//徐々に暗くするので、最初はMAXに
	g_fade.m_count = 255;
	g_fade.m_state = FADE_IN;
	g_fade.m_fadeflg = true;
}

//---------------------------
//フェードアウトリクエスト
//---------------------------
void Fade::RequestFadeOut()
{
	if (g_fade.m_fadeflg)return;

	//徐々に暗くするので、最初は透明の0に
	g_fade.m_count = 0;
	g_fade.m_state = FADE_OUT;
	g_fade.m_fadeflg = true;
}

//---------------------------
//フェードインが終了したか
//---------------------------
bool Fade::IsEndFadeIn()
{
	//フェードイン時はまだやっている
	if (g_fade.m_state == FADE_IN)
	{
		return false;
	}
	//他は少なくともフェードインではない
	else {
		g_fade.m_fadeflg =false;
		return true;
	}
}

bool Fade::IsEndFadeOut()
{
	//フェードアウト時はまだやっている
	if (g_fade.m_state == FADE_OUT)
	{
		return false;
	}
	//他は少なくともフェードアウトではない
	else {
		g_fade.m_fadeflg = false;
		return true;
	}
}