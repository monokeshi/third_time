#include "DxLib.h"
#include "Chara_EnemyAbsorption.h"
#include "../Define/Define.h"

Chara_EnemyAbsorption::Chara_EnemyAbsorption(float x, float y, int radius,
											 float speed, int hp, int attackPower, int graphHandle):
	CharaEnemyBase(x, y, radius, speed, hp, attackPower, graphHandle)
{

}

Chara_EnemyAbsorption::~Chara_EnemyAbsorption()
{

}

// ����������
void Chara_EnemyAbsorption::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;
}

// �ړ�
void Chara_EnemyAbsorption::Move()
{
	moveX = 0.0f;
	moveY = 0.0f;

	// �e�X�g�p
	{
		if ( x - radius < 0 || x + radius > WIN_WIDTH )
		{
			speed *= -1;
		}

		moveX += speed;
	}

	CharaMove();
}

// �X�V����
void Chara_EnemyAbsorption::Update()
{
	if ( isAlive )
	{
		Move();
		ChangeGraphicDirection();
		HpZero();
	}
}

// �`�揈��
void Chara_EnemyAbsorption::Draw()
{
	if ( isAlive )
	{
		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}
}