#include "Player.h"
#include <math.h>
#include "../../lib/Input/input.h"

#define DEBUG

//#define XINPUT_BUTTON_DPAD_UP		(0)	// デジタル方向ボタン上
//#define XINPUT_BUTTON_DPAD_DOWN		(1)	// デジタル方向ボタン下
//#define XINPUT_BUTTON_DPAD_LEFT		(2)	// デジタル方向ボタン左
//#define XINPUT_BUTTON_DPAD_RIGHT	(3)	// デジタル方向ボタン右
//#define XINPUT_BUTTON_START		(4)	// STARTボタン
//#define XINPUT_BUTTON_BACK		(5)	// BACKボタン
//#define XINPUT_BUTTON_LEFT_THUMB	(6)	// 左スティック押し込み
//#define XINPUT_BUTTON_RIGHT_THUMB	(7)	// 右スティック押し込み
//#define XINPUT_BUTTON_LEFT_SHOULDER	(8)	// LBボタン
//#define XINPUT_BUTTON_RIGHT_SHOULDER	(9)	// RBボタン
//#define XINPUT_BUTTON_A			(12)	// Aボタン
//#define XINPUT_BUTTON_B			(13)	// Bボタン
//#define XINPUT_BUTTON_X			(14)	// Xボタン
//#define XINPUT_BUTTON_Y			(15)	// Yボタン

//定義関連
static const char PLAYER_MODEL_PATH[] = {
	"Data/Model/Chikin/ニワトリ - コピー.x",
};

static const float ROTATE_SPEED = 0.1f;
static const float MOVE_SPEED = 10.0f;
static const float SHOT_SPEED = 10.0f;
static const VECTOR ZERO = { 0.0f,0.0f,0.0f };
//-------------------------------

//--------------------
//コンストラクタ
//--------------------
Player::Player()
{
	//初期化
	memset(&m_pos, 0, sizeof(VECTOR));
	memset(&m_rot, 0, sizeof(VECTOR));
	memset(&m_speed, 0, sizeof(VECTOR));
	m_state = PLSTATE_NORMAL;
}

//---------------------
//デストラクタ
//---------------------
Player::~Player()
{

	Exit();
}

//---------------------
//初期化
//---------------------
void Player::Init()
{
	m_pos = { 0.0f,0.0f,0.0 };
	m_rot = { 0.0f,3.15f,0.0f };
	m_scale = { 2.0f,2.0f,2.0f };
	m_speed = ZERO;
	m_state = PLSTATE_NORMAL;
	m_isActive = true;
	m_radius = 52.0f;
	m_hndl = -1;

	//追加
	m_CameraRot = { 0.0f,0.0f,0.0f };

}
//---------------------
//初期化
//---------------------
void Player::Init(VECTOR vPos, VECTOR vRot)
{
	m_pos = vPos;
	m_rot = vRot;
	memset(&m_speed, 0, sizeof(VECTOR));
	m_state = PLSTATE_NORMAL;


}

//---------------------
//データ関連のロード
//---------------------
void Player::Load()
{
	if (m_hndl == -1)
	{
		m_hndl = MV1LoadModel(PLAYER_MODEL_PATH);
	}
}

//---------------------
//終了処理
//---------------------
void Player::Exit()
{
	if (m_hndl != -1)
	{
		MV1DeleteModel(m_hndl);
		m_hndl = -1;
	}
}

//---------------------
//毎フレーム呼ぶ処理
//---------------------
void Player::Step(ShotManeger& shot)
{

	//弾の発射
	if (Input::IsInputTrg(KEY_EGGSHOT))
	{
		VECTOR speed;
		speed.x = sinf(m_rot.y + 0.0) * -SHOT_SPEED;
		speed.y = m_rot.x;
		speed.z = cosf(m_rot.y + 0.0) * -SHOT_SPEED;
		VECTOR pos = m_pos;
		pos.y += 25.0f;

		shot.RequestPlayerShot(pos, speed);
	}

	
	//追加
	m_speed = { 0.0f,0.0f,0.0f };
	bool IsMove = false;
	if (CheckHitKey(KEY_INPUT_W)) {
		m_speed.z = MOVE_SPEED;
		IsMove = true;
	}
	else if (CheckHitKey(KEY_INPUT_S)) {
		m_speed.z = -MOVE_SPEED;
		IsMove = true;
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		m_speed.x = -MOVE_SPEED;
		IsMove = true;
	}
	else if (CheckHitKey(KEY_INPUT_D)) {
		m_speed.x = MOVE_SPEED;
		IsMove = true;
	}

	if (CheckHitKey(KEY_INPUT_U)) {
		m_speed.y += MOVE_SPEED;
		IsMove = true;
	}

	if (CheckHitKey(KEY_INPUT_H)) {
		m_speed.y -= MOVE_SPEED;
		IsMove = true;
	}

	if (IsMove) {
		VECTOR Vec = m_speed;
		MATRIX Mat1, Mat2;
		Mat1 = MGetTranslate(Vec);
		Mat2 = MGetRotY(m_CameraRot.y);
		Mat1 = MMult(Mat1, Mat2);
		Vec = VGet(Mat1.m[3][0], Mat1.m[3][1], Mat1.m[3][2]);

		m_pos = VAdd(m_pos, Vec);
		m_rot.y = atan2f(Vec.x, Vec.z);
	}

	//m_speed.x = sinf(m_rot.y) * fSpd;
	//m_speed.z = cosf(m_rot.y) * fSpd;
	// 計算した速度を座標に足し算する
	//m_pos = VAdd(m_pos, m_speed);


}


//---------------------
//更新したデータを反映させる
//---------------------
void Player::Update()
{
	MV1SetRotationXYZ(m_hndl, m_rot);
	MV1SetScale(m_hndl, m_scale);
	MV1SetPosition(m_hndl, m_pos);
}

//---------------------
//描画処理
//---------------------
void Player::Draw()
{
	if (m_isActive == true)
		MV1DrawModel(m_hndl);


#ifdef DEBUG
	//当たり判定を目視できる
	DrawSphere3D(GetCenter(), m_radius, 3, GetColor(0, 0, 255),
		GetColor(0, 0, 255), false);
	DrawFormatString(20, 20, GetColor(255, 255, 0), "P_pos.x:%.2f", m_pos.x);
	DrawFormatString(20, 40, GetColor(255, 255, 0), "P_pos.y:%.2f", m_pos.y);
	DrawFormatString(20, 60, GetColor(255, 255, 0), "P_pos.z:%.2f", m_pos.z
	);
#endif // DEBUG

}

VECTOR Player::GetCenter()
{
	//基本は物体の球の判定の位置
	VECTOR res = m_pos;
	//高さだけ足元から玉の半径分上げる
	res.y += m_radius;

	return res;
}

void Player::HitCalc()
{
	//生存フラグを消す
	m_isActive = false;
}
