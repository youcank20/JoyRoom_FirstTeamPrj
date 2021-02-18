#include "pch.h"
#include "Milotic.h"

#include "Image.h"
#include "Animation.h"
#include "Camera.h"
Milotic::Milotic(const string & name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Milotic::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Milotic", Resources(L"milotic.bmp"), 183, 92, 3, 2, true);
	mImage = IMAGEMANAGER->FindImage(L"Milotic");

	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.2f);
	mLeftIdleAnimation->Play();

	mRightIdleAnimation = new Animation();
	mRightIdleAnimation->InitFrameByStartEnd(0, 1, 1, 1, false);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->SetFrameUpdateTime(0.2f);
	mRightIdleAnimation->Play();

	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.1f);

	mRightRunAnimation = new Animation();
	mRightRunAnimation->InitFrameByStartEnd(0, 1, 2, 1, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.1f);

	mCurrentAnimation = mLeftIdleAnimation;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Milotic::Release()
{
	SafeDelete(mLeftIdleAnimation);
}

void Milotic::Update()
{
	mCurrentAnimation->Update();
}

void Milotic::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());
}
