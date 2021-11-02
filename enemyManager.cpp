#include "pch.h"
#include "enemyManager.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	//setSchoolGirl();
	//for (_viGirl = _vGirl.begin(); _viGirl != _vGirl.end(); ++_viGirl)
	for (int i = 0; i < _vGirl.size(); ++i)
	{
		_vGirl[i]->update();
	}

}

void enemyManager::render()
{
	//for (_viGirl = _vGirl.begin(); _viGirl != _vGirl.end(); ++_viGirl)
	for (int i = 0; i < _vGirl.size(); ++i)
	{
		_vGirl[i]->render();
	}
}

void enemyManager::setSchoolGirl()
{
	for (int i = 500; i < 1300; i += 200)
	{
		enemy* schoolGirl1;
		schoolGirl1 = new schoolGirl;
		schoolGirl1->init(PointMake(i, i));
		schoolGirl1->getEnemyState()->setEnemy(schoolGirl1);
		_vGirl.push_back(schoolGirl1);
	
	}
	//enemy* schoolGirl1;
	//schoolGirl1 = new schoolGirl;
	//schoolGirl1->init(PointMake(300, 300));
	//schoolGirl1->getEnemyState()->setEnemy(schoolGirl1);
	//_vGirl.push_back(schoolGirl1);
	//
	//enemy* schoolGirl2;
	//schoolGirl2 = new schoolGirl;
	//schoolGirl2->init(PointMake(500, 500));
	//schoolGirl2->getEnemyState()->setEnemy(schoolGirl2);
	//_vGirl.push_back(schoolGirl2);
	//
	//enemy* schoolGirl3;
	//schoolGirl3 = new schoolGirl;
	//schoolGirl3->init(PointMake(800, 800));
	//schoolGirl3->getEnemyState()->setEnemy(schoolGirl3);
	//_vGirl.push_back(schoolGirl3);
}

void enemyManager::removeSchoolGirl(int arrNum)
{

	_vGirl.erase(_vGirl.begin() + arrNum);

}

