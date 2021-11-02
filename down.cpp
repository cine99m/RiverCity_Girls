#include "pch.h"
#include "down.h"
#include "player.h"

HRESULT down::init()
{
	_playerImg =IMAGEMANAGER->findImage("PLAYER_down");
	return S_OK;
}

void down::release()
{
}

void down::update()
{
	state::update();
	_playerImg = IMAGEMANAGER->findImage("PLAYER_down");
}

void down::render()
{
	state::render();
}

void down::stateChange()
{
}

void down::ani()
{
	if (_dir == LEFT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_downL");
		_playerAni->resume();
	}
	else if (_dir == RIGHT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_downR");
		_playerAni->resume();
	}
}

void down::callBk()
{
	if (!_playerAni->isPlay())
	{
		_playerAni->stop();
		_player->setState(new stand);
	}
}
