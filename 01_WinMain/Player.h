#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

