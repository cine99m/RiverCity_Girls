#include "pch.h"
#include "object.h"
#include "pixelCollisionClass.h" // - 삭제 가능

object::object()
{
}

object::~object()
{
}

HRESULT object::init()
{
	return S_OK;
}

HRESULT object::init(float x, float y, int objectType)
{
	_objectType = (OBJECTTYPE)objectType;

	if (_objectType == 0)_objectImg = IMAGEMANAGER->findImage("OBJECT_desk1");
	if (_objectType == 1)_objectImg = IMAGEMANAGER->findImage("OBJECT_LPillar");
	if (_objectType == 2)_objectImg = IMAGEMANAGER->findImage("OBJECT_RPillar");
	if (_objectType == 3)_objectImg = IMAGEMANAGER->findImage("OBJECT_particle1");
	if (_objectType == 4)_objectImg = IMAGEMANAGER->findImage("OBJECT_particle2");
	if (_objectType == 5)_objectImg = IMAGEMANAGER->findImage("OBJECT_particle3");

	_objectMX = x;
	_objectMY = y;

	_objectOX = _objectMX;
	_objectOY = _objectMY - (_objectImg->getHeight() / 2);

	_objectRc = RectMakeCenter(_objectOX, _objectOY, _objectImg->getWidth(), _objectImg->getHeight());
	

	return S_OK;
}

void object::release()
{
}

void object::update()
{
	_objectOX = _objectMX;
	_objectOY = _objectMY - (_objectImg->getHeight() / 2);

	_objectRc = RectMakeCenter(_objectOX, _objectOY, _objectImg->getWidth(), _objectImg->getHeight());
}

void object::render()
{
	//if (KEYMANAGER->isOnceKeyUp('J') && _pixel->setIsCheck(true))
	//{
		_objectImg->render(getMemDC(), _objectRc.left, _objectRc.top);
	//}

}
