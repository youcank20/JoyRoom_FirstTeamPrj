#include "pch.h"
#include "Scene1.h"

#include "Player.h"
#include "Camera.h"
#include "GameEvent.h"
#include "Image.h"

#include "Milotic.h"

#include "Gengar.h"
#include "Wobbuffet.h"
#include "Psyduck.h"
#include "Staravia.h"

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

	Wobbuffet* wobbuffet1 = new Wobbuffet("Wobbuffet1", 150, 100, player1);
	wobbuffet1->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, wobbuffet1);
	Wobbuffet* wobbuffet2 = new Wobbuffet("Wobbuffet2", 300, 300, player1);
	wobbuffet2->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, wobbuffet2);
	Wobbuffet* wobbuffet3 = new Wobbuffet("Wobbuffet3", 250, 550, player1);
	wobbuffet3->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, wobbuffet3);
	Wobbuffet* wobbuffet4 = new Wobbuffet("Wobbuffet4", -150, 250, player1);
	wobbuffet4->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, wobbuffet4);

	Psyduck* psyduck1 = new Psyduck("Psyduck1", 160, 100, player1);
	psyduck1->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, psyduck1);
	Psyduck* psyduck2 = new Psyduck("Psyduck2", 310, 300, player1);
	psyduck2->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, psyduck2);
	Psyduck* psyduck3 = new Psyduck("Psyduck3", 260, 550, player1);
	psyduck3->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, psyduck3);
	Psyduck* psyduck4 = new Psyduck("Psyduck4", -140, 250, player1);
	psyduck4->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, psyduck4);

	Staravia* staravia1 = new Staravia("staravia1", 167, 100, player1);
	staravia1->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, staravia1);
	Staravia* staravia2 = new Staravia("staravia2", 317, 300, player1);
	staravia2->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, staravia2);
	Staravia* staravia3 = new Staravia("staravia3", 267, 550, player1);
	staravia3->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, staravia3);
	Staravia* staravia4 = new Staravia("staravia4", -127, 250, player1);
	staravia4->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Monster, staravia4);


	// 여기까지 몬스터 }}Psyduck
}

void Scene1::Release()
{
	ObjectManager::GetInstance()->Release();
}

void Scene1::Update()
{
	if(Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		//GameEventManager::GetInstance()->PushEvent(new IDelayEvent(2.0f));
		//GameEventManager::GetInstance()->PushEvent(new IChangeCameraTargetEvent(ObjectManager::GetInstance()->FindObject("milotic")));
		//dynamic_cast<Milotic*>(ObjectManager::GetInstance()->FindObject("milotic"))->GetCurrentAnimation()->;
		GameEventManager::GetInstance()->PushEvent(
			new IScriptEvent(L"milotic_profile", L"이것은 테스트용 문장이다"));
		GameEventManager::GetInstance()->PushEvent(
			new IScriptEvent(L"milotic_profile", L"문장을 바꿔보겠다"));
		GameEventManager::GetInstance()->PushEvent(
			new IScriptEvent(L"milotic_profile", L"아 이게 되네 ㅋㅋㅋㅋㅋ"));
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