#pragma once
#include "Monster.h"

class Player;

class Gengar : public Monster
{
public:
	Gengar(const string& name, float x, float y, Player* player);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};