#pragma once
#include "gameNode.h"
#include "camera.h"
#include "player.h"
#include "state.h"
#include "zOrder.h"

class pixelCollisionClass;

//보스방(등장 전)
class bossStage1 : public gameNode
{
private:

	zOrder* _zO;
	//오브젝트
	float _X, _Y;

	//충돌용
	RECT _rc;
	float _x, _y;

	camera* _camera;
	player* _player;

	pixelCollisionClass* _pixel;

public:
	bossStage1();
	~bossStage1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayer(player* player) { _player = player; }

	void setpixelCollisionClassMemoryAddressLink(pixelCollisionClass* pixel) { _pixel = pixel; }
};

