#include "pch.h"
#include "bossStage2.h"
#include "pixelCollisionClass.h"

bossStage2::bossStage2()
{
}

bossStage2::~bossStage2()
{
}

HRESULT bossStage2::init()
{
	IMAGEMANAGER->findImage("STAGE_bossStage2");

	//_boss = new boss;
	//_boss->setPlayerMemoryAddressLink(_player);
	//_boss->init();

	//_camera = new camera;
	//_camera->init();
	//_camera->setStage(3);

	//_player = new player;
	//_player->init();
	//_player->setCamera(_camera);

	//_pixel = new pixelCollisionClass;

	//_pixel->init(0, 0, 3);
	//_pixel->setPixelPlayer(_player);
	//_pixel->setCAMERAMemoryAddressLink(_camera);		//카메라 값 연동

	return S_OK;
}

void bossStage2::release()
{
}

void bossStage2::update()
{
	/*_player->update();

	_player->getState()->setPlayer(_player);

	_boss->setPlayerMemoryAddressLink(_player);
	_boss->update();

	_pixel->setPixelPlayer(_player);
	_pixel->update();*/
}

void bossStage2::render()
{
	//_camera->render();

	//if (KEYMANAGER->isToggleKey(VK_F8))
	//{
	//	_pixel->render();
	//}

	//_player->render();
	//_boss->render();
}
