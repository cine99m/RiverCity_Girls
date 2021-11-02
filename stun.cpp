#include "pch.h"
#include "stun.h"
#include "player.h"

HRESULT stun::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_stun");
	return S_OK;
}

void stun::release()
{
}

void stun::update()
{
	state::update();
	_playerImg = IMAGEMANAGER->findImage("PLAYER_stun");
}

void stun::render()
{
	state::render();
	
}

void stun::stateChange()
{
}

void stun::ani()
{
	if (_dir == LEFT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_stompL");
		_playerAni->resume();
	}
	else if (_dir == RIGHT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_stompR");
		_playerAni->resume();
	}
}

void stun::callBk()
{
	if (!_playerAni->isPlay())
	{
		_playerAni->stop();
		_player->setState(new idle);
	}
}
