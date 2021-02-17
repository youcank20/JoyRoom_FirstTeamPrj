#include "pch.h"
#include "UIBossHP.h"

UIBossHP::UIBossHP()
	:GameObject("UIBossHP")
{
}

void UIBossHP::Init()
{
	
}

void UIBossHP::Release()
{
}

void UIBossHP::Update()
{
}

void UIBossHP::Render(HDC hdc)
{
	TextOut(hdc, WINSIZEX / 2, 50, mText.c_str(), mText.length());
}
