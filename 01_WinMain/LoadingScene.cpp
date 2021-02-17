#include "pch.h"
#include "LoadingScene.h"

void LoadingScene::AddLoadFunc(const function<void(void)>& func)
{
	mLoadList.push_back(func);
}

void LoadingScene::Init()
{
	mLoadIndex = 0;
	mIsEndLoading = false;

	//AddLoadFunc([]() { LoadFromImageFile; });
	//AddLoadFunc([]() { LoadFromSoundFile; });
	//AddLoadFunc([]() { ImageManager::GetInstance()->LoadFromFile(L"Bullet", Resources(L"bullet.bmp"), 21, 21, true); }); // 이건 됨

	mStrText = L"";
	mCount = 0;
	mImgLoadEnd = false;
	mSndLoadEnd = false;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
	if (mLoadIndex >= mLoadList.size())
	{
		mIsEndLoading = true;
		return;
	}

	function<void(void)> func = mLoadList[mLoadIndex];
	func();
	mLoadIndex++;
	++mCount;

	if (!mImgLoadEnd)
	{
		if (mImgMax <= mCount)
		{
			mImgLoadEnd = true;
			mCount = 0;
		}
	}
	else if (!mSndLoadEnd)
	{
		if (mSndMax <= mCount)
		{
			mSndLoadEnd = true;
		}
	}
}

void LoadingScene::Render(HDC hdc)
{
	RECT loadingBorderRc = { 98, WINSIZEY / 2 - 52, WINSIZEX - 98, WINSIZEY / 2 + 52 };
	RECT loadingBarRc = { 100, WINSIZEY / 2 - 50, (WINSIZEX - 200) * mLoadIndex / (int)mLoadList.size() + 100, WINSIZEY / 2 + 50 };

	RenderRect(hdc, loadingBorderRc);

	HBRUSH newBrush = CreateSolidBrush(RGB(0, 0, 100));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
	RenderRect(hdc, loadingBarRc);
	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);

	if (!mImgLoadEnd)
		mStrText = L"이미지 로딩 중입니다. (이미지 파일 " + to_wstring(mCount) + L" / " + to_wstring(mImgMax) + 
		L", 총 " + to_wstring(mLoadIndex) + L" / " + to_wstring(mLoadList.size()) + L", 진행률: " + to_wstring((int)(100 * mLoadIndex / mLoadList.size())) + L"%)";
	else
		mStrText = L"사운드 로딩 중입니다. (사운드 파일 " + to_wstring(mCount) + L" / " + to_wstring(mSndMax) +
		L", 총 " + to_wstring(mLoadIndex) + L" / " + to_wstring(mLoadList.size()) + L", 진행률: " + to_wstring((int)(100 * mLoadIndex / mLoadList.size())) + L"%)";

	if(!mSndLoadEnd || !mImgLoadEnd)
		TextOut(hdc, WINSIZEX / 2 - 250, WINSIZEY / 2 - 10, mStrText.c_str(), (int)mStrText.length());
}

//void LoadingScene::LoadFromImageFile()
//{
//	ImageManager::GetInstance()->LoadFromFile(L"Bullet", Resources(L"bullet.bmp"), 21, 21, true);
//}
//
//void LoadingScene::LoadFromSoundFile()
//{
//	SoundPlayer::GetInstance()->LoadFromFile(L"TSound", Resources(L"TestSound.mp3"), false);
//}