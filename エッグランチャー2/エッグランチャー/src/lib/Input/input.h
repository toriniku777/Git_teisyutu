#pragma once

#define KEY_SHOT	 (0b1)
#define KEY_JUMP	 (0b10)
#define KEY_CHANGE_1 (0b100)
#define KEY_CHANGE_2 (0b1000)
#define KEY_CHANGE_3 (0b10000)
#define KEY_CHANGE_4 (0b100000)
#define KEY_EGGSHOT  (0b1000000)
 
class Input
{
public:

	//キー入力初期化
	static void Init();

	//キー入力情報更新
	static void Update();

	//キー入力判定（通常判定）
	static bool IsInputTrg(unsigned int key);

	//キー入力判定（トリガー判定）
	static bool IsInputRep(unsigned int key);
};
