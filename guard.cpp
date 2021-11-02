#include "pch.h"
#include "guard.h"
#include "player.h"

HRESULT guard::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_guard");
	return S_OK;
}

void guard::release()
{

}

void guard::update()
{
	state::update();
	_playerImg = IMAGEMANAGER->findImage("PLAYER_guard");
}

void guard::render()
{
	state::render();
}

void guard::stateChange()
{
    if (KEYMANAGER->isOnceKeyUp('F'))
    {
        _player->setState(new idle);
        _player->setIsGuarding(false);
    }
}

void guard::ani()
{
    if (_dir == LEFT)
    {
        _playerAni = KEYANIMANAGER->findAnimation("PLAYER_guardL");
        _playerAni->resume();
    }
    if (_dir == RIGHT)
    {
        _playerAni = KEYANIMANAGER->findAnimation("PLAYER_guardR");
        _playerAni->resume();
    }
}

void guard::callBk()
{
}
