#include <math.h>
#include "Chara_EnemyBase.h"
#include"../stage/stage.h"

Chara_EnemyBase::Chara_EnemyBase(float x, float y, int radius,
								 float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{
}

// 画像の向きを変化
void Chara_EnemyBase::ChangeGraphicDirection()
{
	// 左に進行
	if ( x - oldX < 0.0f )
	{
		isLeftWard = true;
	}
	// 右に進攻
	else if ( x - oldX > 0.0f )
	{
		isLeftWard = false;
	}
}

// シェイクスタート
void Chara_EnemyBase::ShakeStart(float *shakeAddX, float *shakeAddY)
{
	if ( hp <= 0 )
	{
		*shakeAddX = *shakeAddY = 4.0f;
	}
}

// ブロックが間にあるか探す
bool Chara_EnemyBase::IsBlock(float playerX)
{
	// 敵とプレイヤーの間のブロック数
	int enemySpace = (int)fabsf(x - playerX) / CHIP_SIZE;

	// プレイヤーとの間にブロックがあるか
	for ( int i = 1; i <= enemySpace; i++ )
	{
		// 左向きの時
		if ( isLeftWard )
		{
			if ( Stage::GetMapParam(x - (float)(CHIP_SIZE * i), y) == e_MAP_BLOCK )
			{
				return true;
			}
		}
		// 右向きの時
		else
		{
			if ( Stage::GetMapParam(x + (float)(CHIP_SIZE * i), y) == e_MAP_BLOCK )
			{
				return true;
			}
		}
	}

	return false;
}

// 敵同士の当たり判定
void Chara_EnemyBase::EnemiesCollision()
{

}