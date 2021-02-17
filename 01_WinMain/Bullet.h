#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
	float mAngle;
	float mSpeed;
public:
	Bullet();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Fire(float x, float y, float angle, float speed);
};

