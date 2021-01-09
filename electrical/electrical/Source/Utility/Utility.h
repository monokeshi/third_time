#pragma once

const float SHAKE_DECREASE = 0.3f;	// 振動の減少量

// マップチップの当たり判定
enum MapHit
{
	e_HIT_NOT,
	e_HIT_LEFT,
	e_HIT_RIGHT,
	e_HIT_TOP,
	e_HIT_BOTTOM
};

class Utility
{
private:
	Utility();

public:
	// 画面内にとどまる
	static void StayOnScreen(float *x, float *y, int radius,
							 bool isStayX, bool isStayY);

	//マップとの当たり判定
	// 1：左辺、2：右辺、3：上辺、4：下辺
	static int MapHitCheck(float x, float y, float *moveX, float *moveY);

	// 円のコリジョン
	static bool IsCircleCollision(float x1, float y1, int r1,
								  float x2, float y2, int r2);

	// 矩形のコリジョン
	static bool IsRectCollision(float x1, float y1, int w1, int h1,
								float x2, float y2, int w2, int h2);

	// スクロール
	static void Scroll(int centerX, int centerY,
					   int *scrollX, int *scrollY);

	// HSVからRGBに変換
	static void ConvertHSVtoRGB(float *r, float *g, float *b,
								float h, float s, float v);
};