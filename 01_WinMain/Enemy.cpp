#include "pch.h"
#include "Enemy.h"
#include "UIBossHP.h"

Enemy::Enemy(float x, float y)
	:GameObject("Enemey")
{
	mX = x;
	mY = y;
	mSizeX = 50;
	mSizeY = 50;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Enemy::Init()
{
	mHPText = 
		(UIBossHP*)ObjectManager::GetInstance()
		->FindObject(ObjectLayer::UI,"UIBossHP");
	mHP = 100;
	mHPText->SetText(to_wstring(mHP));
}

void Enemy::Release()
{
}

void Enemy::Update()
{
	
}

void Enemy::Render(HDC hdc)
{
	RenderRect(hdc, mRect);
}

void Enemy::TakeDamage(int damage)
{
	mHP -= damage;
	mHPText->SetText(to_wstring(mHP));
	if (mHP <= 0)
	{
		mIsDestroy = true;
	}
}
