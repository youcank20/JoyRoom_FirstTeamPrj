#pragma once
#include "Monster.h"

class Wobbuffet : public Monster // ���ڿ�
{
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};