#include "pch.h"
#include "Bullet.h"
#include "Image.h"
#include "Camera.h"

void Bullet::Fire(Image* image, float x, float y, float speed, float angle)
{
	mImage = image;
	mX = x;
	mY = y;
	mSpeed = speed;
	mAngle = angle;
	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
}

void Bullet::Release()
{

}

void Bullet::Update()
{
	mX += cosf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mY -= sinf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mRect = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
}

void Bullet::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleRender(hdc, mImage, (int)mRect.left, (int)mRect.top, mImage->GetFrameWidth(), mImage->GetFrameHeight());
}