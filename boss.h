#pragma once
#include "gameNode.h"
#include "bossState.h"
#include "camera.h"

class bossState;
class player;

enum class STATE
{
	IDLE,
	WALK,
	ATTACK,
	JUMP,
	SIT,
	GROGGY,
	LOSE
};

class boss : public gameNode
{
private:
	// class
	bossState* _state;
	STATE* _bState;

	player* _player;

	// shadow
	image* _bShadowImg;
	RECT _bShadowRc;

	// boss
	image* _bossImg;
	RECT _bossRc;

	int _hp;

	// position
	float _sx, _sy;		// shadowImgPos
	float _bx, _by;		// bossImgPos

	// distance
	float _dx, _dy;		// distance bShadow to pShadow

	// velocity
	float _speed;
	float _jumpPower;
	float _gravity;

	// direction
	int _direction;

	// time
	float _time;

	// bool (state)
	bool _isIdle;
	bool _isMove;
	bool _isAttack;
	bool _isJump;
	bool _isDrop;
	bool _isFloat;
	bool _isDash;
	bool _isGroggy;
	bool _isHit;

	// camera
	camera* _camera;

public:
	boss() {}
	~boss() {}

	HRESULT init();
	void release();
	void update();
	void render();

	void setState(bossState* state) { _state = state; }
	void stateRender(animation* anim);

	void bossAnim();

	void move();
	void jump();
	void calDistance();
	
	void setBossPosAtCameraPos();

	float getPosY() { return _sy; }


	// get
	int getBossHp() { return _hp; }
	float getBossShadowX() { return _sx; }
	float getBossShadowY() { return _sy; }
	float getBossX() { return _bx; }
	float getBossY() { return _by; }
	RECT getBossRect() { return _bossRc; }
	RECT getBossShadowRect() { return _bShadowRc; }

	float getBossWidth() { return _bossRc.right - _bossRc.left; }
	float getBossHeight() { return _bossRc.bottom - _bossRc.top; }
	float getBossShadowWidth() { return _bShadowRc.right - _bShadowRc.left; }
	float getBossShadowHeight() { return _bShadowRc.bottom - _bShadowRc.top; }

	float getDistanceX() { return _dx; }
	float getDistanceY() { return _dy; }

	int getBossDirection() { return _direction; }

	player* getPlayer() { return _player; }
	bossState* getState() { return _state; }

	bool getMove() { return _isMove; }
	bool getIsAttack() { return _isAttack; }
	bool getIsJump() { return _isJump; }
	bool getIsDrop() { return _isDrop; }
	bool getFloat() { return _isFloat; }
	bool getDash() { return _isDash; }
	bool getIdle() { return _isIdle; }
	bool getGroggy() { return _isGroggy; }
	bool getHit() { return _isHit; }

	float getTime() { return _time; }
	float getJumpPower() { return _jumpPower; }


	// set
	void setBossShadowX(float x) { _sx = x; }
	void setBossShadowY(float y) { _sy = y; }
	void setBossX(float x) { _bx = x; }
	void setBossY(float y) { _by = y; }

	void setDistanceX(float dx) { _dx = dx; }
	void setDistanceY(float dy) { _dy = dy; }

	void setBossDirection(int dir) { _direction = dir; }

	void setMove(bool move) { _isMove = move; }
	void setIsAttack(bool attack) { _isAttack = attack; }
	void setIsJump(bool jump) { _isJump = jump; }
	void setIsDrop(bool drop) { _isDrop = drop; }
	void setFloat(bool isFloat) { _isFloat = isFloat; }
	void setDash(bool dash) { _isDash = dash; }
	void setIdle(bool idle) { _isIdle = idle; }
	void setGroggy(bool groggy) { _isGroggy = groggy; }
	void setHit(bool hit) { _isHit = hit; }

	void setTime(float time) { _time = time; }
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }

	void setBossHp(int hp) { _hp -= hp; }

	

	// Memory
	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	void setCameraMemoryAddressLink(camera* camera) { _camera = camera; }

};

