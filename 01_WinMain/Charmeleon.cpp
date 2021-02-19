#include "pch.h"
#include "Charmeleon.h"
#include "Animation.h"
#include "Image.h"
#include "Player.h"
#include "Camera.h"

Charmeleon::Charmeleon(const string & name, float x, float y, Player * player)
	:Monster(name, x, y)
{
	mPlayer = player;
}

void Charmeleon::Init()
{
}

void Charmeleon::Release()
{
}

void Charmeleon::Update()
{
}

void Charmeleon::Render(HDC hdc)
{
}