#pragma once

#include "WeaponBase.h"

extern const float EG_SPEED;

class Weapon_ElectricGun:public WeaponBase
{
private:
	double exRate;	// 拡大率

	// 移動
	void Move();

	// 消去
	void Erase();

public:
	Weapon_ElectricGun(float x, float y, int radius, float speedX, float speedY,
					   float flightDistance, int eraseFrame, bool isCharaLeft);

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int scrollX, int scrollY, 
			  int displaceX, int displaceY);
};