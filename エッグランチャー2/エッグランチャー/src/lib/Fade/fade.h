#pragma once

class Fade 
{
public:

	//フェードを初期化する
	static void InitFade();

	//フェード処理更新
	static void StepFade();

	//フェード用の画像描画
	static void DrawFade();

	//フェードインリクエスト
	static void RequestFadeIn();

	//フェードアウトリクエスト
	static void RequestFadeOut();

	//フェードインが終了したか
	static bool IsEndFadeIn();

	//フェードアウトが終了したか
	static bool IsEndFadeOut();
};
