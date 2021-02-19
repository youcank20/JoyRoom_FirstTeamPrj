#include "pch.h"
#include "MonBullet.h"
#include "Camera.h"
#include "Animation.h"

MonBullet::MonBullet(float x, float y, float targetX, float targetY, float angle, float speed, BulletType bulletType)
{
	mX = x;
	mY = y;
	mTargetX = targetX;
	mTargetY = targetY;
	mBulletType = bulletType;
}

void MonBullet::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Wind", Resources(L"Wind.bmp"), 64, 16, 4, 1, true);
	IMAGEMANAGER->LoadFromFile(L"Fire", Resources(L"Fire.bmp"), 64, 16, 4, 1, true);

	if(mBulletType == BulletType::Wind)
		mImage = IMAGEMANAGER->FindImage(L"Wind");
	else if (mBulletType == BulletType::Fire)
		mImage = IMAGEMANAGER->FindImage(L"Fire");

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, 0, 3, 0, false);
	mAnimation->SetIsLoop(true);
	mAnimation->SetFrameUpdateTime(0.2f);
}

void MonBullet::Release()
{
}

void MonBullet::Update()
{
	mX += cosf(mAngle * 180 / PI) * mSpeed * Time::GetInstance()->DeltaTime();
	mY += (-sinf(mAngle * 180 / PI)) * mSpeed * Time::GetInstance()->DeltaTime();
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);

	mAnimation->Update();
}

void MonBullet::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, (int)mRect.left, (int)mRect.top, mAnimation->GetNowFrameX(), mAnimation->GetNowFrameY(), (int)mSizeX * 2, (int)mSizeY * 2);
}