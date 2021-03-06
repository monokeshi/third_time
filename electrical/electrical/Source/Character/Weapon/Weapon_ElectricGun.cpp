#include "DxLib.h"
#include "Weapon_ElectricGun.h"
#include "../../Define/Define.h"
#include "../../Utility/Utility.h"
#include "../../Resource/Graphic.h"
#include "../../Resource/Sound_SE.h"

const float EG_SPEED = 10.0f;

Weapon_ElectricGun::Weapon_ElectricGun(float x, float y, int radius, float speedX, float speedY,
									   float flightDistance, int eraseFrame, bool isCharaLeft):
	WeaponBase(x, y, radius, speedX, speedY, flightDistance, eraseFrame, isCharaLeft)
{
	exRate = 0.75;

	// SE再生
	Sound_SE::GetInstance()->PlaySE(e_SHOT_ELECTRIC_GUN_SE, false);
}

// 移動
void Weapon_ElectricGun::Move()
{
	// 移動量初期化
	moveX = 0.0f;
	moveY = 0.0f;

	// 左向き
	if ( isLeft )
	{
		moveX -= speedX;
	}
	// 右向き
	else
	{
		moveX += speedX;
	}

	moveY += speedY;

	flightDistance -= fabsf(moveX);

	BulletMove(true);
}

// 消去
void Weapon_ElectricGun::Erase()
{
	// 画面外に出たら消去
	if ( x + radius < 0 ||
		x - radius > MAP_COUNT_X * CHIP_SIZE )
	{
		isAlive = false;
	}

	// マップに当たったら消去
	if ( isMapHit )
	{
		isAlive = false;
	}

	// 飛距離
	if ( flightDistance <= 0.0f )
	{
		exRate -= 0.05f;
		// 小さくなったら消去
		if ( exRate < 0.0f )
		{
			isAlive = false;
		}
	}
}

// 更新処理
void Weapon_ElectricGun::Update()
{
	Move();
	Erase();
}

// 描画処理
void Weapon_ElectricGun::Draw(int scrollX, int scrollY,
							  int displaceX, int displaceY)
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x - scrollX + displaceX,
					  (int)y - scrollY + displaceY,
					  exRate, 0.0, Graphic::GetInstance()->GetElectricGun(), true, isLeft);
	}
}