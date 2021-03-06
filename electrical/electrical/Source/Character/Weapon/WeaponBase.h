#pragma once

class WeaponBase
{
protected:
	float x;				// 中心座標
	float y;				// 中心座標
	float oldX;				// 1フレーム前の中心座標
	float oldY;				// 1フレーム前の中心座標
	float moveX;			// 移動量
	float moveY;			// 移動量
	int radius;				// 半径
	float speedX;			// スピードX
	float speedY;			// スピードY
	float flightDistance;	// 飛距離
	int mapHitFrame;		// マップチップにヒットしているフレーム数
	int eraseFrame;			// マップチップにヒットしてから消去するフレーム数
	bool isAlive;			// 発射フラグ
	bool isMapHit;			// マップヒットフラグ
	bool isLeft;			// 左向きフラグ

	// マップチップとの当たり判定を考慮した移動
	void BulletMove(bool isHitCalc);

public:
	WeaponBase(float x, float y, int radius, float speedX, float speedY,
			   float flightDistance, int eraseFrame, bool isCharaLeft);


	// 弾がヒットした場合の処理
	void Hit();

	// X座標を取得
	float GetPosX();

	// Y座標を取得
	float GetPosY();

	// 半径を取得
	int GetRadius();

	// isAliveを取得
	bool GetIsAlive();

	// isLeftを取得
	bool GetIsLeft();
};