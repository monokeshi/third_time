#pragma once

class FrameRate
{
private:
	static long long baseTime;		// 基準となる時刻
	static long long fpsBaseTime;	// 基準となる時刻(fps用)
	static float fps;				// FPS

	FrameRate();
public:
	// 初期化処理
	static void Initialize();

	// FPSを計算
	static void CalcFPS();

	// FPSを表示
	static void DrawFPS();
};