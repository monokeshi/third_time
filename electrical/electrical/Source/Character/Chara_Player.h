#pragma once

#include <vector>
#include "CharaBase.h"
#include "Weapon/Weapon_ElectricGun.h"

enum PlayerState
{
	e_P_STATE_IDLE,					// 待機
	e_P_STATE_CHARGE,				// 充電
	e_P_STATE_WALK,					// 歩き
	e_P_STATE_DASH,					// ダッシュ
	e_P_STATE_JUMP,					// ジャンプ
	e_P_STATE_STOP_ATTACK,			// とまって攻撃
	e_P_STATE_WALK_ATTACK,			// 歩き攻撃
	e_P_STATE_DASH_ATTACK,			// ダッシュ攻撃
	e_P_STATE_JUMP_ATTACK,			// ジャンプ攻撃
	e_P_STATE_RECIEVE_DAMAGE,		// ダメージを受ける
	e_P_STATE_BATTERY_ZERO,			// バッテリーゼロ
	e_P_STATE_GOAL,					// ゴール
	e_P_STATE_NUM
};

extern const int P_WIDTH;						// 横幅
extern const int P_HEIGHT;						// 縦幅
extern const float P_NORMAL_SPEED;				// 通常スピード
extern const float P_DASH_SPEED;				// ダッシュスピード
extern const float P_JUMP_POWER;				// ジャンプ力
extern const int BATTERY_DCREASE_TIME;			// バッテリー減少タイム
extern const int BATTERY_CHARGE_TIME;			// バッテリーチャージタイム
extern const int P_MAX_HP;						// 最大HP
extern const int P_MAX_BATTERY;					// 最大バッテリー
extern const int P_CONSUMPTION_BULLET_NUM;		// 電力を消費する弾数
extern const int P_MOTION[e_P_STATE_NUM][4];	// モーション

class Chara_Player:public CharaBase
{
private:
	std::vector<Weapon_ElectricGun *> electricGun;

	int padInputX, padInputY;	// パッドレバーの入力量(キーボードの矢印キーの入力量も取得できる)
	int battery;				// バッテリー
	int batteryTimer;			// バッテリー減少タイマー
	int batteryChargeTimer;		// バッテリーチャージタイマー
	int shotBulletNum;			// 撃った弾数

	bool isBatteryZero;			// バッテリーゼロフラグ
	int attackMotionFrame;		// 攻撃モーションフレーム

	// バッテリーボックス
	typedef struct
	{
		float boxPosLeft;	// バッテリーの左座標
		float boxPosRight;	// バッテリーの右座標
		float boxPosTop;	// バッテリーの上座標
		float boxPosBottom;	// バッテリーの下座標
		float r;			// 赤色				:0~255
		float g;			// 緑色				:0~255
		float b;			// 青色				:0~255
		float h;			// 色相(hue)			:0~360
		float s;			// 彩度(saturation)	:0~255
		float v;			// 明度(value)		:0~255
	} BatteryBox;

	BatteryBox batteryBox;

	// 初期の画像の向き
	bool InitGraphDirection();

	// 移動入力があるかの判定
	bool IsInputMove();

	// ダッシュの判定
	bool IsDash();

	// ダッシュなどの判定からスピードを取得
	float GetNowSpeed();

	// 向き固定時の処理
	void Fixed();

	// 入力での移動
	void InputMove();

	// 移動
	void Move();

	// 画像の向きを変更
	void ChangeGraphicDirection();

	// バッテリー減少
	void BatteryDecrease();

	// バッテリチャージを行わない場合
	void NotBatteryChage();

	// バッテリーチャージ
	void BatteryCharge();

	// バッテリーゼロ
	void BatteryZero();

	// バッテリー管理
	void BatteryManager();

	// 攻撃
	bool IsAttack();

	// 武器処理管理
	void WeaponManager();

	// 攻撃モーション
	void AttackMotion();

	// ゴールに入っているかの判定
	bool IsGoal();

	// 状態
	void State();

	// バッテリーボックスの初期化処理
	void InitBatteryBox();

	// バッテリーボックスの更新処理
	void UpdateBatteryBox();

	// バッテリーボックスの描画処理
	void DrawBatteryBox(float shakeX, float shakeY, int scrollX, int scrollY);

public:
	Chara_Player(float x, float y, int radius, int width, int height,
				 float speed, int hp, int attackPower);
	~Chara_Player();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// スポーン
	void Spawn(float x, float y);

	// 攻撃ヒット
	void HitAttack(int index);

	// 電気銃の要素数
	unsigned int GetGunSize();

	// 電気銃のX座標を取得
	float GetGunPosX(int index);

	// 電気銃のY座標を取得
	float GetGunPosY(int index);

	// 電気銃のradiusを取得
	int GetGunRadius(int index);

	// 電気銃のisLeftWardを取得
	bool GetIsGunLeftWard(int index);

	// HPを取得
	int GetHp();

	// バッテリーを取得
	int GetBattery();

	// ゴール判定を取得
	bool GetIsGoal();

	// moveXを取得
	float GetMoveX();

	// moveYを取得
	float GetMoveY();
};