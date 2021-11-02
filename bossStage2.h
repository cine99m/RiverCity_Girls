#pragma once
#include "gameNode.h"
#include "camera.h"
#include "player.h"
#include "boss.h"
#include "state.h"

class pixelCollisionClass;

//보스방(등장 후)
class bossStage2 : public gameNode
{
private:
	camera* _camera;
	player* _player;
	boss* _boss;

	pixelCollisionClass* _pixel;

public:
	bossStage2();
	~bossStage2();
	
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayer(player* player) { _player = player; }

	void setpixelCollisionClassMemoryAddressLink(pixelCollisionClass* pixel) { _pixel = pixel; }
};

