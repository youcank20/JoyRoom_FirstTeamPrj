#include "pch.h"
#include "Scene1.h"

void Scene1::Init()
{
}

void Scene1::Release()
{
}

void Scene1::Update()
{
}

void Scene1::Render(HDC hdc)
{
	wstring str = L"³ª Scene1";
	TextOut(hdc, WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}