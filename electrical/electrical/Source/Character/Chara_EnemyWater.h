#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/Weapon_WaterGun.h"

enum EnemyWaterState
{
	e_EW_STATE_IDLE,				// 待機
	e_EW_STATE_ATTACK,				// 攻撃
	e_EW_STATE_RECIEVE_DAMAGE,		// ダメージを受ける
	e_EW_STATE_NUM
};

extern const int EW_WIDTH;						// 横幅
extern const int EW_HEIGHT;						// 縦幅
extern const int EW_BULLET_INTERVAL;			// 間隔
extern const int EW_MOTION[e_EW_STATE_NUM][4];	// モーション

class Chara_EnemyWater:public Chara_EnemyBase
{
private:
	std::vector<Weapon_WaterGun *> waterGun;

	int bulletInterval;		// 銃を撃つ間隔
	float bulletSpeed;		// 銃のスピード

	// 移動
	void Move();

	// 向きを変更
	void ChangeDirection(float playerX);

	// 状態
	void State();

public:
	Chara_EnemyWater(float x, float y, int radius, int width, int height,
					 float speed, int hp, int attackPower);
	~Chara_EnemyWater();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update(float playerX, float playerY);

	// 描画処理
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// 攻撃ヒット
	void HitAttack(int index);

	// 武器処理管理
	void WeaponManager(float playerX, float playerY, bool isPlayerAlive);

	// 水弾の要素数
	unsigned int GetGunSize();

	// 水弾のX座標取得
	float GetGunPosX(int index);

	// 水弾のY座標取得
	float GetGunPosY(int index);

	// 水弾のradius取得
	int GetGunRadius(int index);

	// 水銃のisLeftWard取得
	bool GetIsGunLeftWard(int index);
};