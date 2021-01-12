#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/Weapon_WaterGun.h"

const int E_WATER_WIDTH = 50;			// ¡
const int E_WATER_HEIGHT = 50;			// c

extern const int BULLET_INTERVAL;

class Chara_EnemyWater :public Chara_EnemyBase
{
private:
	std::vector<Weapon_WaterGun *> waterGun;

	int bulletInterval;		// eðÂÔu
	float bulletSpeed;		// eÌXs[h

	// Ú®
	void Move();

	// ü«ðÏX
	void ChangeDirection(float playerX);

public:
	Chara_EnemyWater(float x, float y, int radius, int width, int height,
		float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyWater();

	// ú»
	void Initialize();

	// XV
	void Update(float playerX, float playerY);

	// `æ
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// Uqbg
	void HitAttack(int index);

	// íÇ
	void WeaponManager(float playerX, float playerY, bool isPlayerAlive, int electricGunGH);

	// eÌvf
	unsigned int GetGunSize();

	// eÌXÀWæ¾
	float GetGunPosX(int index);

	// eÌYÀWæ¾
	float GetGunPosY(int index);

	// eÌradiusæ¾
	int GetGunRadius(int index);

	// eÌisLeftWardæ¾
	bool GetIsGunLeftWard(int index);
};