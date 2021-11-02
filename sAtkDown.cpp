#include "pch.h"
#include "sAtkDown.h"
#include "player.h"

HRESULT sAtkDown::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_sAttackDown");
	return S_OK;
}

void sAtkDown::release()
{
}

void sAtkDown::update()
{
	state::update();
	_playerImg = IMAGEMANAGER->findImage("PLAYER_sAttackDown");
}

void sAtkDown::render()
{
	state::render();
	callBk();
}

void sAtkDown::stateChange()
{
}

void sAtkDown::ani()
{
	if (_dir == LEFT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_sAttackDownL");
		_playerAni->resume();
	}
	else if (_dir == RIGHT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_sAttackDownR");
		_playerAni->resume();
	}
}

void sAtkDown::callBk()
{
	if (!_playerAni->isPlay())
	{
		_playerAni->stop();
		_player->setState(new idle);
	}
}
