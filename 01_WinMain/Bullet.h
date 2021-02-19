#pragma once

class Bullet
{
	float mX;
	float mY;
	float mSpeed;
	float mAngle;
	RECT mRect;

	Image* mImage;

public:
	void Fire(class Image* image, float x, float y, float speed, float angle);
	void Release();
	void Update();
	void Render(HDC hdc);
	RECT GetRect() { return mRect; };
};
