#include "pch.h"
#include "bossStage1.h"
#include "pixelCollisionClass.h"

bossStage1::bossStage1()
{
}

bossStage1::~bossStage1()
{
}

HRESULT bossStage1::init()
{

	//IMAGEMANAGER->findImage("STAGE_bossStage1");

	/*
	_x = 800;
	_y = WINSIZEY / 2;

	_rc = RectMakeCenter(_x, _y, 10, 1080);

	_camera = new camera;
	_camera->init();
	_camera->setStage(3);

	_player = new player;
	_player->init();
	_player->setCamera(_camera);

	_pixel = new pixelCollisionClass;

	_pixel->init(0, 0, 3);
	_pixel->setPixelPlayer(_player);
	_pixel->setCAMERAMemoryAddressLink(_camera);		//카메라 값 연동
	*/
	_zO = new zOrder;
	_zO->init();


	return S_OK;
}

void bossStage1::release()
{
}

void bossStage1::update()
{
	_zO->update();
	/*
	_player->update();

	_player->getState()->setPlayer(_player);

	_pixel->setPixelPlayer(_player);
	_pixel->update();
	*/
}

void bossStage1::render()
{
	_zO->render();
	/*_camera->render();

	if (KEYMANAGER->isToggleKey(VK_F8))
	{
		_pixel->render();
	}

	_player->render();*/
}
