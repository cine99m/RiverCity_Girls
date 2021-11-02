#include "pch.h"
#include "stomp.h"
#include "player.h"

HRESULT stomp::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_stomp");
	return S_OK;
}

void stomp::release()
{
}

void stomp::update()
{
	state::update();
	_playerImg = IMAGEMANAGER->findImage("PLAYER_stomp");
}

void stomp::render()
{
	state::render();
}

void stomp::stateChange()
{
}

void stomp::ani()
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

void stomp::callBk()
{
	if (!_playerAni->isPlay())
	{
		_playerAni->stop();
		_player->setState(new idle);
	}
}
