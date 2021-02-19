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
	int mMoveRange;
	int mAttackRange;
	float mAngle;
	float mSpeed;
	MonsterState mMonState;
	MonsterState mPrevMonState;
	MonsterDirection mMonDirection;
	MonsterDirection mPrevMonDirection;
	Animation* mLeftIdleAnimation;
	Animation* mLeftMoveAnimation;
	Animation* mLeftAtkAnimation;
	Animation* mLeftSpeAtkAnimation;
	Animation* mLeftHurtAnimation;
	Animation* mRightIdleAnimation;
	Animation* mRightMoveAnimation;
	Animation* mRightAtkAnimation;
	Animation* mRightSpeAtkAnimation;
	Animation* mRightHurtAnimation;
	Animation* mUpIdleAnimation;
	Animation* mUpMoveAnimation;
	Animation* mUpAtkAnimation;
	Animation* mUpSpeAtkAnimation;
	Animation* mUpHurtAnimation;
	Animation* mDownIdleAnimation;
	Animation* mDownMoveAnimation;
	Animation* mDownAtkAnimation;
	Animation* mDownSpeAtkAnimation;
	Animation* mDownHurtAnimation;
	Animation* mCurrentAnimation;
	bool mAttacked;
	float mDieAlpha;
	int mPrevIndex;
	bool mAttackWait;
	float mAttackWaitTime;
	float mHurtTime;

public:
	Monster(const string& name, float x, float y);

	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;

	inline int GetHp()const { return mHp; } // ���� ü�� �޾ƿ��� hp = GetHp();
	inline void SetHp(int hp) { mHp = hp; } // ü�� ���� �� ���� �� hp -= 20; SetHp(hp);
	inline void SetMoveRange(int moveRange) { mMoveRange = moveRange; }
	inline void SetAttackRange(int attackRange) { mAttackRange = attackRange; }
	inline float GetAngle()const { return mAngle; };
	inline void SetAngle(float angle) { mAngle = angle; }
	inline float GetSpeed()const { return mSpeed; }
	inline void SetSpeed(float speed) { mSpeed = speed; }
	inline bool GetAttacked()const { return mAttacked; }
	inline void SetAttacked(bool attacked) { mAttacked = attacked; } // �ǰ� ��� ���� SetAttacked(true); �� �� ���õǸ� �ڵ����� false ������༭ �װ� �Ű� �Ƚᵵ ��
};