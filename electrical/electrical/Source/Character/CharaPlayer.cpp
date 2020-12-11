#include "DxLib.h"
#include "Chara_Player.h"
#include "../Define/Define.h"
#include "../Input/InputKey.h"
#include "../Input/InputPad.h"
#include "../Utility/Utility.h"

Chara_Player::Chara_Player(float x, float y, int radius,
						   float speed, int hp, int attackPower, int graphHandle):
	CharaBase(x, y, radius, speed, hp, attackPower, graphHandle)
{
	hpTimer = 0;
	chargeTimer = 0;
}

Chara_Player::~Chara_Player()
{

}

// 初期化処理
void Chara_Player::Initialize()
{
	moveX = 0.0f;
	moveY = 0.0f;

	gravity = 0.0f;

	hpTimer = 0;
	chargeTimer = 0;
}

// 移動
void Chara_Player::Move()
{
	// 移動量初期化
	moveX = 0.0f;
	moveY = 0.0f;

	// 方向キー/アナログスティックでの左右移動
	moveX += speed * (InputPad::inputX / 1000.0f);

	// それ以外での左右移動
	if ( InputPad::inputX == 0 &&
		InputPad::inputY == 0 )
	{
		// 左移動
		if ( InputKey::IsKeyInputNow(e_KEY_LEFT) ||
			InputPad::IsPadInputNow(e_PAD_LEFT) )
		{
			moveX += speed * (InputPad::inputX / 1000);
		}

		//右移動
		if ( InputKey::IsKeyInputNow(e_KEY_RIGHT) ||
			InputPad::IsPadInputNow(e_PAD_RIGHT) )
		{
			moveX += speed * (InputPad::inputX);
		}
	}

	// ダッシュ
	if (InputKey::IsKeyInputBarrage(e_KEY_LEFT)||
		InputKey::IsKeyInputBarrage(e_KEY_RIGHT)||
		InputPad::IsPadInputBarrage(e_PAD_LEFT) ||
		InputPad::IsPadInputBarrage(e_PAD_RIGHT) )
	{
		DrawString(300, 300, "DASH!", GetColor(255, 255, 255));
		speed = DASH_SPEED;
	}
	else if (!CheckHitKey(KEY_INPUT_LEFT) && 
			 !CheckHitKey(KEY_INPUT_RIGHT) &&
			 !GetJoypadInputState(PAD_INPUT_LEFT) &&
			 !GetJoypadInputState(PAD_INPUT_RIGHT))
	{
		speed = NORMAL_SPEED;
	}

	// ジャンプ
	if ( InputKey::IsKeyInputTrigger(e_KEY_JUMP) ||
		InputPad::IsPadInputTrigger(e_PAD_JUMP) )
	{
		// ジャンプ中でない
		if ( !isJump )
		{
			gravity = JUMP_POWER;
			isJump = true;
		}
	}

	CharaMove();

	// 画面内にとどまる(X方向についてのみ)
	Utility::StayOnScreen(&x, &y, radius, true, false);
}

// HP(バッテリー)減少
void Chara_Player::HpDcrease()
{
	hpTimer++;
	if ( hpTimer > HP_DCREASE_TIME )
	{
		// HP減少
		hp--;

		// タイマーリセット
		hpTimer = 0;
	}
}

// HP(バッテリー)チャージ
void Chara_Player::HpCharge()
{
	// 移動中でない
	if ( moveX == 0.0f && moveY == 0.0f && !isJump )
	{
		if ( InputKey::IsKeyInputNow(e_KEY_ATTACK) ||
			InputPad::IsPadInputNow(e_PAD_ATTACK) )
		{
			// 一定時間チャージでチャージ量が増加
			if ( chargeTimer < 60 * 3 )
			{
				chargeTimer++;
			}
			else if ( chargeTimer < 60 * 6 )
			{
				chargeTimer += 2;
			}
			else
			{
				chargeTimer += 3;
			}

			// HP上昇
			if ( chargeTimer % HP_CHARGE_TIME == 0 )
			{
				hp++;
			}

			// チャージ中はHPは減少しない
			hpTimer = 0;

			return;
		}
	}

	chargeTimer = 0;
}

// HP管理
void Chara_Player::HpManager()
{
	HpDcrease();
	HpCharge();
	HpZero();

	// HPは最大値を超えない
	if ( hp > PLAYER_MAX_HP )
	{
		hp = 100;
	}
}

// 攻撃
bool Chara_Player::IsAttack()
{
	if ( InputKey::IsKeyInputTrigger(e_KEY_ATTACK) ||
		InputPad::IsPadInputTrigger(e_PAD_ATTACK) )
	{
		return true;
	}

	return false;
}

// 更新処理
void Chara_Player::Update()
{
	if ( isAlive )
	{
		Move();
		HpManager();
		ChangeGraphicDirection();
	}
}

// 描画処理
void Chara_Player::Draw()
{
	// プレイヤー
	if ( isAlive )
	{
		DrawRotaGraph((int)x, (int)y, 1.0, 0.0, graphHandle, true, isLeftWard);
	}

	// デバッグ用
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Player_HP(battery):%d%", hp);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "inputPadX:%d%", InputPad::inputX);
}