#include "pch.h"
#include "Monster.h"

Monster::Monster(const string & name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;

	mAttacked = false;
	mDieAlpha = 1.f;
	mPrevIndex = 0;
	mAttackWait = false;
	mAttackWaitTime = 0.f;
	mHurtTime = 0.f;
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