#include "pch.h"
#include "stand.h"
#include "player.h"

HRESULT stand::init()
{
    _playerImg = IMAGEMANAGER->findImage("PLAYER_stand");
    return S_OK;
}

void stand::release()
{
}

void stand::update()
{
    state::update();
    _playerImg = IMAGEMANAGER->findImage("PLAYER_stand");
}

void stand::render()
{
    state::render();

}

void stand::stateChange()
{
}

void stand::ani()
{
	if (_dir == LEFT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_standL");
		_playerAni->resume();
	}
	else if (_dir == RIGHT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_standR");
		_playerAni->resume();
	}
}

void stand::callBk()
{
	if (!_playerAni->isPlay())
	{
		_playerAni->stop();
		_player->setState(new idle);
	}
}
