#include "pch.h"
#include "bossState.h"
#include "boss.h"
#include "player.h"


HRESULT bossState::init()
{
	return S_OK;
}

void bossState::release()
{
}

void bossState::update()
{
	_direction = (int)_boss->getBossDirection();

	animOver();
	anim();
	stateChange();

	//EFFECTMANAGER->update();
}

void bossState::render()
{
	_direction = (int)_boss->getBossDirection();

	if (_direction == (int)DIRECTION::LEFT) _boss->stateRender(_bossAnimL);
	else if (_direction == (int)DIRECTION::RIGHT) _boss->stateRender(_bossAnimR);

	//EFFECTMANAGER->render();

	char str[128];

	sprintf_s(str, "direction : %d", (int)_direction);
	TextOut(getMemDC(), 10, 320, str, strlen(str));

	sprintf_s(str, "frameIdxL : %d", (int)_bossAnimL->getNowPlayIdx());
	TextOut(getMemDC(), 10, 500, str, strlen(str));

	sprintf_s(str, "frameIdxR : %d", (int)_bossAnimR->getNowPlayIdx());
	TextOut(getMemDC(), 10, 530, str, strlen(str));
}

void bossState::stateChange()
{
}

void bossState::anim()
{
}

void bossState::animOver()
{
}

void bossState::hitCheck()
{
	_dx = abs(_player->getShadowX() - _boss->getBossShadowX());
	_dy = abs(_player->getShadowY() - _boss->getBossShadowY());

	if (_player->getShadowRc().top < _boss->getBossShadowRect().bottom && _player->getShadowRc().bottom > _boss->getBossShadowRect().top && !_player->getIsGetHit())
	{
		if ((int)DIRECTION::LEFT == _boss->getBossDirection())
		{
			if (_dx < _boss->getBossWidth() && _boss->getBossX() > _player->getShadowRc().left)
			{
				_player->setIsGetHit(true);
				_player->setPlayerHp(1);
			}
		}
		else if ((int)DIRECTION::RIGHT == _boss->getBossDirection())
		{
			if (_dx < _boss->getBossWidth() && _boss->getBossX() < _player->getShadowRc().right)
			{
				_player->setIsGetHit(true);
				_player->setPlayerHp(1);
			}
		}
	}
}

idleState::idleState()
{
	_bossImg = IMAGEMANAGER->findImage("BOSS_idle");
	_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_idleL");
	_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_idleR");
}

idleState::~idleState()
{
}

// Idle
HRESULT idleState::init()
{
	bossState::init();

	_bossImg = IMAGEMANAGER->findImage("BOSS_idle");

	return S_OK;
}

void idleState::release()
{
}

void idleState::update()
{
	bossState::update();

	_bossImg = IMAGEMANAGER->findImage("BOSS_idle");
}

void idleState::render()
{
	bossState::render();
}

void idleState::stateChange()
{
	if (_boss->getHit())
	{
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setIdle(false);
		_boss->setState(new hitState);
	}
	if (TIMEMANAGER->getWorldTime() >= _boss->getTime() + 2)
	{
		_bAttackPattern = RND->getInt(3);
		
		if (_bAttackPattern == 0)
		{
			_boss->setMove(true);
			_boss->setIdle(false);
			_boss->setTime(TIMEMANAGER->getWorldTime());
			_bossAnimL->stop();
			_bossAnimR->stop();
			_boss->setState(new walkState);
		}
		else if (_bAttackPattern == 1)
		{
			_boss->setMove(false);
			_boss->setIsJump(false);
			_boss->setIdle(false);
			_bossAnimL->stop();
			_bossAnimR->stop();
			_boss->setState(new jumpState);
		}
		else if (_bAttackPattern == 2)
		{
			_boss->setMove(true);
			_boss->setDash(false);
			_boss->setIdle(false);
			_bossAnimL->stop();
			_bossAnimR->stop();
			_boss->setState(new dashState);
		}
	}
}

void idleState::anim()
{
	if (_direction == (int)DIRECTION::LEFT)
	{
		_bossAnimL->resume();
	}

	else if (_direction == (int)DIRECTION::RIGHT)
	{
		_bossAnimR->resume();
	}
	
	_isStart = true;
}

walkState::walkState()
{
	_bossImg = IMAGEMANAGER->findImage("BOSS_walk");
	_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_walkL");
	_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_walkR");
}

walkState::~walkState()
{
}

// Walk
HRESULT walkState::init()
{
	_bossImg = IMAGEMANAGER->findImage("BOSS_walk");

	return S_OK;
}

void walkState::release()
{
}

void walkState::update()
{
	bossState::update();

	_bossImg = IMAGEMANAGER->findImage("BOSS_walk");

}

void walkState::render()
{
	bossState::render();
}

void walkState::stateChange()
{
	if (_boss->getHit())
	{
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setMove(false);
		_boss->setState(new hitState);
	}

	//if (getDistance(_boss->getPlayer()->getShadowX(), _boss->getPlayer()->getShadowY(), _boss->getBossShadowX(), _boss->getBossShadowY()) <= 150)
	if (_boss->getDistanceX() < _boss->getBossShadowWidth()&& _boss->getDistanceY() < _boss->getBossShadowHeight() / 2)
	{
		_boss->setMove(false);
		_boss->setIsAttack(true);
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setState(new attackState);
	}
	else if (TIMEMANAGER->getWorldTime() >= _boss->getTime() + 4)
	{
		_boss->setMove(false);
		_boss->setIdle(true);
		_boss->setTime(TIMEMANAGER->getWorldTime());
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setState(new idleState);
	}
}

void walkState::anim()
{
	if (_direction == (int)DIRECTION::LEFT)
	{
		_bossAnimL->resume();
	}

	if (_direction == (int)DIRECTION::RIGHT)
	{
		_bossAnimR->resume();
	}

	_isStart = true;
}


// Attack
attackState::attackState()
{
	_bossImg = IMAGEMANAGER->findImage("BOSS_slap");
	_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_slapL");
	_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_slapR");
}

attackState::~attackState()
{
}

HRESULT attackState::init()
{
	_bossImg = IMAGEMANAGER->findImage("BOSS_slap");

	return S_OK;
}

void attackState::release()
{
}

void attackState::update()
{
	bossState::update();

	_bossImg = IMAGEMANAGER->findImage("BOSS_slap");

	//animOver();
}

void attackState::render()
{
	bossState::render();
}

void attackState::stateChange()
{
	if (_boss->getHit())
	{
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setMove(false);
		_boss->setIsAttack(false);
		_boss->setState(new hitState);
	}
	if (getDistance(_boss->getPlayer()->getShadowX(), _boss->getPlayer()->getShadowY(), _boss->getBossShadowX(), _boss->getBossShadowY()) > 150 &&
		_boss->getIsAttack() == false)
	{
		_boss->setMove(false);
		_boss->setIsAttack(false);
		_boss->setIdle(true);
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setState(new idleState);
	}
}

void attackState::anim()
{
	if (_direction == (int)DIRECTION::LEFT)
	{
		if (!_bossAnimL->isPlay())
		{
			_bossAnimL->start();
		}
		if (_bossAnimL->isPlay())
		{
			_bossAnimL->resume();
		}
	}

	if (_direction == (int)DIRECTION::RIGHT)
	{
		if (!_bossAnimR->isPlay())
		{
			_bossAnimR->start();
		}
		if (_bossAnimR->isPlay())
		{
			_bossAnimR->resume();
		}
	}

	// 보스가 플레이어를 공격하면
	if ((_bossAnimL->getNowPlayIdx() == 9 || _bossAnimR->getNowPlayIdx() == 9) && !_player->getIsGetHit())
	{
		hitCheck();
	}

	if ((_bossAnimL->getNowPlayIdx() == 9 || _bossAnimR->getNowPlayIdx() == 9) && _player->getIsGetHit())
	{
		if (_boss->getBossDirection() == (int)DIRECTION::LEFT) EFFECTMANAGER->play("EFFECT_bossSmash", _player->getPlayerX() + 40, _player->getPlayerY() - 30);
		else if (_boss->getBossDirection() == (int)DIRECTION::RIGHT) EFFECTMANAGER->play("EFFECT_bossSmash", _player->getPlayerX() - 40, _player->getPlayerY() - 30);
	}

	_isStart = true;
}

void attackState::animOver()
{
	if (!_bossAnimL->isPlay() && !_bossAnimR->isPlay() && _isStart)
	{
		_isStart = false;
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setTime(TIMEMANAGER->getWorldTime());
		_boss->setIsAttack(false);
		_boss->setMove(false);
		_boss->setIdle(true);
		_boss->setState(new idleState);
	}
}


// JumpAttack
jumpState::jumpState()
{
	_bossImg = IMAGEMANAGER->findImage("BOSS_meteor_J");
	_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_jumpL");
	_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_jumpR");
	_bossAnimL->stop();
	_bossAnimR->stop();
}

jumpState::~jumpState()
{
}

HRESULT jumpState::init()
{
	if (!_boss->getIsDrop())
	{
		_bossImg = IMAGEMANAGER->findImage("BOSS_meteor_J");
		_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_jumpL");
		_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_jumpR");
		_bossAnimL->stop();
		_bossAnimR->stop();
	}
	else if (_boss->getIsDrop())
	{
		_bossImg = IMAGEMANAGER->findImage("BOSS_down");
		_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_dropL");
		_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_dropR");
		_bossAnimL->stop();
		_bossAnimR->stop();
	}

	return S_OK;
}

void jumpState::release()
{
}

void jumpState::update()
{
	bossState::update();

	if (!_boss->getIsDrop())
	{
		_bossImg = IMAGEMANAGER->findImage("BOSS_meteor_J");
		_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_jumpL");
		_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_jumpR");
	}
	else if (_boss->getIsDrop())
	{
		_bossImg = IMAGEMANAGER->findImage("BOSS_down");
		_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_dropL");
		_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_dropR");
	}

	//animOver();
}

void jumpState::render()
{
	bossState::render();
}

void jumpState::stateChange()
{
}

void jumpState::hitCheck()
{
	_dx = abs(_player->getShadowX() - _boss->getBossShadowX());
	_dy = abs(_player->getShadowY() - _boss->getBossShadowY());

	if (_dx < _boss->getBossShadowWidth() * 2 && _dy < _boss->getBossShadowHeight() * 2 && !_player->getIsGetHit())
	{
		_player->setIsGetHit(true);
		_player->setPlayerHp(1);
	}

	//
	//_dx = abs(_player->getShadowX() - _boss->getBossShadowX());
	//_dy = abs(_player->getShadowY() - _boss->getBossShadowY());
	//
	//if (_player->getShadowRc().top < _boss->getBossShadowRect().bottom && _player->getShadowRc().bottom > _boss->getBossShadowRect().top && !_boss->getHit())
	//{
	//	if ((int)DIRECTION::LEFT == _boss->getBossDirection())
	//	{
	//		if (_dx < _boss->getBossShadowWidth() && _boss->getBossShadowX() > _player->getShadowRc().left)
	//		{
	//			_player->setIsGetHit(true);
	//		}
	//	}
	//	else if ((int)DIRECTION::RIGHT == _boss->getBossDirection())
	//	{
	//		if (_dx < _boss->getBossShadowWidth() && _boss->getBossShadowX() < _player->getShadowRc().right)
	//		{
	//			_player->setIsGetHit(true);
	//		}
	//	}
	//}
}

void jumpState::anim()
{
	if (!_boss->getIsDrop())
	{
		if (_direction == (int)DIRECTION::LEFT)
		{
			if (!_bossAnimL->isPlay())
			{
				_bossAnimL->stop();
				_bossAnimL->start();
			}
			if (_bossAnimL->isPlay())
			{
				if (_bossAnimL->getNowPlayIdx() == 7) _bossAnimL->pause();
				else _bossAnimL->resume();
			}
		}

		if (_direction == (int)DIRECTION::RIGHT)
		{
			if (!_bossAnimR->isPlay())
			{
				_bossAnimR->stop();
				_bossAnimR->start();
			}
			if (_bossAnimR->isPlay())
			{
				if (_bossAnimR->getNowPlayIdx() == 7) _bossAnimR->pause();
				else _bossAnimR->resume();
			}
		}

		if (!_boss->getIsJump() && (_bossAnimL->getNowPlayIdx() >= 6 || _bossAnimR->getNowPlayIdx() >= 6) &&
			(!_boss->getMove() || !_boss->getFloat()) && !_boss->getGroggy())
		{
			_boss->setIsJump(true);
			//_isStart = true;
		}

		if (_boss->getMove() && TIMEMANAGER->getWorldTime() >= _boss->getTime() + 3) _isStart = true;
		else if (_boss->getIsJump() && _boss->getJumpPower() >= 800 && !_boss->getMove() && !_boss->getFloat()) _isStart = true;
	}

	if (_boss->getIsDrop())
	{
		if (_direction == (int)DIRECTION::LEFT)
		{
			if (!_bossAnimL->isPlay())
			{
				_bossAnimL->stop();
				_bossAnimL->start();
			}
			if (_bossAnimL->isPlay())
			{
				_bossAnimL->resume();
			}
		}

		if (_direction == (int)DIRECTION::RIGHT)
		{
			if (!_bossAnimR->isPlay())
			{
				_bossAnimR->stop();
				_bossAnimR->start();
			}
			if (_bossAnimR->isPlay())
			{
				_bossAnimR->resume();
			}
		}

		if (_boss->getJumpPower() <= 0)
		{
			//_bossAnimL->stop();
			//_bossAnimR->stop();
			hitCheck();
			EFFECTMANAGER->play("EFFECT_bossMeteor", _boss->getBossShadowX(), _boss->getBossY() + 60);
			EFFECTMANAGER->play("EFFECT_bossStand1", _boss->getBossShadowX(), _boss->getBossShadowY());
			_isStart = true;
		}
	}
}

void jumpState::animOver()
{
	// 공중에 떠있을 때
	if (!_bossAnimL->isPlay() && !_bossAnimR->isPlay() && _isStart && _boss->getIsJump())
	{
		_isStart = false;
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setTime(TIMEMANAGER->getWorldTime());
		_boss->setIsAttack(false);
		_boss->setIsJump(false);
		_boss->setMove(true);
		_boss->setFloat(true);
		_boss->setState(new jumpState);
	}
	// 떨어질 때
	else if (!_bossAnimL->isPlay() && !_bossAnimR->isPlay() && _isStart && _boss->getMove())
	{
		_isStart = false;
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setIsAttack(false);
		_boss->setIsJump(false);
		_boss->setMove(false);
		_boss->setIsDrop(true);
		_boss->setFloat(false);
		_boss->setState(new jumpState);
	}
	// 떨어지고 평상시로 돌아갈 때
	else if (!_bossAnimL->isPlay() && !_bossAnimR->isPlay() && _isStart && _boss->getIsDrop())
	{
		_isStart = false;
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setTime(TIMEMANAGER->getWorldTime());
		_boss->setIsAttack(false);
		_boss->setIsJump(false);
		_boss->setMove(false);
		_boss->setIsDrop(false);
		_boss->setFloat(false);
		_boss->setIdle(false);
		_boss->setGroggy(true);
		_boss->setState(new groggyState);
	}
}

// dash
dashState::dashState()
{
		_bossImg = IMAGEMANAGER->findImage("BOSS_dash");
		_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_dashStartL");
		_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_dashStartR");
}

dashState::~dashState()
{

}

HRESULT dashState::init()
{
	if (!_boss->getDash())
	{
		_bossImg = IMAGEMANAGER->findImage("BOSS_dash");
		_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_dashStartL");
		_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_dashStartR");
	}
	else if (_boss->getDash())
	{
		_bossImg = IMAGEMANAGER->findImage("BOSS_dash");
		_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_dashL");
		_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_dashR");
	}

	return S_OK;
}

void dashState::release()
{
}

void dashState::update()
{
	bossState::update();

	if (!_boss->getDash())
	{
		_bossImg = IMAGEMANAGER->findImage("BOSS_dash");
		_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_dashStartL");
		_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_dashStartR");
	}
	else if (_boss->getDash())
	{
		_bossImg = IMAGEMANAGER->findImage("BOSS_dash");
		_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_dashL");
		_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_dashR");
	}
}

void dashState::render()
{
	bossState::render();
}

void dashState::stateChange()
{
	if (_boss->getHit())
	{
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setMove(false);
		_boss->setDash(false);
		_boss->setState(new hitState);
	}
	//if (getDistance(_boss->getPlayer()->getShadowX(), _boss->getPlayer()->getShadowY(), _boss->getBossShadowX(), _boss->getBossShadowY()) <= 50 ||
	//	TIMEMANAGER->getWorldTime() >= _boss->getTime() + 5)
	if (_boss->getDistanceX() < _boss->getBossShadowWidth() && _boss->getDistanceY() < _boss->getBossShadowHeight() / 2 && _boss->getDash())
	{
		hitCheck();
		EFFECTMANAGER->play("EFFECT_dashAttack", _player->getPlayerX(), _player->getPlayerY());
		_boss->setMove(false);
		_boss->setDash(false);
		_boss->setTime(TIMEMANAGER->getWorldTime());
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setState(new idleState);
	}

	if (TIMEMANAGER->getWorldTime() >= _boss->getTime() + 5)
	{
		_boss->setMove(false);
		_boss->setDash(false);
		_boss->setTime(TIMEMANAGER->getWorldTime());
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setState(new idleState);
	}
}

void dashState::anim()
{
	static int count = 0;

	if (_direction == (int)DIRECTION::LEFT)
	{
		if (!_bossAnimL->isPlay())
		{
			_bossAnimL->start();
		}
		if (_bossAnimL->isPlay())
		{
			_bossAnimL->resume();
		}
		
		if (count % 10 == 0)
		{
			EFFECTMANAGER->play("EFFECT_runL", _boss->getBossShadowX() + _boss->getBossWidth() / 2, _boss->getBossShadowY() - 50);
		}
	}

	if (_direction == (int)DIRECTION::RIGHT)
	{
		if (!_bossAnimR->isPlay())
		{
			_bossAnimR->start();
		}
		if (_bossAnimR->isPlay())
		{
			_bossAnimR->resume();
		}

		if (count % 10 == 0)
		{
			EFFECTMANAGER->play("EFFECT_runR", _boss->getBossShadowX() - _boss->getBossWidth() / 2, _boss->getBossShadowY() - 50);
		}
	}
	count++;

	_isStart = true;
}

void dashState::animOver()
{
	if (!_bossAnimL->isPlay() && !_bossAnimR->isPlay() && _isStart)
	{
		_isStart = false;
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setTime(TIMEMANAGER->getWorldTime());
		_boss->setMove(true);
		_boss->setDash(true);
		_boss->setState(new dashState);
	}
}

// Sit
HRESULT sitState::init()
{
	return S_OK;
}

void sitState::release()
{
}

void sitState::update()
{
	bossState::update();
}

void sitState::render()
{
	bossState::render();
}


// Groggy
groggyState::groggyState()
{
	_bossImg = IMAGEMANAGER->findImage("BOSS_meteor_G");
	_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_gHitL");
	_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_gHitR");
}

groggyState::~groggyState()
{
}

HRESULT groggyState::init()
{
	_bossImg = IMAGEMANAGER->findImage("BOSS_meteor_G");
	_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_gHitL");
	_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_gHitR");

	return S_OK;
}

void groggyState::release()
{
}

void groggyState::update()
{
	bossState::update();

	_bossImg = IMAGEMANAGER->findImage("BOSS_meteor_G");
	_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_gHitL");
	_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_gHitR");
}

void groggyState::render()
{
	bossState::render();
}

void groggyState::stateChange()
{
	//if (_boss->getHit())
	//{
	//	_bossAnimL->stop();
	//	_bossAnimR->stop();
	//	_boss->setIdle(false);
	//	_boss->setMove(false);
	//	_boss->setDash(false);
	//	_boss->setGroggy(false);
	//	_boss->setState(new hitState);
	//}
	if (TIMEMANAGER->getWorldTime() >= _boss->getTime() + 2)
	{
		_boss->setMove(false);
		_boss->setDash(false);
		_boss->setGroggy(false);
		_boss->setIdle(true);
		_boss->setTime(TIMEMANAGER->getWorldTime());
		_bossAnimL->stop();
		_bossAnimR->stop();
		_boss->setState(new idleState);
	}
}

void groggyState::anim()
{
	if (_direction == (int)DIRECTION::LEFT)
	{
		if (!_bossAnimL->isPlay())
		{
			_bossAnimL->start();
		}
		if (_bossAnimL->isPlay())
		{
			_bossAnimL->resume();
		}
	}

	if (_direction == (int)DIRECTION::RIGHT)
	{
		if (!_bossAnimR->isPlay())
		{
			_bossAnimR->start();
		}
		if (_bossAnimR->isPlay())
		{
			_bossAnimR->resume();
		}
	}

	_isStart = true;
}

void groggyState::animOver()
{
}

// hit
hitState::hitState()
{
	_bossImg = IMAGEMANAGER->findImage("BOSS_attacked3");
	_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_hitL");
	_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_hitR");
	_bossAnimL->stop();
	_bossAnimR->stop();
	//_boss->setHit(false);
}

hitState::~hitState()
{

}

HRESULT hitState::init()
{
	_bossImg = IMAGEMANAGER->findImage("BOSS_attacked3");
	_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_hitL");
	_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_hitR");
	_bossAnimL->stop();
	_bossAnimR->stop();
	//_boss->setHit(false);

	return S_OK;
}

void hitState::release()
{
}

void hitState::update()
{
	bossState::update();

	_bossImg = IMAGEMANAGER->findImage("BOSS_attacked3");
	_bossAnimL = KEYANIMANAGER->findAnimation("BOSS_hitL");
	_bossAnimR = KEYANIMANAGER->findAnimation("BOSS_hitR");
}

void hitState::render()
{
	bossState::render();
}

void hitState::stateChange()
{
}

void hitState::anim()
{
	if (_direction == (int)DIRECTION::LEFT)
	{
		if (!_bossAnimL->isPlay())
		{
			_bossAnimL->stop();
			_bossAnimL->start();
		}
		if (_bossAnimL->isPlay())
		{
			_bossAnimL->resume();
		}
	}

	if (_direction == (int)DIRECTION::RIGHT)
	{
		if (!_bossAnimR->isPlay())
		{
			_bossAnimR->stop();
			_bossAnimR->start();
		}
		if (_bossAnimR->isPlay())
		{
			_bossAnimR->resume();
		}
	}

	_isStart = true;
}

void hitState::animOver()
{
	if (!_bossAnimL->isPlay() && !_bossAnimR->isPlay() && _isStart)
	{
		_bossAnimL->stop();
		_bossAnimR->stop();
		_isStart = true;
		_boss->setMove(false);
		_boss->setDash(false);
		_boss->setGroggy(false);
		_boss->setIdle(true);
		_boss->setHit(false);
		//_boss->setTime(TIMEMANAGER->getWorldTime());
		_boss->setState(new idleState);
	}
}

// Lose
HRESULT loseState::init()
{
	return S_OK;
}

void loseState::release()
{
}

void loseState::update()
{
	bossState::update();
}

void loseState::render()
{
	bossState::render();
}