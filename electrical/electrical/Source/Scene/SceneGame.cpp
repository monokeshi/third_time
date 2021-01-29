#include "DxLib.h"
#include "SceneGame.h"
#include "../Define/Define.h"
#include "../Utility/Utility.h"
#include "../Input/InputManager.h"
#include "../Background/Background.h"
#include "../Resource/Sound_BGM.h"
#include "../Resource/Sound_SE.h"

// コンストラクタ
SceneGame::SceneGame()
{
	// キャラクター
	characters = new Chara_Manager;

	// ステージ
	stage = new Stage;

	// エフェクト
	effects = new EffectManager;

	// UI
	ui = new UI_Manager;

	scrollX = 0;
	scrollY = 0;
	screenX = 0;
	screenY = 0;
	isScroll = false;
	isDrawUIMM = false;

	r = g = b = 255.0f;
	h = s = v = 255.0f;
}

// デストラクタ
SceneGame::~SceneGame()
{
	delete characters;
	delete stage;
	delete effects;
	delete ui;
}

// 初期化処理
void SceneGame::Initialize()
{
	// ステージ
	if ( !stage->Initialize() )
	{
		isGameEnd = true;
	}

	// キャラクター
	if ( !characters->Initialize() )
	{
		isGameEnd = true;
	}

	isSceneChange = false;
}

// スクリーン座標を求める
void SceneGame::Screen()
{
	screenX = scrollX + WIN_WIDTH / 2;
	screenY = scrollY + WIN_HEIGHT / 2;
}

// エフェクト管理
void SceneGame::MyEffectManager()
{
	// キャラクターの死亡エフェクト
	if ( characters->GetIsCharaDeath() )
	{
		// シェイク
		effects->Shake();

		// 爆発
		effects->Explosion(characters->GetExplosionPosX(),
						   characters->GetExplosionPosY());
	}

	// クリア時のエフェクト
	if ( characters->GetPlayerIsGoal() )
	{
		effects->Clear(characters->GetPlayerX(), characters->GetPlayerY());
	}

	// エフェクト
	effects->Update();
}

// UI管理
void SceneGame::MyUIManager()
{
	// 更新処理
	ui->Update(characters->GetPlayerHp(), characters->GetPlayerMaxHp(),
			   characters->GetPlayerBattery(), characters->GetPlayerMaxBattery(), isDrawUIMM);

	// 操作一覧表示中でない
	if ( !isDrawUIMM )
	{
		h = 0.0f;
		s = 0.0f;
		v = 255.0f;
	}
	// 操作一覧表示中
	else
	{
		h = 0.0f;
		s = 0.0f;
		v = 64.0f;
	}

	//  READYの場合は処理を行わない
	if ( ui->GetIsReady() )
	{
		return;
	}

	// ヘルプ(操作一覧を表示)
	if ( !isDrawUIMM &&
		InputManager::IsInputTrigger(e_HELP) )
	{
		// SE再生
		Sound_SE::GetInstance()->PlaySE(e_OPEN_HELP_SE, false);
		isDrawUIMM = true;
		return;
	}

	// ヘルプを閉じる
	if ( isDrawUIMM &&
		InputManager::IsInputTrigger(e_HELP) )
	{
		// SE再生
		Sound_SE::GetInstance()->PlaySE(e_OPEN_HELP_SE, false);
		isDrawUIMM = false;
		return;
	}
}

// シーン遷移
void SceneGame::SceneChange(bool isSCPossible)
{
	// シーン遷移が可能
	if ( !isSCPossible )
	{
		return;
	}

	// プレイヤーが死亡→初期化処理
	if ( !characters->GetPlayerIsAlive() )
	{
		// BGM停止
		Sound_BGM::GetInstance()->StopBGM(e_GAME_BGM);
		nextScene = e_GAME;
		isSceneChange = true;
		return;
	}

	// プレイヤーがゴール→エンディング
	if ( characters->GetPlayerIsGoal() )
	{
		// 一定時間経過
		static int timer = 0;
		if ( timer++ < 30 )
		{
			return;
		}

		timer = 0;
		// BGM停止
		Sound_BGM::GetInstance()->StopBGM(e_GAME_BGM);

		// すべてのSE停止
		if ( !isSceneChange )
		{
			Sound_SE::GetInstance()->StopAllSE();
		}

		// SE(ジングル)再生
		Sound_SE::GetInstance()->PlaySE(e_STAGE_CLEAR_SE, true);
		nextScene = e_ENDING;
		isSceneChange = true;
		return;
	}
}

// ゲーム終了
void SceneGame::GameEnd()
{
	if ( InputManager::IsInputRelease(e_EXIT) )
	{
		isGameEnd = true;
	}
}

// 更新処理
void SceneGame::Update(bool isSCPossible)
{
	// BGM再生
	if ( !isSceneChange )
	{
		Sound_BGM::GetInstance()->PlayBGM(e_GAME_BGM);
	}

	// スクリーン座標を求める
	Screen();

	// 操作一覧表示中は更新処理を行わない
	if ( !isDrawUIMM )
	{
		// SE再生
		if ( isScroll )
		{
			Sound_SE::GetInstance()->PlaySE(e_SCROLL_SE, true);
		}

		// スクロール
		Utility::Scroll((int)characters->GetScrollCenterX(),
						(int)characters->GetScrollCenterY(),
						&scrollX, &scrollY, &isScroll);

		// エフェクト
		MyEffectManager();

		// スクロール中またはREADYの場合は更新処理を行わない
		if ( !isScroll && !ui->GetIsReady() )
		{
			// キャラクター
			characters->Update(screenX, screenY);
		}
	}

	// UI
	MyUIManager();

	// HSVからRGBへ変換
	Utility::ConvertHSVtoRGB(&r, &g, &b, h, s, v);

	// シーン遷移
	SceneChange(isSCPossible);

	// ゲーム終了
	GameEnd();
}

// 描画処理
void SceneGame::Draw()
{
	SetDrawBright((int)r, (int)g, (int)b);
	// 背景
	Background back;
	back.Draw(effects->GetShakeX(), effects->GetShakeY());

	// ステージ
	stage->Draw(effects->GetShakeX(),
				effects->GetShakeY(),
				scrollX, scrollY, screenX, screenY);

	// キャラクター
	characters->Draw(effects->GetShakeX(),
					 effects->GetShakeY(), scrollX, scrollY);

	// エフェクト
	effects->Draw(scrollX, scrollY);

	// UI
	ui->Draw(characters->GetPlayerHp(), characters->GetPlayerMaxHp(),
			 characters->GetPlayerBattery(), characters->GetPlayerMaxBattery(), isDrawUIMM);

	SetDrawBright(255, 255, 255);
}

// 終了処理
void SceneGame::Finalize()
{

}