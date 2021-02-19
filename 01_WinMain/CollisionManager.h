#pragma once
#include "Player.h"
#include "Monster.h"
#include "GameObject.h"

class Player;
class Monster;
class Bullet;
class CollisionManager
{
	Player* mPlayer;
	vector <Monster*>* mMonsterListPtr;
	vector <Bullet*>* mBulletListPtr;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetPlayerPtr(Player* player) { mPlayer = player; }
	void SetMonsterVectorPtr(vector <Monster*>* monsterList) { mMonsterListPtr = monsterList; }
	void SetBulletListPtr(vector <Bullet*>* bulletList) { mBulletListPtr = bulletList; }
};