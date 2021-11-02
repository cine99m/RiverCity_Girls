#pragma once
#include "gameNode.h"
#include "camera.h"
#include "imageStorage.h"


#include "wait.h"

#include "idle.h"
#include "walk.h"
#include "run.h"
#include "jump.h"

#include "hit.h"
#include "guard.h"
#include "down.h"
#include "stand.h"
#include "stun.h"
#include "die.h"

#include "atk.h"
#include "sAtk.h"
#include "sAtkDown.h"

#include "grab.h"
#include "stomp.h"
#include "jumpAtk.h"
#include "dashAttack.h"
#include "dashSAttack.h"

#define GRAVITY 1.0f  // 중력값

#pragma warning(disable:4996)

class boss;

class object;

class enemy;

class objectManager;//추가

class enemyManager;


class gameManager;


class player : public gameNode
{
private:
	camera* _camera;

	state* _state;
	boss* _boss;

	object* _object;
	objectManager* _objectManager;//추가

	enemyManager* _enemyManager;

	gameManager* _gM;

	enemy* _enemy;


	image* _shadowImg;		//그림자 이미지
	RECT   _shadowRc;       //그림자 직사각형
	
	float _sX, _sY;			//그림자 x,y
	float _speed;			//이동 속도
	float _jumpPower;		//점프 파워

	//불값들
	bool  _isJump;          //점프하고 있는지
	
	bool  _isAttacking;     //공격하고 있는지

	bool  _isHitToEnemy;	//내 공격이 상대에게 들어갔는지.

	bool _isGetHit;			//적에게 맞았을때
	bool _isGuarding;		//내가 방어하고있을때
	
	//플레이어 관련
	image* _playerImg;		//플레이어의 이미지
	RECT  _playerRc;        //플레이어의 직사각형

	float _pX, _pY;			//실제 플레이어의 x,y 값


	int _hp;				//플레이어 체력

	int _dir;				//빙향

	//개떡같은 카메라 제작중


	bool _DK;				//윗키불
	bool _UK;				//아래키불
	bool _RK;				//오른쪽키불
	bool _LK;				//왼쪽키불


	stageImg _stage;
	


public:
	player();
	~player();

    HRESULT init();			//초기화 함수
    void release();			//메모리 해제 함슈
    void update();			//연산하는 함수
	void render() ;	//그리기 함수

	void stateRender(animation* motion);
	void move();

	
	void playerAni();		//플레이어 애니메이션 모음
	
	void playerSound();

	void attack();

	static void callBack(void* obj);

	// 접근자 및 설정자 
	
	//플레이어 X 
	float getPlayerX() { return _pX; }
	void setPlayerX(float px) { _pX = px; }

	//플레이어 Y
	float getPlayerY() { return _pY; }
	void setPlayerY(float py) { _pY = py; }

	//그림자 X
	float getShadowX() { return _sX; }
	void setShadowX(float sx) { _sX = sx; }

	//그림자 Y
	float getShadowY() { return _sY; }
	void setShadowY(float sy) { _sY = sy; }

	//이동속도
	float getSpeed() { return _speed; }
	void setSpeed(float speed) { _speed = speed; }
	
	//점프값 설정
	float getJumpPower() { return _jumpPower; }
	void setJumpPower(float jumppower) { _jumpPower = jumppower; }

	//플레이어의 상황을 설정 접근자
	bool getIsJump() { return _isJump; }
	void setIsJump(bool isJump) { _isJump = isJump; }

	bool getIsAttacking() { return _isAttacking; }
	void setIsAttacking(bool isAttack) { _isAttacking = isAttack; }

	bool getIsHitToEnemy() { return _isHitToEnemy; }
	void setIsHitToEnemy(bool isHitToEnemy) { _isHitToEnemy = isHitToEnemy; }

	bool getIsGuarding() { return _isGuarding; }
	void setIsGuarding(bool isGuard) { _isGuarding = isGuard; }

	bool getIsGetHit() { return _isGetHit; }
	void setIsGetHit(bool isGetHit) { _isGetHit = isGetHit; }

	//플레이어 체력 
	int getPlayerHp() { return _hp; }
	void setPlayerHp(int playerHp) { _hp -= playerHp; }

	//플레이어 직사각형 설정
	RECT getPlayerRc() { return _playerRc; }
	RECT getShadowRc() { return _shadowRc; }

	//플레이어의 방향을 가져온다 
	int getDir() { return _dir; }

	//플레이어의 이미지를 가져온다
	image* getPlayerImg() { return _playerImg; }
	image* getShadowImg() { return _shadowImg; }


	//중간에 모션이 바뀌면 렌더로 바뀌지 않은 이미지가 로드됨으로 update부터 다시 시작
	void setState(state* state) { _state = state; update(); update(); }

	void setCamera(camera* camera) { _camera = camera; }

	state* getState() { return _state; }







	// width, height
	float getWidth() { return _shadowRc.right - _shadowRc.left; }
	float getHeight() { return _shadowRc.bottom - _shadowRc.top; }


	// bossMemory
	void setBossMemoryAddressLink(boss* boss) { _boss = boss; }
	// enemyMemory
	void setEnemyMemoryAddressLink(enemy* enemy) { _enemy = enemy; }
	// enemyManager
	void setEnemyManagerMemoryAddressLink(enemyManager* enemyManager) { _enemyManager = enemyManager; }

	virtual float getPosY() { return _sY; }

	//오브젝트 메모리
	void setObjectMemoryAddressLink(object* object) { _object = object; }

	void setObjectManagerMemoryAddressLink(objectManager* objectManager) {_objectManager = objectManager;}//추가

	
	void setRK(bool Rk) { _RK = Rk; }
	void setLK(bool Lk) { _LK = Lk; }
	void setUK(bool Uk) { _UK = Uk; }
	void setDK(bool Dk) { _DK = Dk; }


	void setGm(gameManager* gm) { _gM = gm; }


};

