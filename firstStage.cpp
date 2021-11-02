#include "pch.h"
#include "firstStage.h"
#include "pixelCollisionClass.h"

firstStage::firstStage()
{
}

firstStage::~firstStage()
{
}

HRESULT firstStage::init()
{
	//IMAGEMANAGER->findImage("STAGE_stage1");
	
	//_camera = new camera;
	//_camera->init();
	//_camera->setStage(SECOND_STAGE);
	// 
	//


	//_boss = new boss;
	//
	//_player->init();
	//_player->setCamera(_camera);
	//_player->setBossMemoryAddressLink(_boss);
	//
	//_boss->setPlayerMemoryAddressLink(_player);
	//_boss->setCameraMemoryAddressLink(_camera);
	//_boss->init();
	//
	//_enemy = new enemy;
	//_enemy->init();
	//

	//_boss = new boss;
	//_boss->setPlayerMemoryAddressLink(_player);
	//_boss->setCameraMemoryAddressLink(_camera);
	//_boss->init();

	//_enemy = new enemy;
	//_enemy->init();

	//_player = new player;
	//_player->init();
	//_player->setCamera(_camera);
	//_player->setBossMemoryAddressLink(_boss);
	// 
	//_enemy->setPlayerMemoryLink(_player);				//플레이어 연동
	//_enemy->setCameraMemoryLink(_camera);				//카메라 연동

	//_pixel = new pixelCollisionClass;

	//_pixel->init(0, 0, 0);
	//_pixel->setPixelPlayer(_player);
	//_pixel->setCAMERAMemoryAddressLink(_camera);		//카메라 값 연동
	//_camera->setStage(0);
	
	// Hangil
	//_object = new objectManager;
	//_object->init();
	//_object->setObject();
	//
	//_player = new player;
	//_player->init();
	//_player->setCamera(_camera);
	//_player->setBossMemoryAddressLink(_boss);
	//_player->setObjectMemoryAddressLink(_object);

	//_player = new player;
	//_player->init();
	//_player->setCamera(_camera);
	//_player->setBossMemoryAddressLink(_boss);
	//_player->setEnemyMemoryAddressLink(_enemy);


	_zO = new zOrder;
	_zO->init();


	//vrender 벡터에 랜더할 클래스를 넣는다.
	//_vRender.push_back(_player);
	//_vRender.push_back(_enemy);
	//_vRender.push_back(_boss);


	//_vRender.push_back(_player);
	//_vRender.push_back(_enemy);

	return S_OK; 
}

void firstStage::release()
{
}

void firstStage::update()
{
	
	//
	//_player->getState()->setPlayer(_player);
	//
	//_boss->update();
	//_boss->setPlayerMemoryAddressLink(_player);
	//
	//_boss->update();
	//
	//_boss->update();
	//
	//
	//_pixel->setPixelPlayer(_player);
	//_pixel->update();
	//

	//_player->getState()->setPlayer(_player);

	//////////////////////////////////////////////////////////////////////////
	//_object->update();
	//
	//_player->getState()->setPlayer(_player);
	//////////////////////////////////////////////////////////////////////////

	//_boss->setPlayerMemoryAddressLink(_player);

	//_boss->update();

	//_boss->update();


	//_pixel->setPixelPlayer(_player);
	//_pixel->update();

	//_enemy->update();
	//_enemy->getEnemyState()->setEnemy(_enemy);

	//pixelCollision();

	_zO->update();
	//EFFECTMANAGER->update();
	//selectionSort();
}

void firstStage::render()
{
	//_camera->render();

	//if (KEYMANAGER->isToggleKey(VK_F8))
	//{
	//	_pixel->render();
	//}

	//_camera->render();
	////_object->render();
	//if (KEYMANAGER->isToggleKey(VK_F8))
	//{
	//	_pixel->render();
	//}
	_zO->render();
	//EFFECTMANAGER->render();


	//_zO->render();
	//_object->render();

	//_camera->render();
	//_player->render();
	//_enemy->render();
	//_boss->render();

	//게임노드의 객체를 상속받는 객체의 실질적 렌더
	//for (_viRender = _vRender.begin(); _viRender != _vRender.end(); _viRender++)
	//{
	//	(*_viRender)->render();
	//}
}

//선택정렬 함수
//void firstStage::selectionSort()
//{
//	int minIndex;
//	int i, j;
//
//	// 객체를 담은 벡터크기만 for을 돌려서 확인 ! 벡터끝에는 항상 null값이 존재해서 -1 해줌!!!!
//
//	for (i = 0; i < _vRender.size() - 1; i++)
//	{
//		//내가 빡대가리 .
//		//for 문에 서 하나씩올리면서 확인줌 min값은 그대상
//		minIndex = i;
//		//for문에서 j = 그 다음 대상 0 ,1 을비교하기위해서  이중포문 개념으로 접근하자
//		for (j = i + 1; j < _vRender.size(); j++) 
//		{
//			//j랑 minindex
//			if (_vRender[j]->getPosY() < _vRender[minIndex]->getPosY())
//			{ //렌더의 Y값을 가져와서 비교하여 스왑.
//				//바꿨을때 얘가 min이 됨
//				minIndex = j;
//			}
//		}
//
//		swap(&_vRender[i], &_vRender[minIndex]); //render
//	}
//}

//클래스 스왑
//void firstStage::swap(gameNode** a, gameNode** b)
//{
//	//gameNode 
//	gameNode* temp = *a;
//	*a = *b;
//	*b = temp;
//
//	//_player->render();
//	//_enemy->render();
//	//_boss->render();
//
//}

	//게임노드의 객체를 상속받는 객체의 실질적 렌더
	/*for (_viRender = _vRender.begin(); _viRender != _vRender.end(); _viRender++)
	{
		(*_viRender)->render();

	}*/
	//_boss->render();


//선택정렬 함수
//void firstStage::selectionSort()
//{
//	//int minIndex;
//	//int i, j;
//
//	//// 객체를 담은 벡터크기만 for을 돌려서 확인 ! 벡터끝에는 항상 null값이 존재해서 -1 해줌!!!!
//
//	//for (i = 0; i < _vRender.size() - 1; i++)
//	//{
//	//	//내가 빡대가리 .
//	//	//for 문에 서 하나씩올리면서 확인줌 min값은 그대상
//	//	minIndex = i;
//	//	//for문에서 j = 그 다음 대상 0 ,1 을비교하기위해서  이중포문 개념으로 접근하자
//	//	for (j = i + 1; j < _vRender.size(); j++) 
//	//	{
//	//		//j랑 minindex
//	//		if (_vRender[j]->getPosY() < _vRender[minIndex]->getPosY())
//	//		{ //렌더의 Y값을 가져와서 비교하여 스왑.
//	//			//바꿨을때 얘가 min이 됨
//	//			minIndex = j;
//	//		}
//	//	}
//
//
//	//	swap(&_vRender[i], &_vRender[minIndex]); //render
//	//
//	//}
//}
//
////클래스 스왑
//void firstStage::swap(gameNode** a, gameNode** b)
//{
//	//gameNode 
//	//gameNode* temp = *a;
//	//*a = *b;
//	//*b = temp;
//
//	////_player->render();
//	////_enemy->render();
//	////_boss->render();
//
//}
