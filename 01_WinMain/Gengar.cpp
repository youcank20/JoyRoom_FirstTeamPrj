#include "pch.h"
#include "Gengar.h"
#include "Animation.h"
#include "Image.h"
#include "Player.h"
#include "Camera.h"

Gengar::Gengar(const string & name, float x, float y, Player* player)
	:Monster(name, x, y)
{
	mPlayer = player;
}

void Gengar::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Gengar", Resources(L"gengar.bmp"), 590, 164, 10, 4, true);
	mImage = IMAGEMANAGER->FindImage(L"Gengar");

	mHp = 100;
	mMoveRange = 300;
	mAttackRange = 50;
	mAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
	mSpeed = 50.f;

	mDownIdleAnimation = new Animation();
	mDownIdleAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	mDownIdleAnimation->SetIsLoop(true);
	mDownIdleAnimation->SetFrameUpdateTime(0.2f);
	mDownIdleAnimation->Play();

	mUpIdleAnimation = new Animation();
	mUpIdleAnimation->InitFrameByStartEnd(0, 1, 2, 1, false);
	mUpIdleAnimation->SetIsLoop(true);
	mUpIdleAnimation->SetFrameUpdateTime(0.2f);

	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 2, 2, 2, false);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.2f);

	mRightIdleAnimation = new Animation();
	mRightIdleAnimation->InitFrameByStartEnd(0, 3, 2, 3, false);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->SetFrameUpdateTime(0.2f);

	mDownMoveAnimation = new Animation();
	mDownMoveAnimation->InitFrameByStartEnd(3, 0, 5, 0, false);
	mDownMoveAnimation->SetIsLoop(true);
	mDownMoveAnimation->SetFrameUpdateTime(0.2f);

	mUpMoveAnimation = new Animation();
	mUpMoveAnimation->InitFrameByStartEnd(3, 1, 5, 1, false);
	mUpMoveAnimation->SetIsLoop(true);
	mUpMoveAnimation->SetFrameUpdateTime(0.2f);

	mLeftMoveAnimation = new Animation();
	mLeftMoveAnimation->InitFrameByStartEnd(3, 2, 5, 2, false);
	mLeftMoveAnimation->SetIsLoop(true);
	mLeftMoveAnimation->SetFrameUpdateTime(0.2f);

	mRightMoveAnimation = new Animation();
	mRightMoveAnimation->InitFrameByStartEnd(3, 3, 5, 3, false);
	mRightMoveAnimation->SetIsLoop(true);
	mRightMoveAnimation->SetFrameUpdateTime(0.2f);

	mDownAtkAnimation = new Animation();
	mDownAtkAnimation->InitFrameByStartEnd(6, 0, 8, 0, false);
	mDownAtkAnimation->SetIsLoop(true);
	mDownAtkAnimation->SetFrameUpdateTime(0.2f);

	mUpAtkAnimation = new Animation();
	mUpAtkAnimation->InitFrameByStartEnd(6, 1, 8, 1, false);
	mUpAtkAnimation->SetIsLoop(true);
	mUpAtkAnimation->SetFrameUpdateTime(0.2f);

	mLeftAtkAnimation = new Animation();
	mLeftAtkAnimation->InitFrameByStartEnd(6, 2, 8, 2, false);
	mLeftAtkAnimation->SetIsLoop(true);
	mLeftAtkAnimation->SetFrameUpdateTime(0.2f);

	mRightAtkAnimation = new Animation();
	mRightAtkAnimation->InitFrameByStartEnd(6, 3, 8, 3, false);
	mRightAtkAnimation->SetIsLoop(true);
	mRightAtkAnimation->SetFrameUpdateTime(0.2f);

	//mSpeAtkAnimation = new Animation();
	//mIdleAnimation->InitFrameByStartEnd(0, 0, 0, 0, false);
	//mIdleAnimation->SetIsLoop(true);
	//mIdleAnimation->SetFrameUpdateTime(0.2f);

	mDownHurtAnimation = new Animation();
	mDownHurtAnimation->InitFrameByStartEnd(9, 0, 9, 0, false);
	mDownHurtAnimation->SetIsLoop(true);
	mDownHurtAnimation->SetFrameUpdateTime(0.2f);

	mUpHurtAnimation = new Animation();
	mUpHurtAnimation->InitFrameByStartEnd(9, 1, 9, 1, false);
	mUpHurtAnimation->SetIsLoop(true);
	mUpHurtAnimation->SetFrameUpdateTime(0.2f);

	mLeftHurtAnimation = new Animation();
	mLeftHurtAnimation->InitFrameByStartEnd(9, 2, 9, 2, false);
	mLeftHurtAnimation->SetIsLoop(true);
	mLeftHurtAnimation->SetFrameUpdateTime(0.2f);

	mRightHurtAnimation = new Animation();
	mRightHurtAnimation->InitFrameByStartEnd(9, 3, 9, 3, false);
	mRightHurtAnimation->SetIsLoop(true);
	mRightHurtAnimation->SetFrameUpdateTime(0.2f);

	mCurrentAnimation = mDownIdleAnimation;
	mSizeX = (float)(mImage->GetFrameWidth());
	mSizeY = (float)(mImage->GetFrameHeight());
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);

	mMonState = MonsterState::Idle;
	mPrevMonState = MonsterState::Idle;
	mMonDirection = MonsterDirection::Down;
	mPrevMonDirection = MonsterDirection::Down;
}

void Gengar::Release()
{
	SafeDelete(mDownIdleAnimation);
	SafeDelete(mUpIdleAnimation);
	SafeDelete(mLeftIdleAnimation);
	SafeDelete(mRightIdleAnimation);
	SafeDelete(mDownMoveAnimation);
	SafeDelete(mUpMoveAnimation);
	SafeDelete(mLeftMoveAnimation);
	SafeDelete(mRightMoveAnimation);
	SafeDelete(mDownAtkAnimation);
	SafeDelete(mUpAtkAnimation);
	SafeDelete(mLeftAtkAnimation);
	SafeDelete(mRightAtkAnimation);
	SafeDelete(mDownHurtAnimation);
	SafeDelete(mUpHurtAnimation);
	SafeDelete(mLeftHurtAnimation);
	SafeDelete(mRightHurtAnimation);
}

void Gengar::Update()
{
	if (mHp <= 0 && mDieAlpha <= 0.f)
	{
		mIsActive = false;
	}

	if (Input::GetInstance()->GetKeyDown('E')) // 피격 테스트용임, 사용 끝나면 주석
	{
		mAttacked = true;
		mHp -= 20;
	}

	if (mAttacked || mHp <= 0)
	{
		mMonState = MonsterState::Hurt;
		mAttacked = false;

		mAttackWait = false;
		mAttackWaitTime = 0.f;
	}

	float distance = Math::GetDistance(mX, mY, mPlayer->GetX(), mPlayer->GetY());
	if (mMonState != MonsterState::Hurt)
	{
		if (distance >= mMoveRange)
			mMonState = MonsterState::Idle;
		else if (distance >= mAttackRange)
			mMonState = MonsterState::Move;
		else
			mMonState = MonsterState::Attack;
	}

	if (mAttackWait)
	{
		mAttackWaitTime += Time::GetInstance()->DeltaTime();
		if (mAttackWaitTime >= 0.8f) // 때리는 동작 대기시간 조절
		{
			mAttackWait = false;
			mAttackWaitTime = 0.f;
		}
		else
			return;
	}

	if (mHp <= 0)
	{
		mDieAlpha -= 0.2f * Time::GetInstance()->DeltaTime();
	}

	mAngle = Math::GetAngle(mX, mY, mPlayer->GetX(), mPlayer->GetY());
	if (mAngle >= PI * 5 / 4 && mAngle < PI * 7 / 4)
		mMonDirection = MonsterDirection::Down;
	else if(mAngle >= PI * 3 / 4 && mAngle < PI * 5 / 4)
		mMonDirection = MonsterDirection::Left;
	else if (mAngle >= PI * 1 / 4 && mAngle < PI * 3 / 4)
		mMonDirection = MonsterDirection::Up;
	else if (mAngle >= PI * 7 / 4 || mAngle < PI * 1 / 4)
		mMonDirection = MonsterDirection::Right;

	if (mMonState == MonsterState::Move)
	{
		mX += cosf(mAngle * 180 / PI) * mSpeed * Time::GetInstance()->DeltaTime();
		mY += (-sinf(mAngle * 180 / PI)) * mSpeed * Time::GetInstance()->DeltaTime();
		mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
	}
	if (mMonState == MonsterState::Move && (mPrevMonState != MonsterState::Move || mPrevMonDirection != mMonDirection))
	{
		mCurrentAnimation->Stop();
		if(mMonDirection == MonsterDirection::Down)
			mCurrentAnimation = mDownMoveAnimation;
		else if (mMonDirection == MonsterDirection::Left)
			mCurrentAnimation = mLeftMoveAnimation;
		else if (mMonDirection == MonsterDirection::Up)
			mCurrentAnimation = mUpMoveAnimation;
		else if (mMonDirection == MonsterDirection::Right)
			mCurrentAnimation = mRightMoveAnimation;
		mCurrentAnimation->Play();
	}
	if (mMonState == MonsterState::Attack && (mPrevMonState != MonsterState::Attack || mPrevMonDirection != mMonDirection))
	{
		mCurrentAnimation->Stop();
		if (mMonDirection == MonsterDirection::Down)
			mCurrentAnimation = mDownAtkAnimation;
		else if (mMonDirection == MonsterDirection::Left)
			mCurrentAnimation = mLeftAtkAnimation;
		else if (mMonDirection == MonsterDirection::Up)
			mCurrentAnimation = mUpAtkAnimation;
		else if (mMonDirection == MonsterDirection::Right)
			mCurrentAnimation = mRightAtkAnimation;
		mCurrentAnimation->Play();
	}
	if (mMonState == MonsterState::Hurt && (mPrevMonState != MonsterState::Hurt || mPrevMonDirection != mMonDirection))
	{
		mCurrentAnimation->Stop();
		if (mMonDirection == MonsterDirection::Down)
			mCurrentAnimation = mDownHurtAnimation;
		else if (mMonDirection == MonsterDirection::Left)
			mCurrentAnimation = mLeftHurtAnimation;
		else if (mMonDirection == MonsterDirection::Up)
			mCurrentAnimation = mUpHurtAnimation;
		else if (mMonDirection == MonsterDirection::Right)
			mCurrentAnimation = mRightHurtAnimation;
		mCurrentAnimation->Play();
	}

	if (mMonState == MonsterState::Hurt)
	{
		mHurtTime += Time::GetInstance()->DeltaTime();
		if (mHurtTime >= 1.f)
		{
			mHurtTime = 0.f;
			mMonState = mPrevMonState;
			mPrevMonState = MonsterState::Hurt;
			mCurrentAnimation->Stop();
			if (mDieAlpha == 1.f)
			{
				if (mMonState == MonsterState::Move)
				{
					if (mMonDirection == MonsterDirection::Down)
						mCurrentAnimation = mDownMoveAnimation;
					else if (mMonDirection == MonsterDirection::Left)
						mCurrentAnimation = mLeftMoveAnimation;
					else if (mMonDirection == MonsterDirection::Up)
						mCurrentAnimation = mUpMoveAnimation;
					else if (mMonDirection == MonsterDirection::Right)
						mCurrentAnimation = mRightMoveAnimation;
				}
					mCurrentAnimation = mDownMoveAnimation;
					if (mMonState == MonsterState::Attack)
					{
						if (mMonDirection == MonsterDirection::Down)
							mCurrentAnimation = mDownAtkAnimation;
						else if (mMonDirection == MonsterDirection::Left)
							mCurrentAnimation = mLeftAtkAnimation;
						else if (mMonDirection == MonsterDirection::Up)
							mCurrentAnimation = mUpAtkAnimation;
						else if (mMonDirection == MonsterDirection::Right)
							mCurrentAnimation = mRightAtkAnimation;
				}
			}
			mCurrentAnimation->Play();
		}
	}

	mCurrentAnimation->Update();

	if (mMonState != MonsterState::Hurt)
		mPrevMonState = mMonState;

	if (mPrevIndex == 8 && mCurrentAnimation->GetNowFrameX() == 6)
		mAttackWait = true;

	if (mMonState == MonsterState::Attack)
		mPrevIndex = mCurrentAnimation->GetNowFrameX();

	mPrevMonDirection = mMonDirection;
}

void Gengar::Render(HDC hdc)
{
	//mImage->FrameRender(hdc, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	//mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX * 2, mSizeY * 2);
	//CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, (int)mRect.left, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX * 2, (int)mSizeY * 2);
	if (mDieAlpha <= 0.f)
		return;

	if (mMonState == MonsterState::Hurt && mHurtTime > 0.f && mDieAlpha == 1.f)
	{
		if ((int)(mHurtTime * 4) % 2)
			CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mImage, (int)mRect.left - 2, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX * 2, (int)mSizeY * 2, mDieAlpha);
		else
			CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mImage, (int)mRect.left + 2, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX * 2, (int)mSizeY * 2, mDieAlpha);
	}
	else
		CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mImage, (int)mRect.left, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX * 2, (int)mSizeY * 2, mDieAlpha);
}