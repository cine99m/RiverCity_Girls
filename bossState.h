#pragma once
#include "gameNode.h"

class boss;
class player;

enum class DIRECTION
{
	LEFT,
	RIGHT
};

class bossState : public gameNode
{
protected:
	image* _bossImg;
	int _direction;

	boss* _boss;
	RECT _bossRc;

	player* _player;

	//animation* _bossAnim;
	animation* _bossAnimL;
	animation* _bossAnimR;

	bool _isAnim;
	bool _isStart;

	float _distance;

	float _dx, _dy;

	int _bAttackPattern = 1;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void anim();
	virtual void animOver();
	virtual void hitCheck();

	image* getImg() { return _bossImg; }
	void setBoss(boss* boss) { _boss = boss; }
	void setPlayerMemoryAddressLink(player* player) { _player = player; }

	//animation* getBossAnim() { return _bossAnim; }

	void setDirection(int direction) { _direction = direction; }

protected:
	void setBossState(boss* boss, bossState* state) { /*boss->setState(state); // 상태 변경*/ }
};

class idleState : public bossState
{
private:

public:
	idleState();
	~idleState();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void anim();
};

class walkState : public bossState
{
private:

public:
	walkState();
	~walkState();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void anim();
};

class attackState : public bossState
{
private:

public:

	attackState();
	~attackState();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void anim();
	virtual void animOver();
};

class jumpState : public bossState
{
private:

public:

	jumpState();
	~jumpState();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void anim();
	virtual void animOver();
	virtual void hitCheck();
};

class dashState : public bossState
{
private:

public:

	dashState();
	~dashState();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void anim();
	virtual void animOver();
};

class roarState : public bossState
{
private:

public:

	roarState();
	~roarState();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void anim();
	virtual void animOver();
};

class sitState : public bossState
{
private:
	sitState* instance;

public:
	sitState* getInstance() { if (instance == nullptr) instance = new sitState(); return instance; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

class groggyState : public bossState
{
private:

public:
	groggyState();
	~groggyState();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void anim();
	virtual void animOver();
};

class hitState : public bossState
{
private:

public:
	hitState();
	~hitState();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void stateChange();
	virtual void anim();
	virtual void animOver();
};

class loseState : public bossState
{
private:
	loseState* instance;

public:
	loseState* getInstance() { if (instance == nullptr) instance = new loseState(); return instance; }

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
