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
	wstring str = L"���� ���� ��1�̴� ��! ���̹� ���� ���ٳ�!";
	TextOut(hdc, WINSIZEX / 2 - 150, WINSIZEY / 2 - 10, str.c_str(), (int)str.length());
}