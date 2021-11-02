#include "pch.h"
#include "wait.h"
#include "player.h"

HRESULT wait::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_down");
	return S_OK;
}

void wait::release()
{
}

void wait::update()
{
	state::update();
	_playerImg = IMAGEMANAGER->findImage("PLAYER_down");
}

void wait::render()
{
	state::render();
}

void wait::stateChange()
{
}

void wait::ani()
{
}

void wait::callBk()
{
}
