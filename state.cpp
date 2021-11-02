#include "pch.h"
#include "state.h"
#include "player.h"
#include "boss.h"


HRESULT state::init()
{
	

	return S_OK;
}

void state::release()
{

}

void state::update()
{
	//방향을 플레이어에서 get으로 가져와서 설정해준다;
	_dir = _player->getDir();

	stateChange();
	ani();



	KEYANIMANAGER->update();
}

void state::render()
{

	if (_playerAni == NULL)
	{
		
	}

	_player->stateRender(_playerAni);

	char str[128];
	sprintf_s(str, "dir : %d", _dir);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
}

void state::distance()
{
	_dx = abs(_player->getShadowX() - _boss->getBossShadowX());
	_dy = abs(_player->getShadowY() - _boss->getBossShadowY());
}

void state::hitCheck()
{
	_dx = abs(_player->getShadowX() - _boss->getBossShadowX());
	_dy = abs(_player->getShadowY() - _boss->getBossShadowY());

	if (_player->getShadowRc().top < _boss->getBossShadowRect().bottom && _player->getShadowRc().bottom > _boss->getBossShadowRect().top && !_boss->getHit())
	{
		if (LEFT == _player->getDir())
		{
			if (_dx < _player->getWidth() && _player->getShadowX() > _boss->getBossShadowRect().left)
			{
				_boss->setHit(true);
			}
		}
		else if (RIGHT == _player->getDir())
		{
			if (_dx < _player->getWidth() && _player->getShadowX() < _boss->getBossShadowRect().right)
			{
				_boss->setHit(true);
			}
		}
	}

	//if (abs(_player->getShadowX() - _boss->getBossShadowX()) < _player->getShadowRc().right - _player->getShadowRc().left && 
	//	abs(_player->getShadowY() - _boss->getBossShadowY()) < _player->getShadowRc().bottom - _player->getShadowRc().top &&
	//	!_boss->getHit())
	//{
	//	_boss->setHit(true);
	//}
}


