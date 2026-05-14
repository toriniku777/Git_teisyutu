#include <DxLib.h>
#include <math.h>
#include "src/Camera/Camera.h"
#include "src/Player/Player.h"
#include "src/Camera/CameraManeger.h"
#include "src/Camera/DebugCamera.h"
#include "src/Scene/SceneManeger.h"
#include "lib/FPS/fps.h"
#include "lib/Fade/fade.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウモードで起動
	ChangeWindowMode(TRUE);
	// ウィンドウのサイズを変更
	SetGraphMode(1280, 720, 32);

	// DxLibの初期化
	if (DxLib_Init() == -1) return -1;

	// 裏描画を行う設定
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SceneManeger scenemaneger;
	// インスタンス作成と初期化
	SceneManeger Loop();

	// カメラ設定
	CameraManeger CameraManeger;
	CameraManeger.Init();
	SetCameraNearFar(1.0f, 1000.0f);
	Fade::InitFade();

	
	// ゲームのメインループ
	while (ProcessMessage() != -1)
	{
		// エスケープキーが押されたら強制終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

		if (Fps::IsNextFrame() == false)continue;

		// 画面を消去する
		ClearDrawScreen();

		// ゲームの処理ここから書く============

		scenemaneger.Loop();

		scenemaneger.Draw();

		Fade::StepFade();
		Fade::DrawFade();
		// ゲームの処理ここまで================

		// 裏画面と入れ替える
		ScreenFlip();
	}

	
	// DxLibの使用を終わらせる
	DxLib_End();

	return 0;
}