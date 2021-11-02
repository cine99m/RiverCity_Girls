#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "boss.h"
#include "schoolGirl.h"
#include <vector>
#include "camera.h"



class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>					vGirl;
	typedef vector<enemy*>::iterator		viGirl;



	enemy* _enemy;

	vGirl _vGirl;
	viGirl _viGirl;
	camera* _cam;

public:
	
	enemyManager();
	~enemyManager();

	virtual HRESULT init();			//초기화 함수
	virtual void release();			//메모리 해제 함슈
	virtual void update();			//연산하는 함수
	virtual void render();			//그리기 함수


	void setSchoolGirl();

	void removeSchoolGirl(int arrNum);

	vGirl getVGirl() { return _vGirl; }
	viGirl getVIGirl() { return _viGirl; }

	void setCam(camera* cam) { _cam = cam; }
};