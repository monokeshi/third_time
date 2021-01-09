#pragma once

#include <vector>

class EffectManager
{
private:
	//std::vector<Effect_Explosion *>explosion;

	float shakeX, shakeY;
	float shakeAddX, shakeAddY;

	int particleGH;

public:
	EffectManager(int particleGH);
	~EffectManager();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

	// shakeX���擾
	float GetShakeX();

	// shakeY���擾
	float GetShakeY();

	// �V�F�C�N
	void Shake();

	// ����
	void Explosion(float x, float y);
};