#include "pch.h"
#include "SceneManager.h"

#include "Scene.h"
#include "LoadingScene.h"

SceneManager::SceneManager()
	:mCurrentScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	SceneIter iter = mSceneList.begin();
	for (; iter != mSceneList.end(); ++iter)
	{
		iter->second->Release();
		SafeDelete(iter->second);
	}
}

void SceneManager::Update()
{
	if (mCurrentScene != nullptr)
		mCurrentScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (mCurrentScene != nullptr)
		mCurrentScene->Render(hdc);
}

void SceneManager::AddScene(const wstring& sceneName, Scene* scene)
{
	SceneIter iter = mSceneList.find(sceneName);
	//이미 해당이름의 데이터가 맵안에 있다
	if (iter != mSceneList.end())
		return;

	mSceneList.insert(make_pair(sceneName, scene));
}

void SceneManager::LoadScene(const wstring& sceneName)
{
	SceneIter iter = mSceneList.find(sceneName);
	//못찾았으면 return (돌아가라)
	if (iter == mSceneList.end())
		return;

	if (mCurrentScene == iter->second)
		return;
	
	Scene* targetScene = iter->second;

	if (mCurrentScene)
		mCurrentScene->Release();

	targetScene->Init();

	mCurrentScene = targetScene;
}

bool SceneManager::CompareWithCurrentScene(const wstring & sceneName)
{
	SceneIter iter = mSceneList.find(sceneName);

	if (mSceneList.end() == iter) // 탐색 실패
		return false;

	if (mCurrentScene == iter->second) // 현재 씬과 일치
		return true;

	return false; // 현재 씬과 불일치
}