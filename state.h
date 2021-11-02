#pragma once
#include "gameNode.h"
#include "animation.h"

#define GRAVITY 0.3f;

class player;					//전방선언
class boss;

enum dir
{
	LEFT,
	RIGHT
};

class state : public gameNode
{
protected:
	
	image* _playerImg;
	int _dir;

	animation* _playerAni;

	

	float _jump = 10.0f;

	player* _player;
	RECT _playerRc;

	boss* _boss;

	// distance
	float _dx, _dy;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange() {};
	virtual void ani() {};
	virtual void distance();
	virtual void hitCheck();


	virtual void setPlayer(player* player) { _player = player; }

	//접근자 // 설정자
	
	virtual animation* getPlayerAni() { return _playerAni; }
	virtual image* getPlImg() { return _playerImg; }

	//점프파워 가져오기
	virtual float getJumpPower() { return _jump; }

	virtual void setBossMemoryAddressLink(boss* boss) { _boss = boss; }
	

	

};

