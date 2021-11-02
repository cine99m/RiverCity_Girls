#include "pch.h"
#include "objectManager.h"

objectManager::objectManager()
{
}

objectManager::~objectManager()
{
}

HRESULT objectManager::init()
{
	return S_OK;
}

void objectManager::release()
{
}

void objectManager::update()
{
	//for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	//{
	//	(*_viObject)->update();
	//}

	for (int i = 0; i < _vObject.size(); ++i)
	{
		//_vObject[i]->setObjectMX(_vObject[i]->getObjectMX());
		//_vObject[i]->setObjectMY(_vObject[i]->getObjectMY());
		_vObject[i]->update();
	}
}

void objectManager::render()
{
	//for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	//{
	//	(*_viObject)->render();
	//}

	for (int i = 0; i < _vObject.size(); ++i)
	{
		//_vObject[i]->setObjectMX(_vObject[i]->getObjectMX());
		//_vObject[i]->setObjectMY(_vObject[i]->getObjectMY());
		_vObject[i]->render();
	}
}

void objectManager::setObject()
{
	//int num = 0;  
	//
	//for (int i = 0; i < 6; i++)
	//{
	//	switch (num)
	//	{
	//	case 0://Ã¥»ó - º¹±¸ °¡´É
	//		
				for (int j = 0; j < 2; j++)
				{
					object* object;
					object = new desk;
					object->init(1028 - j * 200, 665 + j * 200, DESK);
					_vObject.push_back(object);
				}
			//}
			//break;
		//case 1://ÁÂÃø ±âµÕ
		//{
		//	for (int j = 0; j < 2; j++)
		//	{
		//		object* object;
		//		object = new LPillar;
		//		object->init((WINSIZEX / 2) - 30, 300 + j * 300, LPILLAR);
		//		_vObject.push_back(object);
		//	}
		//}
		//break;
		//case 2://¿ìÃø ±âµÕ
		//{
		//	for (int j = 0; j < 2; j++)
		//	{
		//		object* object;
		//		object = new RPillar;
		//		object->init((WINSIZEX / 2) + 300, 300 + j * 300, RPILLAR);
		//		_vObject.push_back(object);
		//	}
		//}
		//break;
		//case 3://±âµÕ ÆÄÆí1
		//{
		//	for (int j = 0; j < 10; j++)
		//	{
		//		object* object;
		//		object = new particle;
		//		object->init(WINSIZEX / 2, WINSIZEY / 2, PARTICLE1);
		//		_vObject.push_back(object);
		//	}
		//}
		//break;
		//case 4://±âµÕ ÆÄÆí2
		//{
		//	for (int j = 0; j < 10; j++)
		//	{
		//		object* object;
		//		object = new particle;
		//		object->init(WINSIZEX / 2, WINSIZEY / 2, PARTICLE2);
		//		_vObject.push_back(object);
		//	}
		//}
		//break;
		//case 5://±âµÕ ÆÄÆí3
		//{
		//	for (int j = 0; j < 10; j++)
		//	{
		//		object* object;
		//		object = new particle;
		//		object->init(WINSIZEX / 2, WINSIZEY / 2, PARTICLE3);
		//		_vObject.push_back(object);
		//	}
		//}
		//break;
		//}

	//}

}
