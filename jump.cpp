#include "pch.h"
#include "jump.h"
#include "player.h"

HRESULT jump::init()
{
	_playerImg = IMAGEMANAGER->findImage("PLAYER_jump");


	return S_OK;
}

void jump::release()
{
}

void jump::update()
{
	state::update();
	_playerImg = IMAGEMANAGER->findImage("PLAYER_jump");

	
}

void jump::render()
{
	state::render();
}

void jump::stateChange()
{
	if (_player->getJumpPower() < 0 && !_player->getIsJump())
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) ||
			KEYMANAGER->isStayKeyDown(VK_RIGHT) ||
			KEYMANAGER->isStayKeyDown(VK_UP) ||
			KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_player->setState(new walk);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
		{
			_player->setState(new run);
		}

		else _player->setState(new idle);

	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_player->setState(new jumpAtk);
	}
}

void jump::ani()
{

	_player->setSpeed(3.0f);
	


	if (_dir == LEFT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_jumpL");
		_playerAni->resume();
	}
	else if (_dir == RIGHT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_jumpR");
		_playerAni->resume();
	}

}

