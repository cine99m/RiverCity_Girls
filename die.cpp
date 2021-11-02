#include "pch.h"
#include "die.h"
#include "player.h"

HRESULT die::init()
{
    _playerImg = IMAGEMANAGER->findImage("PLAYER_dead");

	_playerAni = KEYANIMANAGER->findAnimation("PLAYER_dead");
	return S_OK;
}

void die::release()
{
}

void die::update()
{
    state::update();

    _playerImg = IMAGEMANAGER->findImage("PLAYER_dead");
}

void die::render()
{
	state::render();
}

void die::stateChange()
{
}

void die::ani()
{
	if (_dir == LEFT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_dieL");
		_playerAni->resume();
	}
	else if (_dir == RIGHT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_dieR");
		_playerAni->resume();
	}
}
