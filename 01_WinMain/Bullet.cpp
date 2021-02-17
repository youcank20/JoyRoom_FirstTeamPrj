#include "pch.h"
#include "Bullet.h"
#include "Enemy.h"
Bullet::Bullet()
	:GameObject("Bullet") {}

void Bullet::Init()
{
	mSizeX = 25;
	mSizeY = 25;
}

void Bullet::Release()
{
}

void Bullet::Update()
{
	mX += cosf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mY += -sinf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	vector<GameObject*> enemyList = 
		ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemey);

	for (int i = 0; i < enemyList.size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp, &mRect, &enemyList[i]->GetRect()))
		{
			Enemy* enemy = (Enemy*)enemyList[i];
			enemy->TakeDamage(10);
			mIsDestroy = true;
			break;
		}
	}

	if (mRect.left > WINSIZEX)
		mIsDestroy = true;
}

void Bullet::Render(HDC hdc)
{
	RenderRect(hdc, mRect);
}

void Bullet::Fire(float x, float y, float angle, float speed)
{
	mX = x;
	mY = y;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mAngle = angle;
	mSpeed = speed;
}
