#pragma once

class Effect_Explosion
{
private:
	float x;
	float y;

public:
	Effect_Explosion(float x, float y);

	// 更新処理
	void Update();

	// 描画処理
	void Draw();
};