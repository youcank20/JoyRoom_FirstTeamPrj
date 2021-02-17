#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include "Scene1.h"
#include "Scene2.h"
#include "LoadingScene.h"
/*
Scene : 스테이지 단위를 씬이라고 함
*/
void MainGame::Init()
{
	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	SceneManager::GetInstance()->AddScene(L"Loading", new LoadingScene);
	SceneManager::GetInstance()->AddScene(L"Scene1", new Scene1);
	SceneManager::GetInstance()->AddScene(L"Scene2", new Scene2);

	SceneManager::GetInstance()->LoadScene(L"Loading");

//	LoadingScene* scene = new LoadingScene;
//	scene->AddLoadFunc([]() { &LoadFromImageFile; });

	//Scene* scene = SceneManager::GetInstance()->GetCurrentScene();
	//((LoadingScene*)scene)->AddLoadFunc([]() { LoadFromImageFile; });
	//((LoadingScene*)scene)->AddLoadFunc([]() { LoadFromSoundFile; });

	int rand1 = Random::GetInstance()->RandomInt(100, 500);
	int rand2 = Random::GetInstance()->RandomInt(100, 500);

	Scene* scene = SceneManager::GetInstance()->GetCurrentScene();
	for(int i = 0; i < rand1; ++i)
		((LoadingScene*)scene)->AddLoadFunc([]() { ImageManager::GetInstance()->LoadFromFile(L"Bullet", Resources(L"bullet.bmp"), 21, 21, true); });
	((LoadingScene*)scene)->SetImgMax(rand1);
	for (int i = 0; i < rand2; ++i)
		((LoadingScene*)scene)->AddLoadFunc([]() { SoundPlayer::GetInstance()->LoadFromFile(L"TSound", Resources(L"TestSound.mp3"), false); });
	((LoadingScene*)scene)->SetSndMax(rand2);

	//bStart = false;
}

void MainGame::Release()
{
	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제

	SafeDelete(mBackBuffer);
}

void MainGame::Update()
{
	//if (!bStart)
	//{
	//	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	//		bStart = true;
	//	return;
	//}

	SceneManager::GetInstance()->Update();

	if (SceneManager::GetInstance()->CompareWithCurrentScene(L"Loading")) // 지금 씬이 로딩씬이라면 true 반환하여 내부로 진입
	{
		Scene* scene = SceneManager::GetInstance()->GetCurrentScene();

		if (((LoadingScene*)scene)->GetIsEndLoading()) // 지금 로딩씬에서 로딩이 끝났다면 true 반환하여 내부로 진입
		{
			if (Input::GetInstance()->GetKeyDown(VK_SPACE))
			{
				SceneManager::GetInstance()->LoadScene(L"Scene1");
			}
		}
	}

	//if (Input::GetInstance()->GetKeyDown('A'))
	//{
	//	SceneManager::GetInstance()->LoadScene(L"Scene1");
	//}
	//if (Input::GetInstance()->GetKeyDown('S'))
	//{
	//	SceneManager::GetInstance()->LoadScene(L"Scene2");
	//}
}

void MainGame::Render(HDC hdc)
{
	//백버퍼의 HDC 가져온다
	HDC backDC = mBackBuffer->GetHDC();
	//HDC 영역을 특정 색으로 밀어버리는 녀석
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		SceneManager::GetInstance()->Render(backDC);

		if (SceneManager::GetInstance()->CompareWithCurrentScene(L"Loading")) // 지금 씬이 로딩씬이라면 true 반환하여 내부로 진입
		{
			Scene* scene = SceneManager::GetInstance()->GetCurrentScene();

			if (((LoadingScene*)scene)->GetIsEndLoading()) // 지금 로딩씬에서 로딩이 끝났다면 true 반환하여 내부로 진입
			{
				// 배경
				//RECT rc = { 0, 0, WINSIZEX, WINSIZEY };
				//HBRUSH newBrush = CreateSolidBrush(RGB(0, 0, 100));
				//HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, newBrush);
				//RenderRect(backDC, rc);
				//SelectObject(backDC, oldBrush);
				//DeleteObject(newBrush);

				wstring str = L"로딩이 완료되었습니다. Space Bar를 누르십시오.";
				TextOut(backDC, WINSIZEX / 2 - 150, WINSIZEY / 2 - 10, str.c_str(), (int)str.length());
			}
		}
		
		RenderTime(backDC);
	}
	//====================================================
	//후면버퍼 내용을 윈도우 창에 고속 복사
	mBackBuffer->Render(hdc, 0, 0);
}

void MainGame::RenderTime(HDC hdc)
{
	float worldTime = Time::GetInstance()->GetWorldTime();
	float deltaTime = Time::GetInstance()->DeltaTime();
	ULONG fps = Time::GetInstance()->GetmFrameRate();
	wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	wstring strDeltaTime = L"DeltaTime : " + to_wstring(deltaTime);
	wstring strFPS = L"FPS : " + to_wstring(fps);

	TextOut(hdc, 10, 10, strWorldTime.c_str(), (int)strWorldTime.length());
	TextOut(hdc, 10, 25, strDeltaTime.c_str(), (int)strDeltaTime.length());
	TextOut(hdc, 10, 40, strFPS.c_str(), (int)strFPS.length());
}

//void MainGame::LoadFromImageFile()
//{
//	ImageManager::GetInstance()->LoadFromFile(L"Bullet", Resources(L"bullet.bmp"), 21, 21, true);
//}
//
//void MainGame::LoadFromSoundFile()
//{
//	SoundPlayer::GetInstance()->LoadFromFile(L"TSound", Resources(L"TestSound.mp3"), false);
//}