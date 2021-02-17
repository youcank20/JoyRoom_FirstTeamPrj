#pragma once
#include "GameObject.h"
class UIBossHP : public GameObject
{
	wstring mText;
public:
	UIBossHP();
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetText(const wstring& text) { mText = text; }
};

