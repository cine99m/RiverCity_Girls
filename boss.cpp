#include "pch.h"
#include "boss.h"
#include "player.h"

HRESULT boss::init()
{
	_sx = WINSIZEX / 2 + 151;
	_sy = WINSIZEY / 2;

	bossAnim();

	_state = new idleState;
	_state->init();

	_state->setBoss(this);
	_state->setPlayerMemoryAddressLink(_player);

	_bossImg = _state->getImg();
	_bShadowImg = IMAGEMANAGER->findImage("SHADOW");

	_bx = _sx;
	_by = _sy - _bossImg->getFrameHeight() / 2;

	_bossRc = RectMakeCenter(_bx, _by, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
	_bShadowRc = RectMakeCenter(_sx, _sy, _bShadowImg->getWidth(), _bShadowImg->getHeight());

	_speed = 0;
	_jumpPower = 0;

	_hp = 200;

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	_state->update();

	_bossImg = _state->getImg();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	_bx = _sx;
	_by = _sy - _bossImg->getFrameHeight() / 2;

	calDistance();

	if (_isMove) move();

	jump();

	if ((abs(getAngle(_player->getShadowX(), _player->getShadowY(), _sx, _sy)) < PI / 2 || abs(getAngle(_player->getShadowX(), _player->getShadowY(), _sx, _sy)) > 3 * PI / 2) &&
		!_isAttack && !_isJump && !_isFloat && !_isDrop && !_isGroggy)
	{
		_direction = (int)DIRECTION::LEFT;
	}
	else if ((abs(getAngle(_player->getShadowX(), _player->getShadowY(), _sx, _sy)) > PI / 2 && abs(getAngle(_player->getShadowX(), _player->getShadowY(), _sx, _sy)) < 3 * PI / 2) &&
		!_isAttack && !_isJump && !_isFloat && !_isDrop && !_isGroggy)
	{
		_direction = (int)DIRECTION::RIGHT;
	}

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		_isHit = true;
	}

	//EFFECTMANAGER->update();

	if (_hp <= 0) exit(1);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	_bossRc = RectMakeCenter(_bx, _by, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
	_bShadowRc = RectMakeCenter(_sx, _sy, _bShadowImg->getWidth(), _bShadowImg->getHeight());

	_state->setBoss(this);
	_state->setPlayerMemoryAddressLink(_player);


}

void boss::render()
{
	_bShadowImg->render(getMemDC(), _bShadowRc.left, _bShadowRc.top);
	_state->render();
	//EFFECTMANAGER->render();

	char str[128];
	/*sprintf_s(str, "_sx : %.2f  _sy : %.2f", _sx, _sy);
	TextOut(getMemDC(), 10, 150, str, strlen(str));*/

	sprintf_s(str, "jump : %d", (int)_isJump);
	TextOut(getMemDC(), 10, 300, str, strlen(str));

	sprintf_s(str, "move : %d", (int)_isMove);
	TextOut(getMemDC(), 10, 350, str, strlen(str));

	sprintf_s(str, "hit : %d", (int)_isHit);
	TextOut(getMemDC(), 10, 380, str, strlen(str));

	sprintf_s(str, "time : %.2f", _time);
	TextOut(getMemDC(), 10, 400, str, strlen(str));

	sprintf_s(str, "power : %.2f", _jumpPower);
	TextOut(getMemDC(), 10, 430, str, strlen(str));

	sprintf_s(str, "camX : %.2f camY : %.2f", _camera->getCamX(), _camera->getCamY());
	TextOut(getMemDC(), 10, 700, str, strlen(str));
}

void boss::stateRender(animation* anim)
{
	_bossImg->aniRender(getMemDC(), _bossRc.left, _bossRc.top, anim);
}

void boss::bossAnim()
{
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_idleL", "BOSS_idle", 11, 0, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_idleR", "BOSS_idle", 12, 23, 10, false, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_walkL", "BOSS_walk", 19, 10, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_walkR", "BOSS_walk", 0, 9, 10, false, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_slapL", "BOSS_slap", 27, 14, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_slapR", "BOSS_slap", 0, 13, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_jumpL", "BOSS_meteor_J", 7, 0, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_jumpR", "BOSS_meteor_J", 8, 15, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_dropL", "BOSS_down", 21, 0, 30, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_dropR", "BOSS_down", 22, 43, 30, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_dashStartL", "BOSS_dash", 0, 1, 10, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_dashStartR", "BOSS_dash", 19, 18, 10, false, false);

	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_dashL", "BOSS_dash", 9, 2, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_dashR", "BOSS_dash", 10, 17, 10, false, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_groggyL", "BOSS_groggy", 0, 3, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_groggyR", "BOSS_groggy", 7, 4, 10, false, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_gHitL", "BOSS_meteor_G", 11, 6, 10, false, true);
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_gHitR", "BOSS_meteor_G", 0, 5, 10, false, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_hitL", "BOSS_attacked3", 0, 2, 7, false, false);
	KEYANIMANAGER->addCoordinateFrameAnimation("BOSS_hitR", "BOSS_attacked3", 5, 3, 7, false, false);


}

void boss::move()
{
	if (_isMove) _speed = 2;
	if (_isFloat) _speed = 6;
	if (_isDash) _speed = 6;

	if (_dx > _bShadowRc.right - _bShadowRc.left && !_isFloat)
	{
		_bx -= cosf(getAngle(_player->getShadowX(), _player->getShadowY(), _sx, _sy)) * _speed;
		_sx = _bx;
	}
	else if (_isFloat)
	{
		_bx -= cosf(getAngle(_player->getShadowX(), _player->getShadowY(), _sx, _sy)) * _speed;
		_sx = _bx;
	}

	if (_dy > (_bShadowRc.bottom - _bShadowRc.top) / 2 && !_isFloat)
	{
		_by -= -sinf(getAngle(_player->getShadowX(), _player->getShadowY(), _sx, _sy)) * _speed + _jumpPower;
		_sy = _by + _bossImg->getFrameHeight() / 2 + _jumpPower;
	}
	else if (_isFloat)
	{
		_by -= -sinf(getAngle(_player->getShadowX(), _player->getShadowY(), _sx, _sy)) * _speed + _jumpPower;
		_sy = _by + _bossImg->getFrameHeight() / 2 + _jumpPower;
	}
}

void boss::jump()
{
	if (!_isMove)
	{
		_by -= _jumpPower;
		_sy = _by + _bossImg->getFrameHeight() / 2 + _jumpPower;
	}

	if (_isJump)
	{
		if (_sy - _by < 1000)
		{
			_jumpPower += 30;
		}
	}
	else if (_isDrop)
	{
		if (_jumpPower > 0)
		{
			_jumpPower -= 30;
		}
	}
}

void boss::calDistance()
{
	_dx = abs(_player->getShadowX() - _sx);
	_dy = abs(_player->getShadowY() - _sy);
}

void boss::setBossPosAtCameraPos()
{
	_sx += _camera->getCamX();
	_sy += _camera->getCamY();
}
