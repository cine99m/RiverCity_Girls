#include "pch.h"
#include "secondStage.h"
#include "pixelCollisionClass.h"

secondStage::secondStage()
{
}

secondStage::~secondStage()
{
}

HRESULT secondStage::init()
{
	IMAGEMANAGER->findImage("STAGE_stage4");
	IMAGEMANAGER->findImage("BATTLE_unlockDoor1");
	IMAGEMANAGER->findImage("BATTLE_unlockDoor2");

	
	_enemy = new enemy;
	_enemy->init();

	_camera = new camera;
	_camera->init();
	_camera->setStage(1);

	_player = new player;
	_player->init();
	_player->setCamera(_camera);

	_enemy->setPlayerMemoryLink(_player);				//플레이어 연동

	_pixel = new pixelCollisionClass;

	_pixel->init(0, 0, 1);
	_pixel->setPixelPlayer(_player);
	_pixel->setCAMERAMemoryAddressLink(_camera);		//카메라 값 연동

	
	return S_OK;
}

void secondStage::release()
{
}

void secondStage::update()
{
	
	_player->update();

	_player->getState()->setPlayer(_player);

	
	_pixel->setPixelPlayer(_player);
	_pixel->update();
	

	_enemy->update();
	_enemy->getEnemyState()->setEnemy(_enemy);
	
}

void secondStage::render()
{
	_camera->render();

	
	if (KEYMANAGER->isToggleKey(VK_F8))
	{
		_pixel->render();
	}
	
	_player->render();
	_enemy->render();
	
	
}
