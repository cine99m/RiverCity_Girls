#include "pch.h"
#include "jumpAtk.h"
#include "player.h"

HRESULT jumpAtk::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_jumpAttack");
	return S_OK;
}

void jumpAtk::release()
{
}

void jumpAtk::update()
{
	state::update();
	_playerImg = IMAGEMANAGER->findImage("PLAYER_jumpAttack");
	callBk();
}

void jumpAtk::render()
{
	state::render();
}

void jumpAtk::stateChange()
{
}

void jumpAtk::ani()
{
	if (_dir == LEFT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_jumpAttackL");
		_playerAni->resume();
	}
	else if (_dir == RIGHT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_jumpAttackR");
		_playerAni->resume();
	}
}

void jumpAtk::callBk()
{
	if (!_playerAni->isPlay())
	{
		_playerAni->stop();
		_player->setState(new idle);
	}
}
