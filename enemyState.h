#pragma once
#include "gameNode.h"
#include "animation.h"


class enemy;

enum enemyDir
{
	ENEMY_LEFT,
	ENEMY_RIGHT
};

class enemyState : public gameNode
{
protected:

	int _EattackIdx;		//적 공격시 카운트
	int	_EhultIdx;			//적 피격시 카운트
	image* _enemyImg;
	int _enemyDir;

	int _ERunAttackIdx;			//런 공격 콤보가 없어서 쓸모는 없는데 일단 만들어주자 조건을 위해
	int _ERunAttackCount;		//런 공격시 풀리는 카운트

	bool _isHitCheck;			//히트체크
	int _EHurtcount;			//피격 카운트
	animation* _enemyAni;

	enemy* _enemy;
	RECT _enemyRc;


public:
	enemyState();
	~enemyState();

	virtual HRESULT init(); //초기화
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void enemyStateChange() {};
	virtual void enemyAni() {};

	virtual void callBk();

	virtual void setEnemy(enemy* enemy) { _enemy = enemy; }

	int getEattackIdx() { return _EattackIdx; }			//공격카운트
	void setEattackIdx(int EattackIdx) { _EattackIdx = EattackIdx; }

	int getEhultIdx() { return _EhultIdx; }				//피격카운트

	int getEhurtcount() { return _EHurtcount; }			//피격 시간 카운트

	bool gethitCheck() { return _isHitCheck; }
	void sethitCheck(bool hitCheck) { _isHitCheck = hitCheck; }

	//접근자 설정자
	
	//적 애니
	virtual animation* getEnemeyAni() { return _enemyAni; }
	
	//적 이미지
	virtual image* getEnemyImg() { return _enemyImg; }
};

class enemyIdle : public enemyState		//기본
{

public:

	enemyIdle();
	~enemyIdle();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update()  override;
	virtual void render()  override;

	virtual void enemyStateChange();
	virtual void enemyAni();
};

class enemyChase : public enemyState	//추적
{

public:

	enemyChase();
	~enemyChase();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();

};

class enemyAttack : public enemyState	//공격
{

private:

	

public:

	enemyAttack();
	~enemyAttack();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();

	virtual void callBk(); //콜백
};


class enemyHurt : public enemyState		//피격
{

public:

	enemyHurt();
	~enemyHurt();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();

	virtual void callBk();
};

class enemyJump : public enemyState		//점프
{

public:

	enemyJump();
	~enemyJump();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();
};

class enemyDie : public enemyState		//죽음
{

public:

	enemyDie();
	~enemyDie();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();
};

class enemybackdown : public enemyState		//넘어짐
{

public:

	enemybackdown();
	~enemybackdown();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();
};

class enemyheld : public enemyState		//잡힘
{

public:

	enemyheld();
	~enemyheld();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();
};

class enemyWaitAttack : public enemyState //공격모션 대기
{

public:
	enemyWaitAttack();
	~enemyWaitAttack();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();

};

class enemyRun : public enemyState // 적 달리기 모션
{
public:
	enemyRun();
	~enemyRun();

	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();
};

class enemyRunAttack : public enemyState //적 달리기 공격
{
public:
	enemyRunAttack();
	~enemyRunAttack();
	
	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();

	virtual void callBk();
	

};

class enemyCompleteDeath : public enemyState //적 완전히 죽음 나중에 이걸로 지우면 될려나.
{
public:
	enemyCompleteDeath();
	~enemyCompleteDeath();


	virtual HRESULT init() override;
	virtual void release() override;
	virtual void update() override;
	virtual void render() override;

	virtual void enemyStateChange();
	virtual void enemyAni();
};