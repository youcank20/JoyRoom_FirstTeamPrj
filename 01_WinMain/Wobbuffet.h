#pragma once
#include "Monster.h"

class Wobbuffet : public Monster // ¸¶ÀÚ¿ë
{
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};