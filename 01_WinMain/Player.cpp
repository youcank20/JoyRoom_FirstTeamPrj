#include "pch.h"
#include "Player.h"
#include "Bullet.h"

//멤버 이니셜라이즈할때 부모의 생성자 호출 가능하다, 내가 명시적으로 호출하지 
//않으면 기본 생성자(매개변수 없는생성자)가 호출된다 자동으로
Player::Player()
	: GameObject("Player") {}

void Player::Init()
{
	mX = WINSIZEX / 2; 
	mY = WINSIZEY / 2;
	mSizeX = 100;
	mSizeY = 100;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Release()
{
}

void Player::Update()
{
	if (Input::GetInstance()->GetKey('A'))
		mX -= 100.f * Time::GetInstance()->DeltaTime();
	else if (Input::GetInstance()->GetKey('D'))
		mX += 100.f * Time::GetInstance()->DeltaTime();
	if (Input::GetInstance()->GetKey('W'))
		mY -= 100.f * Time::GetInstance()->DeltaTime();
	else if (Input::GetInstance()->GetKey('S'))
		mY += 100.f * Time::GetInstance()->DeltaTime();
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		Bullet* bullet = new Bullet();
		bullet->Init();
		bullet->Fire(mX, mY, 0.f, 500.f);

		ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, bullet);
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Render(HDC hdc)
{
	RenderRect(hdc,mRect);
}
