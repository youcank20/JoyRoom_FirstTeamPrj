#include "pch.h"
#include "Scene1.h"

#include "Player.h"
#include "Camera.h"
#include "GameEvent.h"
#include "Image.h"

#include "Milotic.h"

#include "Gengar.h"

void Scene1::Init()
{
	Player* player1 = new Player("1", 100, WINSIZEY / 2);
	Player* player2 = new Player("2", WINSIZEX - 100, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player1);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player2);

	Milotic* milotic = new Milotic("milotic", WINSIZEX + 50, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, milotic);
	
	Camera* camera = new Camera();
	camera->SetX(100);
	camera->SetY(WINSIZEY / 2);
	camera->SetTarget(player1);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player,camera);

	ObjectManager::GetInstance()->Init();

	/*GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.0f));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(player2));
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(3.0f));
	GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(player1));*/

	IMAGEMANAGER->LoadFromFile(L"Field", Resources(L"Field.bmp"), 1200, 1200, false);
	mBackground = IMAGEMANAGER->FindImage(L"Field");

	IMAGEMANAGER->LoadFromFile(L"milotic_profile", Resources(L"milotic_profile.bmp"), 120, 120, false);
	IMAGEMANAGER->LoadFromFile(L"pikachu_profile", Resources(L"pikachu_profile.bmp"), 120, 120, false);

	// {{ 여기부터 몬스터
	Gengar* gengar1 = new Gengar("Gengar1", 200, 100, player1);
	gengar1->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, gengar1);
	Gengar* gengar2 = new Gengar("Gengar2", 350, 300, player1);
	gengar2->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, gengar2);
	Gengar* gengar3 = new Gengar("Gengar3", 300, 550, player1);
	gengar3->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, gengar3);
	Gengar* gengar4 = new Gengar("Gengar4", -150, 300, player1);
	gengar4->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, gengar4);



	// 여기까지 몬스터 }}
}

void Scene1::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene1::Update()
{
	//if(ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Monster).size() == NULL)
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		//GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.0f));
		//GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(ObjectManager::GetInstance()->FindObject("milotic")));
		//dynamic_cast<Milotic*>(ObjectManager::GetInstance()->FindObject("milotic"))->GetCurrentAnimation()->;
		GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(ObjectManager::GetInstance()->FindObject("milotic")));
		GameEventManager::GetInstance()->PushEvent(
			new IMoveGameObject(ObjectManager::GetInstance()->FindObject("milotic"), ObjectManager::GetInstance()->FindObject("1")));

		GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f));

		GameEventManager::GetInstance()->PushEvent(
			new IScriptEvent(L"milotic_profile", L"이것은 테스트용 문장이다"));
		GameEventManager::GetInstance()->PushEvent(
			new IScriptEvent(L"milotic_profile", L"문장을 바꿔보겠다"));
		GameEventManager::GetInstance()->PushEvent(
			new IScriptEvent(L"pikachu_profile", L"이건 대사 주고받기다"));
		GameEventManager::GetInstance()->PushEvent(
			new IScriptEvent(L"milotic_profile", L"아 이게 되네 ㅋㅋㅋㅋㅋ"));
		GameEventManager::GetInstance()->PushEvent(
			new IScriptEvent(L"pikachu_profile", L"만ㅡ족"));

		GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(ObjectManager::GetInstance()->FindObject("1")));
		GameEventManager::GetInstance()->PushEvent(
			new IMoveGameObject(ObjectManager::GetInstance()->FindObject("milotic"), WINSIZEX * 2, ObjectManager::GetInstance()->FindObject("milotic")->GetY()));

	}

	ObjectManager::GetInstance()->Update();
	GameEventManager::GetInstance()->Update();
}

void Scene1::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleRender(hdc, mBackground, -960, 0, 3600, 3600);
//	mBackground->ScaleRender(hdc, 0, 0, 2400, 2400);
	ObjectManager::GetInstance()->Render(hdc);
	GameEventManager::GetInstance()->Render(hdc);
}