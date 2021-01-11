#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/WaterBullet.h"

const int E_WATER_WIDTH = 50;			// ก
const int E_WATER_HEIGHT = 50;			// c

extern const int BULLET_INTERVAL;

class Chara_EnemyWater :public Chara_EnemyBase
{
private:
	std::vector<WaterBullet *> waterBullet;

	int bulletInterval;		// e๐ยิu
	float bulletSpeed;		// eฬXs[h

	// ฺฎ
	void Move();

public:
	Chara_EnemyWater(float x, float y, int radius, int width, int height,
		float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyWater();

	// ๚ป
	void Initialize();

	// XV
	void Update(float playerX, float playerY);

	// `ๆ
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// Uqbg
	void HitAttack(int index);

	// ํว
	void WeaponManager(float playerX, float playerY, bool isPlayerAlive, int electricGunGH);

	// eฬvf
	unsigned int GetGunSize();

	// eฬXภWๆพ
	float GetGunPosX(int index);

	// eฬYภWๆพ
	float GetGunPosY(int index);

	// eฬradiusๆพ
	int GetGunRadius(int index);
};