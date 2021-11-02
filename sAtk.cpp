#include "pch.h"
#include "sAtk.h"
#include "player.h"

HRESULT sAtk::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_sAttack");
	return S_OK;
}

void sAtk::release()
{
}

void sAtk::update()
{
	state::update();
	_playerImg = IMAGEMANAGER->findImage("PLAYER_sAttack");
	callBk();
}

void sAtk::render()
{
	state::render();
}

void sAtk::stateChange()
{
}

void sAtk::ani()
{
	if (_dir == LEFT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_sAttackL");
		_playerAni->resume();
	}
	else if (_dir == RIGHT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_sAttackR");
		_playerAni->resume();
	}
}

void sAtk::callBk()
{
	if (!_playerAni->isPlay())
	{
		_playerAni->stop();
		_player->setState(new idle);
	}
}
