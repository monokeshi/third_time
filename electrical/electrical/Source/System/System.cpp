#include "DxLib.h"
#include <time.h>
#include "System.h"
#include "SettingDxLib.h"
#include "../Mask/Mask.h"

// コンストラクタ
System::System()
{
	gameMain = nullptr;
}

// デストラクタ
System::~System()
{
	delete gameMain;
}

// 初期化処理
bool System::Initialize()
{
	// DXLibの初期化
	if ( !SettingDxLib::DxLibInit() )
	{
		return false;
	}

	// シード値
	srand((unsigned)time(nullptr));

	// インスタンス生成
	gameMain = new GameMain;

	// メインゲーム
	gameMain->Initialize();

	// マスクセット
	Mask::SetMask();

	return true;
}

// メインループ
bool System::MainLoop()
{
	// ゲームループ
	while ( true )
	{
		/* ----- 更新処理 ----- */
		// メインゲーム
		gameMain->Update();

		/* ----- 描画処理 ----- */
		// マスクの描画
		Mask::DrawMask();

		// メインゲーム
		gameMain->Draw();

		// マスクの後処理
		Mask::LoopMask();

		// DxLibのループ処理
		if ( !SettingDxLib::DxLibGameLoop() )
		{
			return false;
		}
	}

	return true;
}

// 終了処理
void System::Finalize()
{
	// Dxライブラリ終了処理
	DxLib_End();
}

// メイン処理
bool System::Main()
{
	// 初期化処理
	if ( !Initialize() )
	{
		return false;
	}

	// メインループ処理を行う
	if ( !MainLoop() )
	{
		return false;
	}

	// 終了処理
	Finalize();

	return true;
}