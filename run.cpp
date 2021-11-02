#include "pch.h"
#include "run.h"
#include "player.h"

HRESULT run::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_run");
	return S_OK;
}

void run::release()
{
}

void run::update()
{
	state::update();
    if (_player->getPlayerHp() < 1)
    {
        _player->setState(new die);
    }

	_playerImg = IMAGEMANAGER->findImage("PLAYER_run");
}

void run::render()
{
	state::render();
}

void run::stateChange()
{

    if (_player->getIsGetHit())
    {
       // _playerAni->stop();
        _player->setState(new hit);
    }
    if (KEYMANAGER->isOnceKeyDown('Q'))
    {
        SOUNDMANAGER->play("PLAYER_combo1", 1.0f);
       _player->setState(new atk);
    }
    if (KEYMANAGER->isOnceKeyDown('W'))
    {
        _player->setState(new dashAttack);
    }
    if (KEYMANAGER->isOnceKeyDown('E'))
    {
        _player->setState(new dashSAttack);
    }


    if (!KEYMANAGER->isStayKeyDown(VK_LSHIFT))
    {
        _player->setState(new walk);
    }
    if (!KEYMANAGER->isStayKeyDown(VK_LEFT)     &&
        !KEYMANAGER->isStayKeyDown(VK_RIGHT)    &&
        !KEYMANAGER->isStayKeyDown(VK_UP)       &&
        !KEYMANAGER->isStayKeyDown(VK_DOWN))
    {
        _player->setState(new idle);
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        _player->setJumpPower(20.0f);
        _player->setState(new jump);
    }
    if (_player->getIsGetHit())
    {
        _player->setState(new hit);
    }
}

void run::ani()
{
    _player->setSpeed(8.0f);


    if (_dir == LEFT)
    {
        _playerAni = KEYANIMANAGER->findAnimation("PLAYER_runL");
        _playerAni->resume();
    }
    else if (_dir == RIGHT)
    {
        _playerAni = KEYANIMANAGER->findAnimation("PLAYER_runR");
        _playerAni->resume();
    }
}
