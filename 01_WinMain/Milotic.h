#pragma once
#include "GameObject.h"
class Milotic : public GameObject
{
	class Image* mImage;
	class Animation* mLeftIdleAnimation;
	class Animation* mRightIdleAnimation;
	class Animation* mLeftRunAnimation;
	class Animation* mRightRunAnimation;
	class Animation* mCurrentAnimation;	//현재 애니메이션
public:
	Milotic(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	Animation* GetCurrentAnimation() { return mCurrentAnimation; }
	void SetCurrentAnimation(Animation* animation) { mCurrentAnimation = animation; }
};