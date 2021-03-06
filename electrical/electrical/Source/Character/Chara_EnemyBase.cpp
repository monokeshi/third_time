#include <math.h>
#include "Chara_EnemyBase.h"
#include"../stage/stage.h"
#include "../Resource/Graphic.h"
#include "../Define/Define.h"

const float E_JUMP_POWER = -13.0f;

Chara_EnemyBase::Chara_EnemyBase(float x, float y, int radius, int width, int height,
								 float speed, int hp, int attackPower, int mapChipX, int mapChipY):
	CharaBase(x, y, radius, width, height, speed, hp, attackPower)
{
	this->mapChipX = mapChipX;
	this->mapChipY = mapChipY;
	attackX = 0.0f;
	attackY = 0.0f;
	attackRadius = 0;
	isAttackLeft = isLeft;
}

// ジャンプする
void Chara_EnemyBase::Jump()
{
	if ( x != oldX )
	{
		return;
	}

	// 目の前に縦1ブロックがあるかつ真上にブロックがない場合のみジャンプする
	if ( Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_NONE &&
		((Stage::GetMapParam(x + width + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x + width + 1, y - CHIP_SIZE) == e_MAP_NONE) ||
		 (Stage::GetMapParam(x - width - 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x - width - 1, y - CHIP_SIZE) == e_MAP_NONE)) )
	{
		CharaJump(E_JUMP_POWER);
	}
}

// 進行方向を変える
void Chara_EnemyBase::ChangeDirection(int screenX, int screenY)
{
	// スクリーンより端 この判定は優先して行われる
	// 左
	if ( (int)x - width / 2 < screenX - WIN_WIDTH / 2 - displaceX + DISPLACE_X )
	{
		x = (float)(screenX - WIN_WIDTH / 2 - displaceX + DISPLACE_X + width / 2);
		speed *= -1.0f;
		return;
	}
	// 右
	else if ( (int)x + width / 2 > screenX + WIN_WIDTH / 2 - displaceX - DISPLACE_X )
	{
		x = (float)(screenX + WIN_WIDTH / 2 - displaceX - DISPLACE_X - width / 2);
		speed *= -1.0f;
		return;
	}

	// 動いていないまたはジャンプ、落下中の時
	if ( x != oldX || isJump || isFall )
	{
		return;
	}

	// 進む予定の位置に縦に2つ並んでブロックがある
	if ( (Stage::GetMapParam(x + width / 2 + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x + width / 2 + 1, y - CHIP_SIZE) == e_MAP_BLOCK) ||
		(Stage::GetMapParam(x - width / 2 - 1, y) == e_MAP_BLOCK &&
		 Stage::GetMapParam(x - width / 2 - 1, y - CHIP_SIZE) == e_MAP_BLOCK) )
	{
		speed *= -1.0f;
		return;
	}

	// 目の前に縦1ブロックがあるかつ真上にブロックがある
	if ( (Stage::GetMapParam(x + width / 2 + 1, y) == e_MAP_BLOCK &&
		  Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_BLOCK) ||
		(Stage::GetMapParam(x - width / 2 - 1, y) == e_MAP_BLOCK &&
		 Stage::GetMapParam(x, y - CHIP_SIZE) == e_MAP_BLOCK) )
	{
		speed *= -1.0f;
		return;
	}
}

// 画像の向きを変化
void Chara_EnemyBase::ChangeGraphicDirection()
{
	if ( x == oldX )
	{
		return;
	}

	// 左に進行で右向きの場合
	if ( !isLeft )
	{
		if ( speed < 0.0f )
		{
			// 左を向く
			isLeft = true;
		}
	}
	// 右に進行で左向きの場合
	else
	{
		if ( speed > 0.0f )
		{
			// 右を向く
			isLeft = false;
		}
	}
}

// プレイヤーとの間にブロックがあるか探す
bool Chara_EnemyBase::IsBlock(float playerX)
{
	// 敵とプレイヤーの間のブロック数
	int enemySpace = (int)fabsf(x - playerX) / CHIP_SIZE;

	// プレイヤーとの間にブロックがあるか
	for ( int i = 1; i <= enemySpace; i++ )
	{
		// 左向きの時
		if ( x - playerX > 0 )
		{
			if ( Stage::GetMapParam(x - (float)(CHIP_SIZE * i), y) == e_MAP_BLOCK )
			{
				return true;
			}
		}
		// 右向きの時
		else if ( x - playerX < 0 )
		{
			if ( Stage::GetMapParam(x + (float)(CHIP_SIZE * i), y) == e_MAP_BLOCK )
			{
				return true;
			}
		}
	}

	return false;
}

int Chara_EnemyBase::GetMapChipX()
{
	return mapChipX;
}

int Chara_EnemyBase::GetMapChipY()
{
	return mapChipY;
}

float Chara_EnemyBase::GetAttackPosX()
{
	return attackX;
}

float Chara_EnemyBase::GetAttackPosY()
{
	return attackY;
}

int Chara_EnemyBase::GetAttackRadius()
{
	return attackRadius;
}

bool Chara_EnemyBase::GetIsAttackLeftWard()
{
	return isAttackLeft;
}