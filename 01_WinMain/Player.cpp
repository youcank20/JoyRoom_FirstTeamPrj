#include "pch.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Bullet.h"
Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{
	IMAGEMANAGER->LoadFromFile(L"Player", Resources(L"pikachu.bmp"), 297, 104, 9, 4,true);
	mImage = IMAGEMANAGER->FindImage(L"Player");

	mState = State::Down;

	ImageManager::GetInstance()->LoadFromFile(L"Attack", L"../02_Resources/yellowball.bmp", 8, 8, true);

	//스탠드 이미지
	mUpIdleAnimation = new Animation();
	mUpIdleAnimation->InitFrameByStartEnd(0, 1, 1, 1,false);
	mUpIdleAnimation->SetIsLoop(true);
	mUpIdleAnimation->SetFrameUpdateTime(0.3f);
	mUpIdleAnimation->Play();

	mDownIdleAnimation = new Animation();
	mDownIdleAnimation->InitFrameByStartEnd(0, 0, 1, 0, false);
	mDownIdleAnimation->SetIsLoop(true);
	mDownIdleAnimation->SetFrameUpdateTime(0.3f);
	mDownIdleAnimation->Play();

	mLeftIdleAnimation = new Animation();
	mLeftIdleAnimation->InitFrameByStartEnd(0, 2, 1, 2, false);
	mLeftIdleAnimation->SetIsLoop(true);
	mLeftIdleAnimation->SetFrameUpdateTime(0.3f);
	mLeftIdleAnimation->Play();

	mRightIdleAnimation = new Animation();
	mRightIdleAnimation->InitFrameByStartEnd(0, 3, 1, 3, false);
	mRightIdleAnimation->SetIsLoop(true);
	mRightIdleAnimation->SetFrameUpdateTime(0.3f);
	mRightIdleAnimation->Play();

	//이동 이미지
	mUpRunAnimation = new Animation();
	mUpRunAnimation->InitFrameByStartEnd(2, 1, 5, 1, false);
	mUpRunAnimation->SetIsLoop(true);
	mUpRunAnimation->SetFrameUpdateTime(0.1f);

	mDownRunAnimation = new Animation();
	mDownRunAnimation->InitFrameByStartEnd(2, 0, 5, 0, false);
	mDownRunAnimation->SetIsLoop(true);
	mDownRunAnimation->SetFrameUpdateTime(0.1f);

	mLeftRunAnimation = new Animation();
	mLeftRunAnimation->InitFrameByStartEnd(2, 2, 5, 2, false);
	mLeftRunAnimation->SetIsLoop(true);
	mLeftRunAnimation->SetFrameUpdateTime(0.1f);

	mRightRunAnimation = new Animation();
	mRightRunAnimation->InitFrameByStartEnd(2, 3, 5, 3, false);
	mRightRunAnimation->SetIsLoop(true);
	mRightRunAnimation->SetFrameUpdateTime(0.1f);

	//Animation* attackAnimation = new Animation();

	//공격 이미지
	mUpAttackAnimation = new Animation();
	mUpAttackAnimation->InitFrameByStartEnd(6, 1, 7, 1, false);
	mUpAttackAnimation->SetIsLoop(false);
	mUpAttackAnimation->SetFrameUpdateTime(0.2f);
	mUpAttackAnimation->SetCallbackFunc(bind(&Player::UpEndAttack, this));

	mDownAttackAnimation = new Animation();
	mDownAttackAnimation->InitFrameByStartEnd(6, 0, 7, 0, false);
	mDownAttackAnimation->SetIsLoop(false);
	mDownAttackAnimation->SetFrameUpdateTime(0.2f);
	mDownAttackAnimation->SetCallbackFunc(bind(&Player::DownEndAttack, this));

	mLeftAttackAnimation = new Animation();
	mLeftAttackAnimation->InitFrameByStartEnd(6, 2, 7, 2, false);
	mLeftAttackAnimation->SetIsLoop(false);
	mLeftAttackAnimation->SetFrameUpdateTime(0.2f);
	mLeftAttackAnimation->SetCallbackFunc(bind(&Player::LeftEndAttack, this));

	mRightAttackAnimation = new Animation();
	mRightAttackAnimation->InitFrameByStartEnd(6, 3, 7, 3, false);
	mRightAttackAnimation->SetIsLoop(false);
	mRightAttackAnimation->SetFrameUpdateTime(0.2f);
	mRightAttackAnimation->SetCallbackFunc(bind(&Player::RightEndAttack, this));

	mCurrentAnimation = mDownIdleAnimation;
	mSizeX = (float)(mImage->GetFrameWidth());
	mSizeY = (float)(mImage->GetFrameHeight());
	mRect = RectMakeCenter((int)mX, (int)mY, (int)mSizeX, (int)mSizeY);
}

void Player::Release()
{
	//SafeDelete(mIdleAnimation);
}

void Player::Update()
{
	//이동 프레임 이미지
	if (Input::GetInstance()->GetKeyDown('W'))
	{
		mState = State::Up;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mUpRunAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp('W'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mUpIdleAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyDown('S'))
	{
		mState = State::Down;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mDownRunAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp('S'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mDownIdleAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyDown('A'))
	{
		mState = State::Left;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftRunAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp('A'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftIdleAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyDown('D'))
	{
		mState = State::Right;
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightRunAnimation;
		mCurrentAnimation->Play();
	}
	if (Input::GetInstance()->GetKeyUp('D'))
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightIdleAnimation;
		mCurrentAnimation->Play();
	}
	//플레이어 이동
	if (Input::GetInstance()->GetKey('W'))
	{
		mY -= mSpeed * Time::GetInstance()->DeltaTime();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	if (Input::GetInstance()->GetKey('S'))
	{
		mY += mSpeed * Time::GetInstance()->DeltaTime();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	if (Input::GetInstance()->GetKey('A'))
	{
		mX -= mSpeed * Time::GetInstance()->DeltaTime();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	if (Input::GetInstance()->GetKey('D'))
	{
		mX += mSpeed * Time::GetInstance()->DeltaTime();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}

	//공격
	if (Input::GetInstance()->GetKeyDown('K'))
	{
		Bullet* bullet = new Bullet;
		mAttackImage = ImageManager::GetInstance()->FindImage(L"Attack");
		if (mState == State::Up)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mUpAttackAnimation;
			mCurrentAnimation->Play();
			bullet->Fire(mAttackImage, mX + 15, mY, mBulletSpeed, PI / 2.f);
			mBullets.push_back(bullet);
		}
		if (mState == State::Down)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mDownAttackAnimation;
			mCurrentAnimation->Play();
			bullet->Fire(mAttackImage, mX + 15, mY + 30, mBulletSpeed, PI + PI / 2);
			mBullets.push_back(bullet);
		}
		if (mState == State::Left)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftAttackAnimation;
			mCurrentAnimation->Play();
			bullet->Fire(mAttackImage, mX, mY + 20, mBulletSpeed, PI);
			mBullets.push_back(bullet);
		}
		if (mState == State::Right)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightAttackAnimation;
			mCurrentAnimation->Play();
			bullet->Fire(mAttackImage, mX + 30, mY + 20, mBulletSpeed, 0);
			mBullets.push_back(bullet);
		}
	}
	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Update();

	}

		//공격랙트생성
	mCurrentAnimation->Update();
}

void Player::Render(HDC hdc)
{
	//CameraManager::GetInstance()->GetMainCamera()
	//	->FrameRender(hdc, mImage, mRect.left, mRect.top,
	//		mCurrentAnimation->GetNowFrameX(),
	//		mCurrentAnimation->GetNowFrameY());
	CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mImage, (int)mRect.left, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX * 2, (int)mSizeY * 2, 1.f);

	for (int i = 0; i < mBullets.size(); ++i)
	{
		mBullets[i]->Render(hdc);
		//CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, (int)mRect.left, (int)mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), (int)mSizeX * 2, (int)mSizeY * 2, 1.f);

	}
	//mImage->FrameRender(hdc,mRect.left,mRect.top, mCurrentAnimation->GetNowFrameX(),
	//	mCurrentAnimation->GetNowFrameY());
}

void Player::UpEndAttack()
{
	//Idle로 상태 변경등등
	mCurrentAnimation->Stop();
	mCurrentAnimation = mUpIdleAnimation;
	mCurrentAnimation->Play();
}

void Player::DownEndAttack()
{
	//Idle로 상태 변경등등
	mCurrentAnimation->Stop();
	mCurrentAnimation = mDownIdleAnimation;
	mCurrentAnimation->Play();
}

void Player::LeftEndAttack()
{
	//Idle로 상태 변경등등
	mCurrentAnimation->Stop();
	mCurrentAnimation = mLeftIdleAnimation;
	mCurrentAnimation->Play();
}

void Player::RightEndAttack()
{
	//Idle로 상태 변경등등
	mCurrentAnimation->Stop();
	mCurrentAnimation = mRightIdleAnimation;
	mCurrentAnimation->Play();
}

void Player::Move(float moveX, float moveY)
{
	mX += moveX;
	mY += moveY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

RECT Player::GetBulletRect(int i)
{
	RECT temp = mBullets[i]->GetRect();
	return temp;
}

int Player::BulletNum()
{
	return mBullets.size();
}

void Player::DeleteBullet(int i)
{
	SafeDelete(mBullets[i]);
	mBullets.erase(mBullets.begin() + i);
}