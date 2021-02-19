#include "pch.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Camera.h"
Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Player", Resources(L"Siva.bmp"), 832, 208, 8, 2,true);
	mImage = IMAGEMANAGER->FindImage(L"Player");

	mIdleAnimation = new Animation();
	mIdleAnimation->InitFrameByStartEnd(0, 0, 1, 0,false);
	mIdleAnimation->SetIsLoop(true);
	mIdleAnimation->SetFrameUpdateTime(0.3f);
	mIdleAnimation->Play();

	mRunAnimation = new Animation();
	mRunAnimation->InitFrameByStartEnd(2, 0, 7, 0, false);
	mRunAnimation->SetIsLoop(true);
	mRunAnimation->SetFrameUpdateTime(0.1f);

	//Animation* attackAnimation = new Animation();
	mAttackAnimation = new Animation();
	mAttackAnimation->InitFrameByStartEnd(0, 1, 6, 1, false);
	mAttackAnimation->SetIsLoop(false);
	mAttackAnimation->SetFrameUpdateTime(0.2f);
	mAttackAnimation->SetCallbackFunc(bind(&Player::OnAnimEndAttack, this));

	mCurrentAnimation = mIdleAnimation;
	mSizeX = (float)(mImage->GetFrameWidth());
	mSizeY = (float)(mImage->GetFrameHeight());
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
}

void Player::Release()
{
	SafeDelete(mIdleAnimation);
}

void Player::Update()
{
	if (Input::GetInstance()->GetKeyDown('D'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRunAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp('D'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mIdleAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyDown('K'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mAttackAnimation;
		mCurrentAnimation->Play();

		//공격랙트생성
	}
	mCurrentAnimation->Update();
}

void Player::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top,
			mCurrentAnimation->GetNowFrameX(),
			mCurrentAnimation->GetNowFrameY());

	//mImage->FrameRender(hdc,mRect.left,mRect.top, mCurrentAnimation->GetNowFrameX(),
	//	mCurrentAnimation->GetNowFrameY());
}

void Player::OnAnimEndAttack()
{
	//Idle로 상태 변경등등
	mCurrentAnimation->Stop();
	mCurrentAnimation = mIdleAnimation;
	mCurrentAnimation->Play();
}
