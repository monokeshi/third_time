#pragma once

#include <vector>
#include "Chara_EnemyBase.h"
#include "Weapon/ElectricGun.h"

const int E_GUN_WIDTH = 50;				// ก
const int E_GUN_HEIGHT = 50;			// c
const float E_GUN_NORMAL_SPEED = 2.0f;	// สํXs[h
const float E_GUN_DASH_SPEED = 4.0f;	// _bVXs[h

const int BULLET_INTERVAL = 70;

class Chara_EnemyGun:public Chara_EnemyBase
{
private:
	std::vector<ElectricGun *> electricGun;

	int shotBulletNum;		// มฝe
	int bulletInterval;		// e๐ยิu
	bool isTargetLock;		// ออเฬtO


	// ฺฎ
	void Move(float playerX, float playerY, bool isPlayerAlive);

public:
	Chara_EnemyGun(float x, float y, int radius, int width, int height,
				   float speed, int hp, int attackPower, int graphHandle);
	~Chara_EnemyGun();

	// ๚ป
	void Initialize();

	// XV
	void Update(float playerX, float playerY, bool isPlayerAlive);

	// `ๆ
	void Draw(float shakeX, float shakeY, int scrollX, int scrollY);

	// ํว
	void WeaponManager(int electricGunGH);

	// Uqbg
	void HitAttack(int index);

	// dCeฬvf
	unsigned int GetGunSize();

	// dCeฬXภWๆพ
	float GetGunPosX(int index);

	// dCeฬYภWๆพ
	float GetGunPosY(int index);

	// dCeฬradiusๆพ
	int GetGunRadius(int index);
};