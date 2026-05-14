#include "input.h"
#include <Dxlib.h>

//キーボード入力用構造体
typedef struct {
	unsigned int m_nowKey;		//今回のボタン情報
	unsigned int m_PrevKey;		//1フレーム前のボタン情報
}INPUT_DATA;

//キー入力用にグローバル変数を作成
static INPUT_DATA g_inputData;


//----------------
//キー入力情報更新
//----------------
void Input::Init()
{
	g_inputData.m_nowKey = g_inputData.m_PrevKey = 0;
}



void Input::Update()
{
	g_inputData.m_PrevKey = g_inputData.m_nowKey;

	g_inputData.m_nowKey = 0;

	if (CheckHitKey(KEY_INPUT_Z))g_inputData.m_nowKey |= KEY_SHOT;
	if (CheckHitKey(KEY_INPUT_SPACE))g_inputData.m_nowKey |= KEY_JUMP;
	if (CheckHitKey(KEY_INPUT_1))g_inputData.m_nowKey |= KEY_CHANGE_1;
	if (CheckHitKey(KEY_INPUT_2))g_inputData.m_nowKey |= KEY_CHANGE_2;
	if (CheckHitKey(KEY_INPUT_3))g_inputData.m_nowKey |= KEY_CHANGE_3;
	if (CheckHitKey(KEY_INPUT_4))g_inputData.m_nowKey |= KEY_CHANGE_4;
	if (GetMouseInput() & MOUSE_INPUT_LEFT)g_inputData.m_nowKey |= KEY_EGGSHOT;

}


bool Input::IsInputTrg(unsigned int key)
{
	if ((g_inputData.m_PrevKey & key) == 0 && (g_inputData.m_nowKey & key) != 0)
		return true;
	else return false;
}

bool Input::IsInputRep(unsigned int key)
{
	if ((g_inputData.m_nowKey & key) != 0) return true;
	else return false;
}