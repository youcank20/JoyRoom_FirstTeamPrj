#pragma once
#include "Monster.h"

class Charmeleon : public Monster
{
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};