#include "pch.h"
#include "Scene2.h"

void Scene2::Init()
{
}

void Scene2::Release()
{
}

void Scene2::Update()
{
}

void Scene2::Render(HDC hdc)
{
	RECT rc = { 0, 0, WINSIZEX, WINSIZEY };
	HBRUSH newBrush = CreateSolidBrush(RGB(0, 100, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
	RenderRect(hdc, rc);
	SelectObject(hdc, oldBrush);
	DeleteObject(newBrush);

	wstring str = L"³ª Scene2";
	TextOut(hdc,WINSIZEX / 2, WINSIZEY / 2, str.c_str(), (int)str.length());
}