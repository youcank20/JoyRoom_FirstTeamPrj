#pragma once
#include "Monster.h"

class Gengar : public Monster
{
public:
	Gengar(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};