#include "pch.h"
#include "GameEvent.h"

#include "Camera.h"
IChangeCameraTargetEvent::IChangeCameraTargetEvent(GameObject * target)
{
	mTarget = target;
}

void IChangeCameraTargetEvent::Start()
{
	CameraManager::GetInstance()->GetMainCamera()->SetTarget(mTarget);
}

bool IChangeCameraTargetEvent::Update()
{
	float x = CameraManager::GetInstance()->GetMainCamera()->GetX();
	float y = CameraManager::GetInstance()->GetMainCamera()->GetY();

	if (Math::GetDistance(x, y, mTarget->GetX(), mTarget->GetY()) <= 5.0f)
	{
		return true;
	}

	return false;
}

void IChangeCameraTargetEvent::Render(HDC hdc)
{
}

IDelayEvent::IDelayEvent(float delayTime)
{
	mDelayTime = delayTime;
	mCurrentTime = 0.f;
}

void IDelayEvent::Start()
{
}

bool IDelayEvent::Update()
{
	mCurrentTime += Time::GetInstance()->DeltaTime();

	if (mCurrentTime >= mDelayTime)
	{
		return true;
	}

	return false;
}

void IDelayEvent::Render(HDC hdc)
{
}

IScriptEvent::IScriptEvent(wstring image, wstring script)
{
	mImage = IMAGEMANAGER->FindImage(image);
	mScript = script;
	mDelayTime = 3.f;
	mCurrentTime = 0.f;
}

void IScriptEvent::Start()
{
}

bool IScriptEvent::Update()
{
	mCurrentTime += Time::GetInstance()->DeltaTime();

	if (mCurrentTime >= mDelayTime)
	{
		mScript = L"";
		return true;
	}

	return false;
}

void IScriptEvent::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->Render(hdc, mImage
		, 10 + CameraManager::GetInstance()->GetMainCamera()->GetRect().left
		, 550 + CameraManager::GetInstance()->GetMainCamera()->GetRect().top);
	TextOut(hdc, 200, 600, mScript.c_str(), mScript.length());
}
