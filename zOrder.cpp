#include "pch.h"
#include "zOrder.h"
#include "pixelCollisionClass.h"

zOrder::zOrder()
{
}


zOrder::~zOrder()
{
}

HRESULT zOrder::init()
{
	//_vRender.push_back(_player);
	//_vRender.push_back(_enemy);
	//_vRender.push_back(_boss);

	_player = new player;
	_camera = new camera;
	_boss = new boss;
	_enemy = new enemy;
	_pixel = new pixelCollisionClass;
	_objectManager = new objectManager;
	_enemyManager = new enemyManager;
	_gaM = new gameManager;



	_camera->setStage((int)stageImg::FIRST_STAGE);




	//_enemy = new enemy;
	//_enemy->init();


	_enemyManager->init();
	_enemyManager->setSchoolGirl();
	
	_player->init();
	_player->setCamera(_camera);
	_player->setBossMemoryAddressLink(_boss);
	_player->setEnemyMemoryAddressLink(_enemy);
	_player->setGm(_gaM);
	

	_boss->setPlayerMemoryAddressLink(_player);
	_boss->setCameraMemoryAddressLink(_camera);



	_objectManager->init();
	_objectManager->setObject();



	_pixel->init(0, 0, 0);
	_pixel->setPixelPlayer(_player);
	_pixel->setCAMERAMemoryAddressLink(_camera);		//ī�޶� �� ����
	_pixel->setGameManager(_gaM);
	_player->setObjectManagerMemoryAddressLink(_objectManager);

	_gaM->setPixelM(_pixel);
	_gaM->setPlayer(_player);
	
	
	_gaM->init();


	_camera->init();


	_boss->init();
	
	_enemy->init();

	_player->init();






		for (int i = 0; i < _enemyManager->getVGirl().size(); )
		{
			_player->setEnemyManagerMemoryAddressLink(_enemyManager);
			_enemyManager->getVGirl()[i]->setPlayerMemoryLink(_player);

			++i;
		}
	


	_enemy->setPlayerMemoryLink(_player);				//�÷��̾� ����
	_enemy->setCameraMemoryLink(_camera);				//ī�޶� ����

	for (int i = 0; i < _objectManager->getVObject().size();)
	{
		_player->setObjectManagerMemoryAddressLink(_objectManager);
		_objectManager->getVObject()[i]->setPlayerMemoryAddrsLink(_player);

		++i;
	}


	//�־��ش�.
	_vRender.push_back(_player);
	//_vRender.push_back(_enemy);

	//_vRender.push_back(_boss);

	
	for (int i = 0; i < _objectManager->getVObject().size(); ++i)
	{
		_vRender.push_back(_objectManager->getVObject()[i]);
	}

	//_ef = new effect;
	//_ef->init(IMAGEMANAGER->addFrameImage("smash", "resources/IMG/effect/Boss smash.bmp", 960, 89, 10, 1, true, RGB(255, 0, 255)), 96, 89, 1, 0.5f);


		for (int i = 0; i < _enemyManager->getVGirl().size(); ++i)
		{
			//_vRender.push_back(_enemyManager->getVGirl()[i]);
		}
	


	//_vRender.push_back(_enemyManager);
	//_vRender.push_back(_boss);


	return S_OK;
}

void zOrder::release()
{

}

void zOrder::update()
{
	EFFECTMANAGER->update();

	_player->update();

	_player->getState()->setPlayer(_player);

	_boss->setPlayerMemoryAddressLink(_player);

	
	//_boss->update();
	
	_objectManager->update();

	_pixel->setPixelPlayer(_player);
	_pixel->update();

	//_enemy->update();
	//_enemy->getEnemyState()->setEnemy(_enemy);

		//_enemyManager->update();
	


	_camera->update();

	_gaM->update();
	selectionSort();

	//
	//if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	//{
	//	//_ef->startEffect(WINSIZEX / 2, WINSIZEY / 2);
	//	IMAGEMANAGER->addFrameImage("smash", "resources/IMG/effect/Boss smash.bmp", 960, 89, 10, 1, true, RGB(255, 0, 255));
	//	IMAGEMANAGER->frameRender("smash", getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
	//}
	//
	//_ef->update();

	//zOrder();
}

void zOrder::render()
{

	_camera->render();
	

	if (KEYMANAGER->isToggleKey(VK_F8))
	{
		_pixel->render();
	}
	EFFECTMANAGER->render();


	for (_viRender = _vRender.begin(); _viRender != _vRender.end(); ++_viRender)
	{
		(*_viRender)->render();
	}
	//_ef->render();
	_gaM->render();
	char str[128];
	
	sprintf_s(str, "vecterSize : %d", _vRender.size());
	TextOut(getMemDC(), 1000, 100, str, strlen(str));

	sprintf_s(str, "getstage : %d", _camera->getstage());
	TextOut(getMemDC(), 1000, 200, str, strlen(str));
}


void zOrder::selectionSort()
{
	int minIndex;
	int i, j;

	// ��ü�� ���� ����ũ�⸸ for�� ������ Ȯ�� ! ���ͳ����� �׻� null���� �����ؼ� -1 ����!!!!

	for (i = 0; i < _vRender.size() - 1; i++)
	{
		//for ���� �� �ϳ����ø��鼭 Ȯ���� min���� �״��
		minIndex = i;
		//for������ j = �� ���� ��� 0 ,1 �����ϱ����ؼ�  �������� �������� ��������
		for (j = i + 1; j < _vRender.size(); j++)
		{
			//j�� minindex
			if (_vRender[j]->getPosY() < _vRender[minIndex]->getPosY())
			{ //������ Y���� �����ͼ� ���Ͽ� ����.
				//�ٲ����� �갡 min�� ��
				minIndex = j;
			}
		}


		swap(&_vRender[i], &_vRender[minIndex]); //render ���� ����

	}
}

void zOrder::swap(gameNode** a, gameNode** b)
{
	gameNode* temp = *a;
	*a = *b;
	*b = temp;
}
