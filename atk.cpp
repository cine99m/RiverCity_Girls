#include "pch.h"
#include "atk.h"
#include "player.h"
#include "boss.h"

HRESULT atk::init()
{

	return S_OK;
}

void atk::release()
{
}

void atk::update()
{
	state::update();
	if (_player->getPlayerHp() < 1)
	{
		_player->setState(new die);
	}
	callBk();
	if (KEYMANAGER->isOnceKeyDown('Q') && _attackIdx < 2)
	{
		_player->setIsAttacking(true);
		
		if (_player->getIsAttacking() && !_boss->getHit())
		{
			hitCheck();
			_boss->setBossHp(10);
		}

		if (_playerAni->getNowPlayIdx() >= _playerImg->getMaxFrameX()-2)
		{
			_playerAni->stop();
			_attackIdx++;

			switch (_attackIdx)
			{	
			case 0:

				break;
			case 1:
				SOUNDMANAGER->stop("PLAYER_combo1");
				SOUNDMANAGER->play("PLAYER_combo2", 1.0f);
				break;
			case 2:
				SOUNDMANAGER->stop("PLAYER_combo2");
				SOUNDMANAGER->play("PLAYER_combo3", 1.0f);
				break;

			default:

				break;
			}
		}

	}

	switch (_attackIdx)
	{
	case 0:
		_playerImg = IMAGEMANAGER->findImage("PLAYER_comboAttack1");
	
		break;
	case 1:
		_playerImg = IMAGEMANAGER->findImage("PLAYER_comboAttack2");

		break;
	case 2:
		_playerImg = IMAGEMANAGER->findImage("PLAYER_comboAttack3");
	
		break;
	default:
		break;
	}
	if (_player->getIsGetHit())
	{
		_player->setState(new hit);
	}
}

void atk::render()
{
	state::render();

	char str[128];
	sprintf_s(str, "attcount:%d", _attackIdx);
	TextOut(getMemDC(), 20, 20, str, strlen(str));
}

void atk::stateChange()
{
}

void atk::ani()
{

	_player->setSpeed(0);

	if (_dir == LEFT)
	{
		switch (_attackIdx)
		{
		case 0:
			_playerAni = KEYANIMANAGER->findAnimation("PLAYER_1atkL");
		
			break;
		case 1:
			_playerAni = KEYANIMANAGER->findAnimation("PLAYER_2atkL");

			break;
		case 2:
			_playerAni = KEYANIMANAGER->findAnimation("PLAYER_3atkL");

			break;

		}

	}
	else if (_dir == RIGHT)
	{
		switch (_attackIdx)
		{
		case 0:
			_playerAni = KEYANIMANAGER->findAnimation("PLAYER_1atkR");
			break;
		case 1:
			_playerAni = KEYANIMANAGER->findAnimation("PLAYER_2atkR");
			break;
		case 2:
			_playerAni = KEYANIMANAGER->findAnimation("PLAYER_3atkR");
			break;


		}
	}

	_playerAni->resume();
}

void atk::callBk()
{
	if (!_playerAni->isPlay())
	{
		_playerAni->stop();
		_player->setIsAttacking(false);
		_player->setState(new idle);
		_player->update();
	}

}

//void atk::hitCheck()
//{
//	_dx = abs(_player->getShadowX() - _boss->getBossShadowX());
//	_dy = abs(_player->getShadowY() - _boss->getBossShadowY());
//
//	if (_player->getShadowRc().top < _boss->getBossShadowRect().bottom && _player->getShadowRc().bottom > _boss->getBossShadowRect().top && !_boss->getHit())
//	{
//		if (LEFT == _player->getDir())
//		{
//			if (_dx < _player->getWidth() && _player->getShadowX() > _boss->getBossShadowRect().left)
//			{
//				_boss->setHit(true);
//			}
//		}
//		else if (RIGHT == _player->getDir())
//		{
//			if (_dx < _player->getWidth() && _player->getShadowX() < _boss->getBossShadowRect().right)
//			{
//				_boss->setHit(true);
//			}
//		}
//	}
//
//	//if (abs(_player->getShadowX() - _boss->getBossShadowX()) < _player->getShadowRc().right - _player->getShadowRc().left && 
//	//	abs(_player->getShadowY() - _boss->getBossShadowY()) < _player->getShadowRc().bottom - _player->getShadowRc().top &&
//	//	!_boss->getHit())
//	//{
//	//	_boss->setHit(true);
//	//}
//}

