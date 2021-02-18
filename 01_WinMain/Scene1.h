#pragma once
#include "Scene.h"

class Image;
class Scene1 : public Scene
{
	Image* mBackground;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

