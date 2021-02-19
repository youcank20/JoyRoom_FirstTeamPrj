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
	mDelayTime = 2.f;
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
	TextOut(hdc, 200, 600, mScript.c_str(), (int)mScript.length());
}

IMoveGameObject::IMoveGameObject(GameObject* object, GameObject * target)
{
	mObject = object;
	mTargetX = target->GetX() + target->GetSizeX() + mObject->GetSizeX();
	mTargetY = target->GetY();
	mSpeedX = (mTargetX - mObject->GetX()) * 0.1f * Time::GetInstance()->DeltaTime();
	mSpeedY = (mTargetY - mObject->GetY()) * 0.1f * Time::GetInstance()->DeltaTime();
}

IMoveGameObject::IMoveGameObject(GameObject* object, float x, float y)
{
	mObject = object;
	mTargetX = x;
	mTargetY = y;
	mSpeedX = (mTargetX - mObject->GetX()) * 0.1f * Time::GetInstance()->DeltaTime();
	mSpeedY = (mTargetY - mObject->GetY()) * 0.1f * Time::GetInstance()->DeltaTime();
}

void IMoveGameObject::Start()
{
	mObject->SetIsEventMove(true);
	mObject->SetTargetX(mTargetX);
	mObject->SetTargetY(mTargetY);
}

bool IMoveGameObject::Update()
{
	//mObject->SetX(Math::Lerp(mObject->GetX(), mTargetX, 0.5f * Time::GetInstance()->DeltaTime()));
	//mObject->SetY(Math::Lerp(mObject->GetY(), mTargetY, 0.5f * Time::GetInstance()->DeltaTime()));
	mObject->SetX(mObject->GetX() + mSpeedX);
	mObject->SetY(mObject->GetY() + mSpeedY);

	if (Math::GetDistance(mObject->GetX(), mObject->GetY(), mTargetX, mTargetY) <= 5.0f)
	{
		mObject->SetIsEventMove(false);
		return true;
	}

	return false;
}

void IMoveGameObject::Render(HDC hdc)
{
}
