#include "pch.h"
#include "Scene1.h"

#include "Player.h"
#include "Camera.h"
#include "GameEvent.h"
void Scene1::Init()
{
	Player* player1 = new Player("1", 100, WINSIZEY / 2);
	Player* player2 = new Player("2", WINSIZEX - 100, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player2);
	
	Camera* camera = new Camera();
	camera->SetX(100);
	camera->SetY(WINSIZEY / 2);
	camera->SetTarget(player1);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player,camera);

	ObjectManager::GetInstance()->Init();

	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.0f));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(player2));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(3.0f));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(player1));
}

void Scene1::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene1::Update()
{
	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();
}

void Scene1::Render(HDC hdc)
{
	ObjectManager::GetInstance()->Render(hdc);
}
