#include "pch.h"
#include "hit.h"
#include "player.h"

HRESULT hit::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_hit");
	return S_OK;
}

void hit::release()
{
}

void hit::update()
{
	state::update();
    if (_player->getPlayerHp() < 1)
    {
        _player->setState(new die);
    }
    _playerImg = IMAGEMANAGER->findImage("PLAYER_hit");
    callBk();
}

void hit::render()
{
	state::render();
}

void hit::stateChange()
{
}

void hit::ani()
{
    if (_dir == LEFT)
    {
        _playerAni = KEYANIMANAGER->findAnimation("PLAYER_hitL");
        _playerAni->resume();
    }
    if (_dir == RIGHT)
    {
        _playerAni = KEYANIMANAGER->findAnimation("PLAYER_hitR");
        _playerAni->resume();
    }
}

void hit::callBk()
{
    if (!_playerAni->isPlay())
    {
        _playerAni->stop();
        _player->setIsGetHit(false);
        _player->setState(new idle);
    }
}
