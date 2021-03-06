#pragma once

#include "WeaponBase.h"

extern const float WG_GRAVITY;

class Weapon_WaterGun:public WeaponBase
{
private:
	// 移動
	void Move();

	// 消去
	void Erase();

public:
	Weapon_WaterGun(float x, float y, int radius, float speedX, float speedY,
					float flightDistance, int eraseFrame, bool isCharaLeft);

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int scrollX, int scrollY, 
			  int displaceX, int displaceY);
};