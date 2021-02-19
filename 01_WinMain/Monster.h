#pragma once
#include "GameObject.h"

enum MonsterState
{
	Idle,
	Move,
	Attack,
	SpecialAttack,
	Hurt
};

enum MonsterDirection
{
	Left,
	Up,
	Right,
	Down
};

class Image;
class Player;
class Animation;

class Monster: public GameObject
{
protected:
	Image* mImage;
	Player* mPlayer;
	int mHp;
	int mRange;
	float mAngle;
	float mSpeed;
	MonsterState mMonState;
	MonsterDirection mMonDirection;

	Animation* mIdleAnimation;
	Animation* mMoveAnimation;
	Animation* mAtkAnimation;
	Animation* mSpeAtkAnimation;
	Animation* mHurtAnimation;
	Animation* mCurrentAnimation;

public:
	Monster(const string& name, float x, float y);

	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;

	inline int GetHp()const { return mHp; }
	inline void SetHp(int hp) { mHp = hp; }
	inline void SetRange(int range) { mRange = range; }
	inline float GetAngle()const { return mAngle; };
	inline void SetAngle(float angle) { mAngle = angle; }
	inline float GetSpeed()const { return mSpeed; }
	inline void SetSpeed(float speed) { mSpeed = speed; }
};