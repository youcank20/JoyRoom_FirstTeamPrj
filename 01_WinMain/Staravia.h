#pragma once
#include "Monster.h"

class Staravia : public Monster // Âî¸£¹öµå
{
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};