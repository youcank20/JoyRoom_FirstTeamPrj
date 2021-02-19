#include "pch.h"
#include "Gengar.h"
#include "Animation.h"
#include "Image.h"

Gengar::Gengar(const string & name, float x, float y)
	:Monster(name, x, y)
{
}

void Gengar::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Gengar", Resources(L"gengar.bmp"), 590, 164, 10, 4, true);
	mImage = IMAGEMANAGER->FindImage(L"Gengar");

	mHp = 100;
	mRange = 100;
	mSpeed = 5.f;

	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(0.2f);
	mIdleAnimation->Play();

	mMoveAnimation = new Animation();
	mMoveAnimation->InitFrameByStartEnd(3, 0, 5, 0, false);
	mMoveAnimation->SetIsLoop(true);
	mMoveAnimation->SetFrameUpdateTime(0.2f);

	mAtkAnimation = new Animation();
	mAtkAnimation->InitFrameByStartEnd(6, 0, 8, 0, false);
	mAtkAnimation->SetIsLoop(true);
	mAtkAnimation->SetFrameUpdateTime(0.2f);

	//mSpeAtkAnimation = new Animation();
	//mIdleAnimation->InitFrameByStartEnd(0, 0, 0, 0, false);
	//mIdleAnimation->SetIsLoop(true);
	//mIdleAnimation->SetFrameUpdateTime(0.2f);

	mHurtAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(9, 0, 9, 0, false);
	mHurtAnimation->SetIsLoop(true);
	mHurtAnimation->SetFrameUpdateTime(0.2f);

	mCurrentAnimation = mIdleAnimation;
	mSizeX = (float)(mImage->GetFrameWidth());
	mSizeY = (float)(mImage->GetFrameHeight());
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);

	mMonState = MonsterState::Idle;
	mMonDirection = MonsterDirection::Down;
}

void Gengar::Release()
{
	SafeDelete(mIdleAnimation);
	//SafeDelete(mMoveAnimation);
	//SafeDelete(mAtkAnimation);
}

void Gengar::Update()
{
	mCurrentAnimation->Update();
}

void Gengar::Render(HDC hdc)
{
	//mImage->FrameRender(hdc, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX * 2, mSizeY * 2);
}