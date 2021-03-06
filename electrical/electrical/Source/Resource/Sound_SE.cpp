#include "DxLib.h"
#include "Sound_SE.h"

Sound_SE::Sound_SE()
{
	// 読み込み
	gameStart = MyLoadSoundMem("Resource/Sound/SE/game_start.mp3");
	playerJump = MyLoadSoundMem("Resource/Sound/SE/player_jump.wav");
	playerCharging = MyLoadSoundMem("Resource/Sound/SE/player_charging.mp3");
	shotElectricGun = MyLoadSoundMem("Resource/Sound/SE/shot_electric_gun.mp3");
	shotWaterGun = MyLoadSoundMem("Resource/Sound/SE/shot_water_gun.mp3");
	receiveDamage = MyLoadSoundMem("Resource/Sound/SE/receive_damage.mp3");
	death = MyLoadSoundMem("Resource/Sound/SE/death.mp3");
	openHelp = MyLoadSoundMem("Resource/Sound/SE/open_help.mp3");
	scroll = MyLoadSoundMem("Resource/Sound/SE/scroll.mp3");
	stageClear = MyLoadSoundMem("Resource/Sound/SE/stage_clear.mp3");

	// サウンドの音量を設定
	MyChangeVolumeSoundMem();
}

// サウンドの音量を設定
void Sound_SE::MyChangeVolumeSoundMem()
{
	for ( unsigned i = 0; i < SE.size(); i++ )
	{
		ChangeVolumeSoundMem((int)(255.0f * 60.0f / 100.0f), SE[i]);
	}

	ChangeVolumeSoundMem((int)(255.0f * 70.0f / 100.0f), gameStart);
	ChangeVolumeSoundMem((int)(255.0f * 40.0f / 100.0f), playerJump);
	ChangeVolumeSoundMem((int)(255.0f * 35.0f / 100.0f), shotElectricGun);
	ChangeVolumeSoundMem((int)(255.0f * 65.0f / 100.0f), shotWaterGun);
	ChangeVolumeSoundMem((int)(255.0f * 90.0f / 100.0f), receiveDamage);
}

// 今までロードしたSEを解放する
void Sound_SE::Release()
{
	for ( unsigned i = 0; i < SE.size(); i++ )
	{
		DeleteGraph(SE[i]);
	}

	SE.clear();
}

int Sound_SE::MyLoadSoundMem(const char *filename)
{
	int temp = LoadSoundMem(filename);
	SE.push_back(temp);

	return temp;
}

// サウンドの再生をチェック、再生
void Sound_SE::CheckAndPlay(int soundHandle, bool isCheckSound)
{
	if ( isCheckSound &&
		CheckSoundMem(soundHandle) )
	{
		return;
	}

	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
}

// サウンドの再生をチェック、停止
void Sound_SE::CheckAndStop(int soundHandle)
{
	if ( !CheckSoundMem(soundHandle) )
	{
		return;
	}

	StopSoundMem(soundHandle);
}

// SE再生
void Sound_SE::PlaySE(SE_Info se, bool isCheckSound)
{
	switch ( se )
	{
		case e_GAME_START_SE:
			// ゲームスタート
			CheckAndPlay(gameStart, isCheckSound);
			break;

		case e_PLAYER_JUMP_SE:
			// プレイヤーのジャンプ
			CheckAndPlay(playerJump, isCheckSound);
			break;

		case e_PLAYER_CHAGING_SE:
			// 充電中
			CheckAndPlay(playerCharging, isCheckSound);
			break;

		case e_SHOT_ELECTRIC_GUN_SE:
			// 電気銃を撃つ
			CheckAndPlay(shotElectricGun, isCheckSound);
			break;

		case e_SHOT_WATER_GUN_SE:
			// 水銃を撃つ
			CheckAndPlay(shotWaterGun, isCheckSound);
			break;

		case e_RECEIVE_DAMAGE_SE:
			// ダメージを受ける
			CheckAndPlay(receiveDamage, isCheckSound);
			break;

		case e_DEATH_SE:
			// 死亡
			CheckAndPlay(death, isCheckSound);
			break;

		case e_OPEN_HELP_SE:
			// ヘルプを開く
			CheckAndPlay(openHelp, isCheckSound);
			break;

		case e_SCROLL_SE:
			// スクロール
			CheckAndPlay(scroll, isCheckSound);
			break;

		case e_STAGE_CLEAR_SE:
			// ステージクリア
			CheckAndPlay(stageClear, isCheckSound);
			break;

		default:
			break;
	}
}

// SE停止
void Sound_SE::StopSE(SE_Info se)
{
	switch ( se )
	{
		case e_GAME_START_SE:
			// ゲームスタート
			CheckAndStop(gameStart);
			break;

		case e_PLAYER_JUMP_SE:
			// プレイヤーのジャンプ
			CheckAndStop(playerJump);
			break;

		case e_PLAYER_CHAGING_SE:
			// 充電中
			CheckAndStop(playerCharging);
			break;

		case e_SHOT_ELECTRIC_GUN_SE:
			// 電気銃を撃つ
			CheckAndStop(shotElectricGun);
			break;

		case e_SHOT_WATER_GUN_SE:
			// 水銃を撃つ
			CheckAndStop(shotWaterGun);
			break;

		case e_RECEIVE_DAMAGE_SE:
			// ダメージを受ける
			CheckAndStop(receiveDamage);
			break;

		case e_DEATH_SE:
			// 死亡
			CheckAndStop(death);
			break;

		case e_OPEN_HELP_SE:
			// ヘルプを開く
			CheckAndStop(openHelp);
			break;

		case e_SCROLL_SE:
			// スクロール
			CheckAndStop(scroll);
			break;

		case e_STAGE_CLEAR_SE:
			// ステージクリア
			CheckAndStop(stageClear);
			break;

		default:
			break;
	}
}

// すべてのSEを停止する
void Sound_SE::StopAllSE()
{
	for ( unsigned i = 0; i < SE.size(); i++ )
	{
		StopSoundMem(SE[i]);
	}
}