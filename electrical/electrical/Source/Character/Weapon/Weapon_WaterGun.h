#pragma once

#include "WeaponBase.h"

const float WG_GRAVITY = 0.85f;

class Weapon_WaterGun:public WeaponBase
{
private:
	// 移動
	void Move();

	// 消去
	void Erase();

public:
	Weapon_WaterGun(float x, float y, int radius, float speedX, float speedY,
					int eraseFrame, bool isCharaLeftWard, int graphHandle);

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int scrollX, int scrollY);
};