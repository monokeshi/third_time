#pragma once

#include <vector>
#include "Chara_Player.h"
#include "Chara_EnemyBase.h"
#include "../Define/Define.h"

enum CharaSpawnInfo
{
	e_CharaPlayer,				// プレイヤー
	e_CharaEnemyBomb,			// ボム兵
	e_CharaEnemyElectric,		// 電気銃エネミー
	e_CharaEnemyWater,			// 水銃エネミー
	e_CharaPlayer_ChecKPoint	// プレイヤーチェックポイント
};

class Chara_Manager
{
private:
	Chara_Player *player;
	std::vector<Chara_EnemyBase *>enemys;

	int spawnData[MAP_COUNT_Y][MAP_COUNT_X];		// スポーンデータ
	bool isEnemySpawn[MAP_COUNT_Y][MAP_COUNT_X];	// エネミースポーンフラグ
	bool isPassCheckPoint;							// チェックポイント通過フラグ
	int displaceX;									// スクリーンの中心に描画するためにずらす量
	int displaceY;									// スクリーンの中心に描画するためにずらす量
	float explosionX;								// 爆発の中心となる座標
	float explosionY;								// 爆発の中心となる座標

	// ファイル読み込み
	bool LoadFile();

	// プレイヤーのスポーン
	void PlayerSpawn();

	// エネミーの生成
	void EnemyGenerate(int screenX, int screenY);

	// エネミー管理
	void EnemyManager(int screenX, int screenY);

	// キャラクタ同士の当たり判定
	void CharaCollision();

	// 攻撃の当たり判定
	void AttackCollision();

	// チェックポイントの通過判定
	void PassCheckPoint();

public:
	Chara_Manager();
	~Chara_Manager();

	// 初期化処理
	bool Initialize();

	// 更新処理
	void Update(int screenX, int screenY);

	// 描画処理
	void Draw(float shakeX, float shakeY,
			  int scrollX, int scrollY);

	// displaceXを設定
	void SetDisplaceX(int displaceX);

	// displaceYを設定
	void SetDisplaceY(int displaceY);

	// スクロールの中心座標を取得
	float GetScrollCenterX();
	float GetScrollCenterY();

	// 爆発の中心となるX座標を取得
	float GetExplosionPosX();

	// 爆発の中心となるY座標を取得
	float GetExplosionPosY();

	// キャラクターの死亡を取得
	bool GetIsCharaDeath();

	// プレイヤーの中心X座標を取得
	float GetPlayerX();

	// プレイヤーの中心Y座標を取得
	float GetPlayerY();

	// プレイヤーのmoveXを取得
	float GetPlayerMoveX();

	// プレイヤーのmoveYを取得
	float GetPlayerMoveY();

	// プレイヤーのHPを取得
	int GetPlayerHp();

	// プレイヤーの最大HPを取得
	int GetPlayerMaxHp();

	// プレイヤーの最大バッテリーを取得
	int GetPlayerBattery();

	// プレイヤーのバッテリーを取得
	int GetPlayerMaxBattery();

	// プレイヤーisAliveを取得
	bool GetPlayerIsAlive();

	// プレイヤーのゴールフラグを取得
	bool GetPlayerIsGoal();
};