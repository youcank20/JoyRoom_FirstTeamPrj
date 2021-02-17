#pragma once
#include "Scene.h"
#include <functional>

class LoadingScene : public Scene
{
	vector<function<void(void)>> mLoadList;
	int mLoadIndex;
	bool mIsEndLoading;

	int mImgMax;
	int mSndMax;
	int mCount;
	bool mImgLoadEnd;
	bool mSndLoadEnd;
	wstring mStrText;
public:
	void AddLoadFunc(const function<void(void)>& func);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	bool GetIsEndLoading()const { return mIsEndLoading; }

	void SetImgMax(int imgMax) { mImgMax = imgMax; }
	void SetSndMax(int sndMax) { mSndMax = sndMax; }

	//void LoadFromImageFile();
	//void LoadFromSoundFile();
};