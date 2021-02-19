#include "pch.h"
#include "Monster.h"

Monster::Monster(const string & name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Monster::Init()
{
}

void Monster::Release()
{
}

void Monster::Update()
{
}

void Monster::Render(HDC hdc)
{
}