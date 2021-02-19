#include "pch.h"
#include "CollisionManager.h"

void CollisionManager::Init()
{

}	

void CollisionManager::Release()
{	 

}	 

void CollisionManager::Update()
{	
//	RECT temp;
//	//플레이어랙트와 몬스터랙트 충돌
//	for (int i = 0;i < (*mMonsterListPtr).size();i++)
//	{
//		if (IntersectRect(&temp, &mPlayer->GetRect(), &(*mMonsterListPtr)[i]->GetRect()))
//		{
//			//mPlayer.setHP();
//			//혹은 플레이어도 공격당했단 불린 설정?
//			//충돌이팩트?
//			
//		}
//	}
//
//	//플레이어의 번개와 몬스터랙트 충돌
//	for (int i = 0;i < (*mMonsterListPtr).size();i++)
//	{
//		//플레이어렉트말고 공격으로 바꾸기
//		if (IntersectRect(&temp, &mPlayer->GetRect(), &(*mMonsterListPtr)[i]->GetRect()))
//		{
//			//(*mMonsterListPtr)[i]->SetAttacked(true);
//
//
//		}
//
//	}
//
//	//플레이어의 총알과 몬스터랙트 충돌
//	for (int i = 0;i < (*mMonsterListPtr).size();i++)
//	{
//		for (int j = 0;j < (*mBulletListPtr).size(); j++) 
//		{
//			if (IntersectRect(&temp, &mPlayer->GetRect(), &(*mMonsterListPtr)[i]->GetRect()))
//			{
//				//(*mMonsterListPtr)[i]->SetAttacked(true);
//
//
//			}
//		}
//
//	}


	//몬스터의 공격과 플레이어 충돌

}	

void CollisionManager::Render(HDC hdc)
{

}