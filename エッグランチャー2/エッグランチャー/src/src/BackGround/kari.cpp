// コンストラクタ・デストラクタ

//CFiled::CFiled()
//
//{
//
//	Init();
//
//}
//
//CFiled::~CFiled()
//
//{
//
//	Exit();
//
//}
//
////背景の初期化
//
//void CFiled::Init()
//
//{
//
//	fieldhndl = -1;
//
//	olihndl = -1;
//
//	oliPos = { 55.0f,0.5f,60.0 };
//
//	stairshndl = -1;
//
//	stairsMechanismCheck = 0;
//
//	EventstairsCameraFlag = 0;
//
//	stairsScale = { 0.1f,0.1f,0.1f };
//
//	stairsPos = { -6500.0f,0.0f,0.0f };
//
//	keyhndl = -1;
//
//	keyradius = 3.0f;
//
//	KeyisActive = true;
//
//	keyScale = { 0.1f,0.1f,0.1f };
//
//	keyPos = { -70.0f,10.0f,-60.0f };
//
//	m_kRot = { 0.0f,0.0f,0.0f };
//
//	switchhndl = -1;
//
//	switchhndl1 = -1;
//
//	switchradius = 5.0f;
//
//	switchHitFlag = false;
//
//	switchScale = { 0.1f,0.1f,0.1f };
//
//	switchPos = { 70.0f,7.0f,55.0f };
//
//	goalhndl = -1;
//
//	goalradius = 3.0f;
//
//	goalScale = { 0.1f,0.1f,0.1f };
//
//	goalPos = { 70.0f,10.0f,-70.0f };
//
//	m_Rot = { 0.0f,0.0f,0.0f };
//
//	isHitFlag = false;
//
//}
//
////更新処理
//
//void CFiled::Step()
//
//{
//
//	m_kRot.y += 0.1f;
//
//	//スイッチが押されたら階段の仕掛けが動く
//
//	if (switchHitFlag == true)
//
//	{
//
//		StairsMechanism();
//
//		//仕掛けがちゃんと動いたかチェック
//
//		if (stairsPos.y <= -30.0f)
//
//		{
//
//			stairsMechanismCheck = 1;
//
//		}
//
//	}
//
//	else if (stairsPos.y > 0.0f)
//
//	{
//
//		stairsPos.y--;
//
//	}
//
//}
//
////ロード
//
//void  CFiled::Load()
//
//{
//
//	if (fieldhndl == -1)
//
//	{
//
//		fieldhndl = MV1LoadModel(FILED1_MODEL_PATH);
//
//	}
//
//	if (olihndl == -1)
//
//	{
//
//		olihndl = MV1LoadModel(GIMMICK_MODEL_PATH);
//
//	}
//
//	if (keyhndl == -1)
//
//	{
//
//		keyhndl = MV1LoadModel(KEY_MODEL_PATH);
//
//	}
//
//	if (stairshndl == -1)
//
//	{
//
//		stairshndl = MV1LoadModel(STAIRS_MODEL_PATH);
//
//	}
//
//	if (switchhndl == -1)
//
//	{
//
//		switchhndl = MV1LoadModel(SWITCH_MODEL_PATH);
//
//	}
//
//	if (switchhndl1 == -1)
//
//	{
//
//		switchhndl1 = MV1LoadModel(SWITCHPUSH_MODEL_PATH);
//
//	}
//
//	if (goalhndl == -1)
//
//	{
//
//		goalhndl = MV1LoadModel(GOAL_MODEL_PATH);
//
//	}
//
//	//ここで初期値をセットしちゃう
//
//	MV1SetPosition(olihndl, oliPos);
//
//	MV1SetPosition(switchhndl, switchPos);
//
//	MV1SetPosition(switchhndl1, switchPos);
//
//	MV1SetPosition(keyhndl, keyPos);
//
//	MV1SetPosition(stairshndl, stairsPos);
//
//	MV1SetPosition(goalhndl, goalPos);
//
//	//ここでスケールも決めちゃう
//
//	MV1SetScale(keyhndl, keyScale);
//
//	MV1SetScale(stairshndl, stairsScale);
//
//	MV1SetScale(switchhndl, switchScale);
//
//	MV1SetScale(goalhndl, goalScale);
//
//	//ポリゴンの情報取得
//
//	MV1SetupCollInfo(fieldhndl);
//
//	MV1SetupCollInfo(olihndl);
//
//	MV1SetupCollInfo(stairshndl);
//
//}
//
////フィールドのアップデート
//
//void CFiled::Update()
//
//{
//
//	MV1SetPosition(keyhndl, keyPos);
//
//	MV1SetPosition(stairshndl, stairsPos);
//
//	MV1SetPosition(switchhndl, switchPos);
//
//	MV1SetPosition(goalhndl, goalPos);
//
//	MV1SetRotationXYZ(keyhndl, m_kRot);
//
//	MV1SetupCollInfo(stairshndl);
//
//}
//
////描画
//
//void  CFiled::Draw()
//
//{
//
//	//アクティブがtrueなら表示
//
//	if (KeyisActive == true)
//
//	{
//
//		MV1DrawModel(keyhndl);
//
//	}
//
//	//フラグがtrueならスイッチが押されている状態に
//
//	if (switchHitFlag == true)
//
//	{
//
//		MV1DrawModel(switchhndl1);
//
//	}
//
//	else
//
//	{
//
//		MV1DrawModel(switchhndl);
//
//	}
//
//	MV1DrawModel(olihndl);
//
//	MV1DrawModel(fieldhndl);
//
//	MV1DrawModel(stairshndl);
//
//	MV1DrawModel(goalhndl);
//
//	////当たり判定を目視できるように
//
//	//DrawSphere3D(GetgoalCenter(), goalradius,
//
//	//	16, GetColor(255, 0, 0),
//
//	//	GetColor(255, 0, 0), FALSE);
//
//	/*if (isHitFlag == true)
//
//	{
//
//		DrawFormatString(32, 60, GetColor(255, 255, 255), "Hit!");
//
//	}*/
//
//}
//
////破棄
//
//void  CFiled::Exit()
//
//{
//
//	if (fieldhndl != -1)
//
//	{
//
//		MV1TerminateCollInfo(fieldhndl);
//
//		MV1DeleteModel(fieldhndl);
//
//		fieldhndl = -1;
//
//	}
//
//	if (olihndl != -1)
//
//	{
//
//		MV1TerminateCollInfo(olihndl);
//
//		MV1DeleteModel(olihndl);
//
//		olihndl = -1;
//
//	}
//
//	if (keyhndl != -1)
//
//	{
//
//		MV1DeleteModel(keyhndl);
//
//		keyhndl = -1;
//
//	}
//
//	if (stairshndl != -1)
//
//	{
//
//		MV1DeleteModel(stairshndl);
//
//		stairshndl = -1;
//
//	}
//
//	if (switchhndl != -1)
//
//	{
//
//		MV1DeleteModel(switchhndl);
//
//		switchhndl = -1;
//
//	}
//
//	if (switchhndl1 != -1)
//
//	{
//
//		MV1DeleteModel(switchhndl1);
//
//		switchhndl1 = -1;
//
//	}
//
//	if (goalhndl != -1)
//
//	{
//
//		MV1DeleteModel(goalhndl);
//
//		goalhndl = -1;
//
//	}
//
//}
//
////階段の仕掛け起動
//
//void CFiled::StairsMechanism()
//
//{
//
//	if (stairsPos.y <= 60.0f)
//
//	{
//
//		stairsPos.y += 0.1f;
//
//	}
//
//}
//
//// ゴール位置情報取得
//
//VECTOR CFiled::GetgoalPos()
//
//{
//
//	return goalPos;
//
//}
//
//// 階段位置情報取得
//
//VECTOR CFiled::GetStairsPos()
//
//{
//
//	return stairsPos;
//
//}
//
//// 鍵位置情報取得
//
//VECTOR CFiled::GetkeyPos()
//
//{
//
//	return keyPos;
//
//}
//
//// 当たり判定の座標用
//
//VECTOR CFiled::GetgoalCenter()
//
//{
//
//	// 基本は物体の座標の位置
//
//	VECTOR ret = goalPos;
//
//	// 高さだけ足元からの半分あげる
//
//	ret.y += goalradius;
//
//	return ret;
//
//}
//
//// 当たり判定の座標用
//
//VECTOR CFiled::GetkeyCenter()
//
//{
//
//	// 基本は物体の座標の位置
//
//	VECTOR ret = keyPos;
//
//	// 高さだけ足元からの半分あげる
//
//	ret.y += keyradius;
//
//	return ret;
//
//}
//
//// 階段にカメラが向けられたらチェックする
//
//void CFiled::EventStairsCameraCheck()
//
//{
//
//	EventstairsCameraFlag = 1;
//
//}
//
//// 当たり判定
//
//// @center  :  当たり判定する相手の座標
//
//// @radius　:  球の半径
//
//// @return  :  押し戻すべき距離と方向
//
//VECTOR CFiled::FieldHitCheck(VECTOR center, float radius)
//
//{
//
//	//押し戻し距離を呼び戻し元に伝えるために使用
//
//	VECTOR result = { 0.0f };
//
//	//当たり判定が格納される構造体
//
//	MV1_COLL_RESULT_POLY_DIM col;
//
//	//当たり判定を行い、その結果を構造体に格納
//
//	col = MV1CollCheck_Sphere(fieldhndl, -1, center, radius);
//
//	//ヒットしたポリゴンがあれば、フラグをオンに
//
//	if (col.HitNum != 0)
//
//	{
//
//		//当たった時の処理
//
//		// 当たったデータをすべてチェックする
//
//		for (int i = 0; i < col.HitNum; i++)
//
//		{
//
//			//まず中心点から最近点を引き算
//
//			VECTOR v = VSub(center, col.Dim[i].HitPosition);
//
//			//取得したベクトルを三平方の定理で長さに変換
//
//			float len = VSize(v);
//
//			//実際にめり込んだ距離を計算
//
//			len = radius - len;
//
//			//法線をめり込んだ距離分掛け算する
//
//			v = VScale(col.Dim[i].Normal, len);
//
//			//計算結果を合算していく
//
//			result = VAdd(result, v);
//
//		}
//
//	}
//
//	//終了前にコリジョンデータを破棄
//
//	MV1CollResultPolyDimTerminate(col);
//
//	return result;
//
//}
//
//VECTOR CFiled::oliHitCheck(VECTOR center, float radius)
//
//{
//
//	//押し戻し距離を呼び戻し元に伝えるために使用
//
//	VECTOR result = { 0.0f };
//
//	MV1_COLL_RESULT_POLY_DIM col;
//
//	//当たり判定を行い、その結果を構造体に格納
//
//	col = MV1CollCheck_Sphere(olihndl, -1, center, radius);
//
//	//ヒットしたポリゴンがあれば、フラグをオンに
//
//	// ポリゴンと当たった
//
//	if (col.HitNum != 0)
//
//	{
//
//		//当たった時の処理
//
//		// 当たったデータをすべてチェックする
//
//		for (int i = 0; i < col.HitNum; i++)
//
//		{
//
//			//まず中心点から最近点を引き算
//
//			VECTOR v = VSub(center, col.Dim[i].HitPosition);
//
//			//取得したベクトルを三平方の低利で長さに変換
//
//			float len = VSize(v);
//
//			//実際にめり込んだ距離を計算
//
//			len = radius - len;
//
//			//法線をめり込んだ距離分掛け算する
//
//			v = VScale(col.Dim[i].Normal, len);
//
//			//計算結果を合算していく
//
//			result = VAdd(result, v);
//
//		}
//
//	}
//
//	//終了前にコリジョンデータを破棄
//
//	MV1CollResultPolyDimTerminate(col);
//
//	return result;
//
//}
//
//VECTOR CFiled::stairsHitCheck(VECTOR center, float radius)
//
//{
//
//	//押し戻し距離を呼び戻し元に伝えるために使用
//
//	VECTOR result = { 0.0f };
//
//	MV1_COLL_RESULT_POLY_DIM col;
//
//	//当たり判定を行い、その結果を構造体に格納
//
//	col = MV1CollCheck_Sphere(stairshndl, -1, center, radius);
//
//	//ヒットしたポリゴンがあれば、フラグをオンに
//
//	// ポリゴンと当たった
//
//	if (col.HitNum != 0)
//
//	{
//
//		//当たった時の処理
//
//		// 当たったデータをすべてチェックする
//
//		for (int i = 0; i < col.HitNum; i++)
//
//		{
//
//			//まず中心点から最近点を引き算
//
//			VECTOR v = VSub(center, col.Dim[i].HitPosition);
//
//			//取得したベクトルを三平方の低利で長さに変換
//
//			float len = VSize(v);
//
//			//実際にめり込んだ距離を計算
//
//			len = radius - len;
//
//			//法線をめり込んだ距離分掛け算する
//
//			v = VScale(col.Dim[i].Normal, len);
//
//			//計算結果を合算していく
//
//			result = VAdd(result, v);
//
//		}
//
//	}
//
//	//終了前にコリジョンデータを破棄
//
//	MV1CollResultPolyDimTerminate(col);
//
//	return result;
//
//}
//
//VECTOR CFiled::switchHitCheck(VECTOR center, float radius)
//
//{
//
//	//押し戻し距離を呼び戻し元に伝えるために使用
//
//	VECTOR result = { 0.0f };
//
//	MV1_COLL_RESULT_POLY_DIM col;
//
//	//一旦当たっていない状態にしておく
//
//	switchHitFlag = false;
//
//	//当たり判定を行い、その結果を構造体に格納
//
//	col = MV1CollCheck_Sphere(switchhndl, -1, center, radius);
//
//	//col = MV1CollCheck_LineDim //マルの当たり判定を四角に作り変えます
//
//	//ヒットしたポリゴンがあれば、フラグをオンに
//
//	// ポリゴンと当たった
//
//	if (col.HitNum != 0)
//
//	{
//
//		//当たった時の処理
//
//		//仕掛けのフラグをオンにする
//
//		switchHitFlag = true;
//
//		// 当たったデータをすべてチェックする
//
//		for (int i = 0; i < col.HitNum; i++)
//
//		{
//
//			//まず中心点から最近点を引き算
//
//			VECTOR v = VSub(center, col.Dim[i].HitPosition);
//
//			//取得したベクトルを三平方の低利で長さに変換
//
//			float len = VSize(v);
//
//			//実際にめり込んだ距離を計算
//
//			len = radius - len;
//
//			//法線をめり込んだ距離分掛け算する
//
//			v = VScale(col.Dim[i].Normal, len);
//
//			//当たり判定を少し埋める
//
//			v = VScale(v, 0.1);
//
//			//計算結果を合算していく
//
//			result = VAdd(result, v);
//
//		}
//
//	}
//
//	//終了前にコリジョンデータを破棄
//
//	MV1CollResultPolyDimTerminate(col);
//
//	return result;
//
//}
//
//ごめんヘッダーも送って
//
//#pragma once
//
//#include <DxLib.h>
//
//class CFiled {
//
//private:
//
//	int fieldhndl;                //フィールドハンドル
//
//	int olihndl;                  //檻ハンドル
//
//	VECTOR oliPos;                //檻の座標
//
//	int stairshndl;               //階段ハンドル
//
//	int stairsMechanismCheck;     //階段の仕掛けが最後まで動いたかチェック
//
//	int EventstairsCameraFlag;    //階段にカメラが一度でも向けられたかチェック
//
//	VECTOR stairsScale;           //階段のスケール
//
//	VECTOR stairsPos;             //階段の座標
//
//	int keyhndl;                  //鍵ハンドル
//
//	float keyradius;              //鍵半径取得
//
//	bool KeyisActive;             //鍵の生存フラグ
//
//	VECTOR keyScale;              //鍵のスケール
//
//	VECTOR keyPos;                //鍵の座標
//
//	VECTOR m_kRot;                //鍵の回転速度
//
//	int switchhndl;               //ボタンハンドル
//
//	int switchhndl1;              //ボタンハンドル1
//
//	float switchradius;           //ボタン半径取得
//
//	bool switchHitFlag;           //ボタンが押されたか
//
//	VECTOR switchScale;           //ボタンのスケール
//
//	VECTOR switchPos;             //ボタンの座標
//
//	int goalhndl;                 //ゴールハンドル
//
//	float goalradius;             //ゴール半径取得
//
//	VECTOR goalScale;             //ゴールのスケール
//
//	VECTOR goalPos;               //ゴールの座標
//
//	VECTOR m_Rot;                 //回転速度
//
//	bool isHitFlag;               //フィールドとの当たり判定
//
//public:
//
//	// コンストラクタ・デストラクタ
//
//	CFiled();
//
//	~CFiled();
//
//	//初期化
//
//	void Init();
//
//	//ロード
//
//	void Load();
//
//	//更新処理
//
//	void Step();
//
//	//フィールドのアップデート
//
//	void Update();
//
//	//描画
//
//	void Draw();
//
//	//破棄
//
//	void Exit();
//
//	//階段の仕掛け起動
//
//	void StairsMechanism();
//
//	// ゴール位置情報取得
//
//	VECTOR GetgoalPos();
//
//	// 階段位置情報取得
//
//	VECTOR GetStairsPos();
//
//	// 鍵位置情報取得
//
//	VECTOR GetkeyPos();
//
//	// 当たり判定の座標用
//
//	VECTOR GetgoalCenter();
//
//	// 当たり判定の座標用
//
//	VECTOR GetkeyCenter();
//
//	// 階段にカメラが向けられたらチェックする
//
//	void EventStairsCameraCheck();
//
//	// カメラが一度でも向けられたかを取得
//
//	int GetEventstairsCamera() { return EventstairsCameraFlag; }
//
//	// 仕掛けが最後まで動いたかを取得
//
//	int GetstairsMechanismCheck() { return stairsMechanismCheck; }
//
//	// 鍵の当たり判定の半径サイズを取得
//
//	float GetKeyRadius() { return keyradius; }
//
//	// ゴールの当たり判定の半径サイズを取得
//
//	float GetgoalRadius() { return goalradius; }
//
//	//鍵の生存情報取得
//
//	bool KeyIsActive() { return KeyisActive; }
//
//	void SetKeyActive(bool active) { KeyisActive = active; }
//
//	//ボタンの押されたかのフラグ情報を取得
//
//	bool GetswitchHitFlag() { return switchHitFlag; }
//
//	// 当たり判定
//
//	// @center  :  当たり判定する相手の座標
//
//	// @radius　:  球の半径
//
//	// @return  :  押し戻すべき距離と方向
//
//	VECTOR FieldHitCheck(VECTOR center, float radius);
//
//	VECTOR oliHitCheck(VECTOR center, float radius);
//
//	VECTOR stairsHitCheck(VECTOR center, float radius);
//
//	VECTOR switchHitCheck(VECTOR center, float radius);
//
//
//};
