#include "pch.h"
#include "enemyState.h"
#include "enemy.h"


#pragma region 초기

enemyState::enemyState()
{
}

enemyState::~enemyState()
{
}

HRESULT enemyState::init()
{
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_idle");
	
	_isHitCheck = false;
	return S_OK;
}

void enemyState::release()
{
}

void enemyState::update()
{
	_enemyDir = _enemy->getDir(); 
	
	callBk();
	enemyAni();
	
	enemyStateChange();

	
}

void enemyState::render()
{
	_enemy->enemyStateRender(_enemyAni);
}

void enemyState::callBk()
{
}

#pragma endregion
//////////////////////////////////////////////  기   본  ///////////////////////////////////////////////////////////
#pragma region 기본 상태

enemyIdle::enemyIdle()
{
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_idle");


}

enemyIdle::~enemyIdle()
{
}

HRESULT enemyIdle::init()
{
	enemyState::init();

	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_idle");
	_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_idleL");
	_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_idleR");
	
	
	return S_OK;
}

void enemyIdle::release()
{
}

void enemyIdle::update()
{
	enemyState::update();

	_enemy->setIsEnemyIdle(true);						//기본 상태라서 기본임
	_enemy->setIsEnemyAttack(false);					//기본 상태라서 공격을 안함
	_enemy->setIsEnemyChase(false);						//기본 상태라서 추적을 안함
	_enemy->setIsEnemyWaitAttack(false);				//다가가서 어택하기전 대기
	_enemy->setIsEnemyHurt(false);						//기본 상태라 맞질 않음
	_enemy->setIsEnemyRun(false);						//달리기 상태 아님
	_enemy->setIsEnemyDie(false);						//죽은 상태 아님

	_enemy->setEnemyCount(_enemy->getEnemyCount() + 1);	//기본 상태에 어택 카운트가 올라감
	_enemy->setEnemySpeed(0);							//기본 상태라서 속도가 0
	
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_idle");

}

void enemyIdle::render()
{

	enemyState::render();
}

void enemyIdle::enemyStateChange()
{	

	//CHASE상태로 바꾼다
	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() < 600 && _enemy->getIsEenmyChase() && _enemy->getIsEnemyIdle())			//플레이어과의 거리가 작아질시 추격상태이미지로
		{
			_enemy->setEnemyState(new enemyChase);
		}
	}
	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() < 600 && _enemy->getIsEenmyChase() && _enemy->getIsEnemyIdle())			//플레이어과의 거리가 작아질시 추격상태이미지로
		{
			_enemy->setEnemyState(new enemyChase);
		}
	}
	//달리기 
	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() < 790 && !_enemy->getIsEenmyChase() &&_enemy->getIsEnemyIdle())
		{
			_enemy->setEnemyState(new enemyRun);
		}
	}
	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() < 790)
		{
			_enemy->setEnemyState(new enemyRun);
		}
	}


	//공격상태로
	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() < 10 && !_enemy->getIsEenmyChase() && !_enemy->getIsEnemyAttack() && !_enemy->getIsEnemyIdle() && _enemy->getIsEnemyWaitAttack() && _enemy->getEnemyCount() > 100)
		{
			_enemy->setEnemyState(new enemyAttack);
			
		}
	}
	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() < 10 && !_enemy->getIsEenmyChase() && !_enemy->getIsEnemyAttack() && !_enemy->getIsEnemyIdle() && _enemy->getIsEnemyWaitAttack() && _enemy->getEnemyCount() > 100)
		{
			_enemy->setEnemyState(new enemyAttack);
	
		}
	}
	//피격시
	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getIsEnemyHurt() && _enemy->getEnemyDistance() < 10 && _enemy->getIsEnemyIdle())
		{
			_enemy->setEnemyState(new enemyHurt);

		}
	}

	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getIsEnemyHurt() && _enemy->getEnemyDistanceR() < 10 && _enemy->getIsEnemyIdle())
		{
			_enemy->setEnemyState(new enemyHurt);

		}
	}

}

void enemyIdle::enemyAni()
{
	if (_enemyDir == (int)ENEMY_LEFT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_idleL");
		_enemyAni->resume();
	}
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_idleR");
		_enemyAni->resume();
	}
}

#pragma endregion
//////////////////////////////////////////////  추   격  ///////////////////////////////////////////////////////////
#pragma region 추격 상태

enemyChase::enemyChase()
{
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_walk");
}

enemyChase::~enemyChase()
{
}

HRESULT enemyChase::init()
{
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_walk");
	_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_walkL");
	_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_walkR");
	return S_OK;
}

void enemyChase::release()
{
}

void enemyChase::update()
{
	enemyState::update();


	_enemy->setEnemyCount(_enemy->getEnemyCount() + 1);
	
	_enemy->setEnemySpeed(3.f);
	
	_enemy->setIsEnemyIdle(false);
	_enemy->setIsEnemyAttack(false);
	_enemy->setIsEnemyChase(true);
	_enemy->setIsEnemyWaitAttack(false);
	_enemy->setIsEnemyHurt(false);
	_enemy->setIsEnemyRun(false);
	_enemy->setIsEnemyDie(false);


	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_walk");

}

void enemyChase::render()
{
	enemyState::render();
}

void enemyChase::enemyStateChange()
{
	
		if (_enemyDir == ENEMY_LEFT)
		{
			if (_enemy->getEnemyDistance() > 800 && !_enemy->getIsEnemyAttack() && _enemy->getIsEenmyChase())			//플레이어과의 거리가 커질시 기본상태이미지로
			{
				_enemy->setIsEnemyAttack(false);
				_enemy->setEnemyState(new enemyIdle);
			}
		}
		if (_enemyDir == ENEMY_RIGHT)
		{
			if (_enemy->getEnemyDistanceR() > 800 && !_enemy->getIsEnemyAttack() && _enemy->getIsEenmyChase())			//플레이어과의 거리가 커질시 기본상태이미지로
			{
				_enemy->setIsEnemyAttack(false);
				_enemy->setEnemyState(new enemyIdle);
			}
		}
		
		
		if (_enemyDir == ENEMY_LEFT)
		{
			if (_enemy->getEnemyDistance() < 10 && !_enemy->getIsEnemyAttack() && _enemy->getIsEenmyChase())
			{	
				_enemy->setEnemyState(new enemyWaitAttack);
				
			}
		}
		if (_enemyDir == ENEMY_RIGHT)
		{
			if (_enemy->getEnemyDistanceR() < 10 && !_enemy->getIsEnemyAttack() && _enemy->getIsEenmyChase())			//플레이어와의 거리가 10보다 작아질시
			{
				_enemy->setEnemyState(new enemyWaitAttack);
			}
		}
		
		//피격시
		
		if (_enemyDir == ENEMY_LEFT)
		{
			if (_enemy->getIsEnemyHurt() && _enemy->getEnemyDistance() < 10 && _enemy->getIsEenmyChase())
			{
				_enemy->setEnemyState(new enemyHurt);
		
			}
		}

		if (_enemyDir == ENEMY_RIGHT )
		{
			if (_enemy->getIsEnemyHurt() && _enemy->getEnemyDistanceR() < 10 && _enemy->getIsEenmyChase())
			{
				_enemy->setEnemyState(new enemyHurt);

			}
		}
	}


void enemyChase::enemyAni()
{
	
	if (_enemyDir == (int)ENEMY_LEFT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_walkL");
		_enemyAni->resume();
	}
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_walkR");
		_enemyAni->resume();
	}

}

#pragma endregion
//////////////////////////////////////////////	공   격  ////////////////////////////////////////////////////////////
#pragma region 공격 상태
enemyAttack::enemyAttack()
{
	_EattackIdx = 0;

	if (_EattackIdx == 0)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack1");
		
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack1R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack1L");
		}
	}
	else if (_EattackIdx == 1)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack2");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2L");
		}
	}
	else if (_EattackIdx == 2)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack3");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2L");
		}
	}

	
}

enemyAttack::~enemyAttack()
{
}

HRESULT enemyAttack::init()
{
	if (_EattackIdx == 0)
	{
		_enemyImg = IMAGEMANAGER->findImage
		("SCHOOLGIRL_comboAttack1");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack1R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack1L");
		}
	}
	else if (_EattackIdx == 1)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack2");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2L");
		}
	}
	else if (_EattackIdx == 2)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack3");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2R");

		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2L");
		}
	}


	return S_OK;
}

void enemyAttack::release()
{
}

void enemyAttack::update()
{
	enemyState::update();
	
	_enemy->setEnemySpeed(0);

	_enemy->setIsEnemyIdle(false);
	_enemy->setIsEnemyAttack(true);
	_enemy->setIsEnemyChase(false);
	_enemy->setIsEnemyWaitAttack(false);
	_enemy->setIsEnemyHurt(false);
	_enemy->setIsEnemyRun(false);
	_enemy->setIsEnemyDie(false);

	if ((_enemyAni->getNowPlayIdx() == 5 || _enemyAni->getNowPlayIdx() == 5 &&!_isHitCheck))
	{
		_isHitCheck = true;
	}

	if (_EattackIdx == 0)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack1");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack1R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack1L");
		}
	}
	else if (_EattackIdx == 1)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack2");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2L");
		}
	}
	else if (_EattackIdx == 2)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack3");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack3R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack3L");
		}
	}
	
	if(!_enemy->getIsEnemyAttack())						//어택 했을시
	{
		switch (_EattackIdx)							//어택 콤보수
		{	
		
		case 0:
			_enemy->setIsEnemyAttack(true);
			_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack1");
			
			break;
	
		case 1:
			_enemy->setIsEnemyAttack(true);
			_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack2");
			
			break;
			
		case 2:
			_enemy->setIsEnemyAttack(true);
			_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_comboAttack3");
			
			break;
		}
	}
}

void enemyAttack::render()
{
	enemyState::render();
}

void enemyAttack::enemyStateChange()
{
	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() >= 10 && !_enemy->getIsEnemyAttack() && !_enemy->getIsEenmyChase())
		{
			_enemy->setIsEnemyAttack(false);
			_enemyAni->stop();
			_enemy->setEnemySpeed(2.f);
			_enemy->setEnemyState(new enemyChase);
		}
	}
	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() >= 10 && !_enemy->getIsEnemyAttack() && !_enemy->getIsEenmyChase())
		{
			_enemy->setIsEnemyAttack(false);
			_enemyAni->stop();
			_enemy->setEnemySpeed(2.f);
			_enemy->setEnemyState(new enemyChase);
		}
	}

	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() < 10 && _enemy->getIsEnemyAttack() && _EattackIdx >3)
		{
			_enemy->setIsEnemyAttack(false);
			_enemy->setEnemyState(new enemyIdle);
	
		}
	}
	
	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() < 10 && _enemy->getIsEnemyAttack()&& _EattackIdx >3)
		{
			_enemy->setIsEnemyAttack(false);
			_enemy->setEnemyState(new enemyIdle);
	
		}
	}

	//피격시
	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getIsEnemyHurt() && _enemy->getEnemyDistance() < 10 && _enemy->getIsEnemyAttack())
		{
			_enemy->setEnemyState(new enemyHurt);

		}
	}

	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getIsEnemyHurt() && _enemy->getEnemyDistanceR() < 10 && _enemy->getIsEnemyAttack())
		{
			_enemy->setEnemyState(new enemyHurt);

		}
	}
}

void enemyAttack::enemyAni()
{
	if (_enemyDir == (int)ENEMY_LEFT)
	{
		switch (_EattackIdx)
		{
		case 0:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack1L");
			_enemyAni->resume();
	
			break;
		
		case 1:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2L");
			_enemyAni->resume();
		
			break;
		
		case 2:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack3L");
			_enemyAni->resume();
		
			break;
		
		}
		
	}
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		switch (_EattackIdx)
		{
		case 0:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack1R");
			_enemyAni->resume();
			break;
	
		case 1:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack2R");
			_enemyAni->resume();
			break;
	
		case 2:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_comboAttack3R");
			_enemyAni->resume();
			break;
		}

		
	}
}
void enemyAttack::callBk()				
{
	if (!_enemyAni->isPlay())					
	{
		if (_enemy->getIsEnemyAttack())
		{

			_enemyAni->stop();
			if (_EattackIdx < 3) _EattackIdx++;
			else _EattackIdx = 0;
			
			if (_EattackIdx >= 3)
			{
				_enemy->setEnemyCount(0);
				_enemy->setEnemyState(new enemyWaitAttack);
			}
		}
	}
}

#pragma endregion
//////////////////////////////////////////////	피   격  ////////////////////////////////////////////////////////////
#pragma region 피격 상태

enemyHurt::enemyHurt()
{
	_EattackIdx = 0;

	if (_EhultIdx == 0)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit1R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit1L");
		}
	}
	else if (_EhultIdx == 1)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit2R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit2L");
		}
	}
	else if (_EhultIdx == 2)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit3R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit3L");
		}
	}
}

enemyHurt::~enemyHurt()
{
}

HRESULT enemyHurt::init()
{
	if (_EhultIdx == 0)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit1R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit1L");
		}
	}
	else if (_EhultIdx == 1)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit2R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit2L");
		}
	}
	else if (_EhultIdx == 2)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit3R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit3L");
		}
	}


	return S_OK;
}

void enemyHurt::release()
{
}

void enemyHurt::update()
{
	
	enemyState::update();
	

	_enemy->setIsEnemyIdle(false);
	_enemy->setIsEnemyAttack(false);
	_enemy->setIsEnemyChase(false);
	_enemy->setIsEnemyWaitAttack(false);
	_enemy->setIsEnemyHurt(true);
	_enemy->setIsEnemyRun(false);
	_enemy->setIsEnemyDie(false);

	_EHurtcount++;

	_enemy->setEnemySpeed(0);
	
	if (_EhultIdx == 0)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit1R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit1L");
		}
	}
	else if (_EhultIdx == 1)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit2R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit2L");
		}
	}
	else if (_EhultIdx == 2)
	{
		_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
		if (_enemyDir == (int)ENEMY_RIGHT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit3R");
		}
		if (_enemyDir == (int)ENEMY_LEFT)
		{
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit3L");
		}
	}

	if (!_enemy->getIsEnemyHurt())						
	{
		switch (_EhultIdx)							//어택 콤보수
		{
		case 0:
			
			_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
			break;

		case 1:
			
			_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
			break;

		case 2:
			
			_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_gethit");
			break;
		}
	}

	//callBk();



}

void enemyHurt::render()
{
	enemyState::render();
}

void enemyHurt::enemyStateChange()
{


	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() < 10 && _enemy->getIsEnemyHurt() && _EhultIdx > 3)
		{
			_enemy->setEnemyState(new enemyWaitAttack);

		}
	}

	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() < 10 && _enemy->getIsEnemyHurt() && _EhultIdx > 3)
		{
			_enemy->setEnemyState(new enemyWaitAttack);
		}
	}

	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() >= 10 && !_enemy->getIsEenmyChase())
		{
			_enemyAni->stop();
			_enemy->setEnemySpeed(2.f);
			_enemy->setEnemyState(new enemyChase);
		}
	}
	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() >= 10 && !_enemy->getIsEenmyChase())
		{
			_enemyAni->stop();
			_enemy->setEnemySpeed(2.f);
			_enemy->setEnemyState(new enemyChase);
		}
	}
	if (_enemyDir == ENEMY_RIGHT)
	{
		if (!_enemy->getIsEnemyDie() && _enemy->getEnemyHp() < 1)
		{
			_enemy->setEnemyState(new enemyDie);
		}
	}

	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() < 10 &&!_enemy->getIsEnemyDie() && _enemy->getEnemyHp() < 1)
		{
			_enemy->setEnemyState(new enemyDie);

		}
	}
	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() < 10 && !_enemy->getIsEnemyDie() && _enemy->getEnemyHp() < 1)
		{
			_enemy->setEnemyState(new enemyDie);
		}
	}
}

void enemyHurt::enemyAni()
{
	if (_enemyDir == (int)ENEMY_LEFT)
	{
		switch (_EhultIdx)
		{
		case 0:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit1L");
			_enemyAni->resume();
			break;

		case 1:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit2L");
			_enemyAni->resume();
			break;

		case 2:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit3L");
			_enemyAni->resume();
			break;

		}

	}
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		switch (_EhultIdx)
		{
		case 0:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit1R");
			_enemyAni->resume();
			break;

		case 1:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit2R");
			_enemyAni->resume();
			break;

		case 2:
			_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_gethit3R");
			_enemyAni->resume();
			break;
		}


	}
}
void enemyHurt::callBk()
{
	if (!_enemyAni->isPlay())
	{
		if (_enemy->getIsEnemyHurt())
		{
			
			_enemyAni->stop();

			//맞는 카운트가 3보다 작을때 카운트를 늘려라!
			if (_EhultIdx < 3 && _enemy->getIsEnemyHurt())
			{
				_EHurtcount = 0;
				_EhultIdx += 1;
			}
			else _EhultIdx = 0;
				
			}
			if (_EHurtcount > 20)
			{
				_enemy->setEnemyState(new enemyWaitAttack);
			}
		}
	}

#pragma endregion
//////////////////////////////////////////////	점   프  ////////////////////////////////////////////////////////////
#pragma region 점프 상태
enemyJump::enemyJump()
{
}

enemyJump::~enemyJump()
{
}

HRESULT enemyJump::init()
{
	_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_jumpL");
	_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_jumpR");
	return S_OK;
}

void enemyJump::release()
{
}

void enemyJump::update()
{

	enemyState::update();
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_jump");
}

void enemyJump::render()
{
	enemyState::render();
}

void enemyJump::enemyStateChange()
{
	
}

void enemyJump::enemyAni()
{
	_enemy->setEnemySpeed(3.0f);

	if (_enemyDir == ENEMY_LEFT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_jumpL");
		_enemyAni->resume();
	}
	if (_enemyDir == ENEMY_RIGHT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_jumpR");
		_enemyAni->resume();
	}
}

#pragma endregion
//////////////////////////////////////////////	죽   음  ////////////////////////////////////////////////////////////
#pragma region 죽음 상태

enemyDie::enemyDie()
{
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_weapon_swing");
}

enemyDie::~enemyDie()
{
}

HRESULT enemyDie::init()
{
	enemyState::init();

	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_weapon_swing");
	return S_OK;
}

void enemyDie::release()
{
}

void enemyDie::update()
{
	enemyState::update();

	_enemy->setIsEnemyIdle(false);
	_enemy->setIsEnemyAttack(false);
	_enemy->setIsEnemyChase(false);
	_enemy->setIsEnemyWaitAttack(false);
	_enemy->setIsEnemyHurt(false);
	_enemy->setIsEnemyRun(false);
	_enemy->setIsEnemyDie(true);
	
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_weapon_swing");
}

void enemyDie::render()
{
	enemyState::render();
}

void enemyDie::enemyStateChange()
{
	if (_enemy->getIsEnemyCompleteDeath())
	{
		_enemy->setEnemyState(new enemyCompleteDeath);
	}
	
}

void enemyDie::enemyAni()
{
	if (_enemyDir == (int)ENEMY_LEFT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_dieL");
		_enemyAni->resume();
	}
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_dieR");
		_enemyAni->resume();
	}
}


#pragma endregion
//////////////////////////////////////////////	누   움  ////////////////////////////////////////////////////////////
#pragma region 쓰러졌다 일어남

enemybackdown::enemybackdown()
{
}

enemybackdown::~enemybackdown()
{
}

HRESULT enemybackdown::init()
{
	return S_OK;
}

void enemybackdown::release()
{
}

void enemybackdown::update()
{
}

void enemybackdown::render()
{
}

void enemybackdown::enemyStateChange()
{
}

void enemybackdown::enemyAni()
{
}
#pragma endregion
//////////////////////////////////////////////	잡   힘  ////////////////////////////////////////////////////////////
#pragma region 붙잡힘
enemyheld::enemyheld()
{
}

enemyheld::~enemyheld()
{
}

HRESULT enemyheld::init()
{
	return S_OK;
}

void enemyheld::release()
{
}

void enemyheld::update()
{
}

void enemyheld::render()
{
}

void enemyheld::enemyStateChange()
{
}

void enemyheld::enemyAni()
{
}

#pragma endregion
//////////////////////////////////////////////	공격대기  ////////////////////////////////////////////////////////////
#pragma region 어택하기전 대기 모션

enemyWaitAttack::enemyWaitAttack()
{
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_idle");
}

enemyWaitAttack::~enemyWaitAttack()
{
	
}

HRESULT enemyWaitAttack::init()
{
	enemyState::init();

	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_idle");

	return S_OK;
}

void enemyWaitAttack::release()
{
}

void enemyWaitAttack::update()
{
	_enemy->setEnemyCount(_enemy->getEnemyCount() + 1);
	_enemy->setEnemySpeed(0.f);
		
	_enemy->setIsEnemyIdle(false);
	_enemy->setIsEnemyAttack(false);
	_enemy->setIsEnemyChase(false);
	_enemy->setIsEnemyWaitAttack(true);
	_enemy->setIsEnemyHurt(false);
	_enemy->setIsEnemyRun(false);
	_enemy->setIsEnemyDie(false);
	
	_EhultIdx = 0;


	enemyState::update();

	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_idle");
}

void enemyWaitAttack::render()
{
	enemyState::render();
}

void enemyWaitAttack::enemyStateChange()
{
	if (_enemyDir == ENEMY_LEFT)
	{
		if(_enemy->getEnemyDistance() >= 10)
		{
			_enemy->setEnemyState(new enemyChase);
		}
	}

	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() >= 10)
		{
			_enemy->setEnemyState(new enemyChase);
		}
	}

	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() < 10 && !_enemy->getIsEenmyChase() && !_enemy->getIsEnemyAttack() && !_enemy->getIsEnemyIdle() && _enemy->getIsEnemyWaitAttack() && _enemy->getEnemyCount() > RND->getFromFloatTo(50, 200))
		{
			_enemy->setEnemyState(new enemyAttack);

		}
	}
	
	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() < 10 && !_enemy->getIsEenmyChase() && !_enemy->getIsEnemyAttack() && !_enemy->getIsEnemyIdle() && _enemy->getIsEnemyWaitAttack() && _enemy->getEnemyCount() > RND->getFromFloatTo(50,200))
		{
			_enemy->setEnemyState(new enemyAttack);
		}
	}

	//피격시
	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getIsEnemyHurt() && _enemy->getEnemyDistance() < 10 && _enemy->getIsEnemyWaitAttack())
		{
			_enemy->setEnemyState(new enemyHurt);

		}
	}

	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getIsEnemyHurt() && _enemy->getEnemyDistanceR() < 10 && _enemy->getIsEnemyWaitAttack())
		{
			_enemy->setEnemyState(new enemyHurt);

		}
	}

	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() < 10 && !_enemy->getIsEnemyAttack() && _enemy->getIsEnemyRunAttack())
		{
			_enemy->setEnemyState(new enemyRunAttack);
		}
	}

	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() < 10 && !_enemy->getIsEnemyAttack() && _enemy->getIsEnemyRunAttack())
		{
			_enemy->setEnemyState(new enemyRunAttack);
		}
	}
}

void enemyWaitAttack::enemyAni()
{
	if (_enemyDir == (int)ENEMY_LEFT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_idleL");
		_enemyAni->resume();
	}
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_idleR");
		_enemyAni->resume();
	}
}

#pragma endregion
//////////////////////////////////////////////	달 리 기  ////////////////////////////////////////////////////////////
#pragma region 달리기



enemyRun::enemyRun()
{
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_run");
}

enemyRun::~enemyRun()
{
}

HRESULT enemyRun::init()
{
	enemyState::init();

	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_run");

	return S_OK;
}

void enemyRun::release()
{
}

void enemyRun::update()
{
	
	_enemy->setIsEnemyIdle(false);
	_enemy->setIsEnemyAttack(false);
	_enemy->setIsEnemyChase(false);
	_enemy->setIsEnemyWaitAttack(false);
	_enemy->setIsEnemyHurt(false);
	_enemy->setIsEnemyRun(true);
	_enemy->setIsEnemyDie(false);	
	
	
	_enemy->setEnemySpeed(4.0f);

	enemyState::update();

	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_run");
}

void enemyRun::render()
{
	enemyState::render();
}

void enemyRun::enemyStateChange()
{
	if(_enemyDir == (int)ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() > 800)
		{
			_enemy->setEnemyState(new enemyWaitAttack);
		}
	}
	
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() > 800)
		{
			_enemy->setEnemyState(new enemyWaitAttack);
		}
	}

	if (_enemyDir == (int)ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() < 10)
		{
			_enemy->setEnemyState(new enemyAttack);
		}
	}
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() < 10)
		{
			_enemy->setEnemyState(new enemyAttack);
		}
	}

	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getIsEnemyHurt() && _enemy->getEnemyDistance() < 10 && _enemy->getIsEnemyRun())
		{
			_enemy->setEnemyState(new enemyHurt);

		}
	}

	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getIsEnemyHurt() && _enemy->getEnemyDistanceR() < 10 && _enemy->getIsEnemyRun())
		{
			_enemy->setEnemyState(new enemyHurt);

		}
	}
}

void enemyRun::enemyAni()
{
	if (_enemyDir == (int)ENEMY_LEFT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_runL");
		_enemyAni->resume();
	}
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_runR");
		_enemyAni->resume();
	}
}
#pragma endregion
//////////////////////////////////////////////	대쉬어택  ////////////////////////////////////////////////////////////
#pragma region 대쉬어택
enemyRunAttack::enemyRunAttack()
{
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_jumpAttack");
}

enemyRunAttack::~enemyRunAttack()
{
}

HRESULT enemyRunAttack::init()
{
	enemyState::init();

	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_jumpAttack");
	return S_OK;
}

void enemyRunAttack::release()
{
}

void enemyRunAttack::update()
{
	enemyState::update();
	
	_enemy->setEnemySpeed(0);
	_enemy->setEnemyCount(0);
	_enemy->setIsEnemyChase(false);
	_enemy->setIsEnemyRun(false);
	_enemy->setIsEnemyIdle(false);
	_enemy->setIsEnemyHurt(false);
	_enemy->setIsEnemyRunAttack(true);

	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_jumpAttack");

}

void enemyRunAttack::render()
{
	enemyState::render();
}

void enemyRunAttack::enemyStateChange()
{
	//거리가 멀어지면 공격 대기 모션으로
	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getEnemyDistance() > 10)
		{
			_enemy->setEnemyState(new enemyWaitAttack);
		}
	}
	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getEnemyDistanceR() > 10)
		{
			_enemy->setEnemyState(new enemyWaitAttack);
		}
	}

	//피격시
	if (_enemyDir == ENEMY_LEFT)
	{
		if (_enemy->getIsEnemyHurt())
		{
			_enemy->setEnemyState(new enemyHurt);

		}
	}

	if (_enemyDir == ENEMY_RIGHT)
	{
		if (_enemy->getIsEnemyHurt())
		{
			_enemy->setEnemyState(new enemyHurt);

		}
	}

}

void enemyRunAttack::enemyAni()
{
	if (_enemyDir == (int)ENEMY_LEFT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_dashAttackL");
		_enemyAni->resume();
	}
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_dashAttackR");
		_enemyAni->resume();
	}
}
void enemyRunAttack::callBk()
{
	//if (!_enemyAni->isPlay())
	//{
	//	if (_enemy->getIsEnemyRunAttack())
	//	{			
	//		//_enemyAni->stop();
	//		//_enemy->setEnemyState(new enemyIdle);
	//	}	
	//}
}
#pragma endregion
//////////////////////////////////////////////	적 완전히 죽음  ///////////////////////////////////////////////////////
#pragma region 적 완전히 죽음 
enemyCompleteDeath::enemyCompleteDeath()
{
	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_weapon_swing");
}

enemyCompleteDeath::~enemyCompleteDeath()
{
}

HRESULT enemyCompleteDeath::init()
{
	enemyState::init();

	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_weapon_swing");
	return S_OK;
}

void enemyCompleteDeath::release()
{
}

void enemyCompleteDeath::update()
{
	enemyState::update();
	
	_enemy->setIsEnemyDie(false);


	_enemyImg = IMAGEMANAGER->findImage("SCHOOLGIRL_weapon_swing");

}

void enemyCompleteDeath::render()
{
	enemyState::render();
}

void enemyCompleteDeath::enemyStateChange()
{
}

void enemyCompleteDeath::enemyAni()
{
	if (_enemyDir == (int)ENEMY_LEFT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_CompleteDeathL");
		_enemyAni->resume();
	}
	if (_enemyDir == (int)ENEMY_RIGHT)
	{
		_enemyAni = KEYANIMANAGER->findAnimation("SCHOOLGIRL_CompleteDeathR");
		_enemyAni->resume();
	}



}
#pragma endregion