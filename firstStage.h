#pragma once
#include "gameNode.h"
//#include "camera.h"
//#include "player.h"
//#include "enemy.h"
//#include "boss.h"
//#include "state.h"

//#include "camera.h"
//#include "player.h"
//#include "enemy.h"
//#include "boss.h"
//#include "state.h"
//#include "objectManager.h"
#include "zOrder.h"


class pixelCollisionClass;

//±³½Ç
class firstStage : public gameNode
{
private:

	//typedef vector<gameNode*>				arrRender;
	//typedef vector<gameNode*>::iterator		iterRender;

	//arrRender _vRender;
	//iterRender _viRender;




	//image* _first;
	
	//camera* _camera;
	//player* _player;
	//enemy* _enemy;
	//boss* _boss;

	//objectManager* _object;

	//camera* _camera;
	//player* _player;
	//enemy* _enemy;
	//boss* _boss;

	zOrder* _zO;




	//pixelCollisionClass* _pixel;

public:
	firstStage();
	~firstStage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//void setPlayer(player* player) { _player = player; }

	//void setpixelCollisionClassMemoryAddressLink(pixelCollisionClass* pixel) { _pixel = pixel; }

	//void selectionSort();
	//void swap(gameNode** a, gameNode** b);
};

