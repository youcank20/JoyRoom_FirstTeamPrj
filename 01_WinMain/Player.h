#pragma once
#include "GameObject.h"

enum class State : int
{
	Right,
	Left,
	Up,
	Down
};

class Player : public GameObject
{
	vector<class Bullet*> mBullets;
	State mState;
	float mSpeed = 150.f;
	float mBulletSpeed = 300.f;
	class Image* mAttackImage;

	class Image* mImage;
	class Animation* mUpIdleAnimation;
	class Animation* mDownIdleAnimation;
	class Animation* mLeftIdleAnimation;
	class Animation* mRightIdleAnimation;
	class Animation* mUpRunAnimation;
	class Animation* mDownRunAnimation;
	class Animation* mRightRunAnimation;
	class Animation* mLeftRunAnimation;
	class Animation* mUpAttackAnimation;	//공격
	class Animation* mDownAttackAnimation;
	class Animation* mLeftAttackAnimation;
	class Animation* mRightAttackAnimation;
	class Animation* mCurrentAnimation;	//현재 애니메이션



public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void Move(float moveX, float moveY);
	RECT GetRect() { return mRect; }
	RECT GetBulletRect(int i);
	int BulletNum();
	void DeleteBullet(int i);

	void UpEndAttack();
	void DownEndAttack();
	void LeftEndAttack();
	void RightEndAttack();

};