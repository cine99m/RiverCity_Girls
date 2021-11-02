#include "pch.h"
#include "dashSAttack.h"
#include "player.h"

HRESULT dashSAttack::init()
{
    _playerImg = IMAGEMANAGER->findImage("PLAYER_dashSAttack");
    return S_OK;
}

void dashSAttack::release()
{
}

void dashSAttack::update()
{
    state::update();
    if (_player->getPlayerHp() < 1)
    {
        _player->setState(new die);
    }
    callBk();
    _playerImg = IMAGEMANAGER->findImage("PLAYER_dashSAttack");
}

void dashSAttack::render()
{
    state::render();
}

void dashSAttack::stateChange()
{
}

void dashSAttack::ani()
{
    _player->setSpeed(6.0f);

    if (_dir == LEFT)
    {
        _playerAni = KEYANIMANAGER->findAnimation("PLAYER_dashSAttackL");
        _playerAni->resume();
    }
    if (_dir == RIGHT)
    {
        _playerAni = KEYANIMANAGER->findAnimation("PLAYER_dashSAttackR");
        _playerAni->resume();
    }
}

void dashSAttack::callBk()
{

    if (!_playerAni->isPlay())
    {
        _playerAni->stop();
        _player->setState(new idle);

    }
}
