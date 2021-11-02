#include "pch.h"
#include "grab.h"
#include "player.h"

HRESULT grab::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_grab");
	return S_OK;
}

void grab::release()
{
}

void grab::update()
{
	state::update();
	_playerImg = IMAGEMANAGER->findImage("PLAYER_grab");
}

void grab::render()
{
	state::render();
}

void grab::stateChange()
{
}

void grab::ani()
{
	if (_dir == LEFT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_grabL");
		_playerAni->resume();
	}
	else if (_dir == RIGHT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_grabR");
		_playerAni->resume();
	}
}

void grab::callBk()
{

}
