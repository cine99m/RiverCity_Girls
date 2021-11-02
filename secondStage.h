#pragma once
#include "gameNode.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"
#include "state.h"

class pixelCollisionClass;

//±³¹«½Ç
class secondStage : public gameNode
{
private:

	camera* _camera;
	player* _player;
	enemy* _enemy;
	boss* _boss;

	pixelCollisionClass* _pixel;

public:
	secondStage();
	~secondStage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayer(player* player) { _player = player; }

	void setpixelCollisionClassMemoryAddressLink(pixelCollisionClass* pixel) { _pixel = pixel; }
};

