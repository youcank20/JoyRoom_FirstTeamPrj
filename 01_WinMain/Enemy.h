#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
	class UIBossHP* mHPText;
	int mHP;
public:
	Enemy(float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void TakeDamage(int damage);
};

