#include "pch.h"
#include "idle.h"
#include "player.h"

HRESULT idle::init()
{
	state::init();

	_playerImg = IMAGEMANAGER->findImage("PLAYER_idle");
	_playerAni = KEYANIMANAGER->findAnimation("PLAYER_idleL");

	return S_OK;
}

void idle::release()
{
}

void idle::update()
{
	state::update();
	if (_player->getPlayerHp() < 1)
	{
		_player->setState(new die);
	}
	_playerImg = IMAGEMANAGER->findImage("PLAYER_idle");

}

void idle::render()
{
	state::render();


}

void idle::stateChange()
{
	if (_player->getIsGetHit())
	{
		//_playerAni->stop();
		_player->setState(new hit);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_player->setState(new jump);
		_player->setJumpPower(20.0f);
	}
	// 이동키를 눌렀을 땐 플레이어 상태를 걷는 상태로 정의한다
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)  ||
		KEYMANAGER->isOnceKeyDown(VK_RIGHT) ||
		KEYMANAGER->isOnceKeyDown(VK_UP)	||
		KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_player->setState(new walk);
	}
 
	else if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_player->setIsAttacking(true);
		SOUNDMANAGER->play("PLAYER_combo1", 1.0f);
		_player->setState(new atk);
		hitCheck();
	}
	else if (KEYMANAGER->isStayKeyDown('F'))
	{
		_player->setState(new guard);
		_player->setIsGuarding(true);
		
	}
	else if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_player->setState(new sAtk);
	}
	else if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_player->setState(new sAtkDown);
	}


	if (_player->getIsGetHit())
	{
		_player->setState(new hit);
	}


}

void idle::ani()
{
	_player->setSpeed(0.0f);

	if (_dir == LEFT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_idleL");
		_playerAni->resume();
	}
	if (_dir == RIGHT)
	{
		_playerAni = KEYANIMANAGER->findAnimation("PLAYER_idleR");
		_playerAni->resume();
	}
}

