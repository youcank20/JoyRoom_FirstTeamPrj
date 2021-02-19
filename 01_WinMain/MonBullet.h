#pragma once
#include "GameObject.h"

enum BulletType
{
	Wind,
	Fire
};

class Image;
class Animation;

class MonBullet : public GameObject
{
protected:
	Image* mImage;
	float mAngle;
	float mSpeed;
	Animation* mAnimation;
	float mTargetX;
	float mTargetY;
	BulletType mBulletType;

public:
	MonBullet(float x, float y, float targetX, float targetY, float angle, float speed, BulletType bulletType);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	inline float GetAngle()const { return mAngle; };
	inline void SetAngle(float angle) { mAngle = angle; }
	inline float GetSpeed()const { return mSpeed; }
	inline void SetSpeed(float speed) { mSpeed = speed; }
};