#include "pch.h"
#include "dashAttack.h"
#include "player.h"

HRESULT dashAttack::init()
{
    _playerImg = IMAGEMANAGER->findImage("PLAYER_dashAttack");
    return S_OK;
}

void dashAttack::release()
{
}

void dashAttack::update()
{
    state::update();
    if (_player->getPlayerHp() < 1)
    {
        _player->setState(new die);
    }
    callBk();
    _playerImg = IMAGEMANAGER->findImage("PLAYER_dashAttack");
}

void dashAttack::render()
{
    state::render();
}

void dashAttack::stateChange()
{

}

void dashAttack::ani()
{
    _player->setSpeed(6.0f);

    if (_dir == LEFT)
    {
        _playerAni = KEYANIMANAGER->findAnimation("PLAYER_dashAttackL");
        _playerAni->resume();
    }
    if (_dir == RIGHT)
    {
        _playerAni = KEYANIMANAGER->findAnimation("PLAYER_dashAttackR");
        _playerAni->resume();
    }
}

void dashAttack::callBk()
{

    if (!_playerAni->isPlay())
    {
        _playerAni->stop();
        _player->setState(new idle);

    }
}
