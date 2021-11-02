#include "pch.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기에다 해라!!!
HRESULT playGround::init()
{
	gameNode::init(true);

	_streamSwitch = true;

	//_imageStorage = new imageStorage;
	//_imageStorage->init();

	//_sfxStorage = new sfxStorage;
	//_sfxStorage->init();

	//_gameManager = new gameManager;
	//_gameManager->init();



	SCENEMANAGER->addScene("imageStorage", new imageStorage);

	//스테이지(씬 매니저)
	SCENEMANAGER->addScene("introVid", new introVideo);
	SCENEMANAGER->addScene("stage1", new firstStage);
	//SCENEMANAGER->addScene("stage2", new secondStage);
	//SCENEMANAGER->addScene("stage3", new thirdStage);
	//SCENEMANAGER->addScene("bossStage1", new bossStage1);
	//SCENEMANAGER->addScene("bossStage2", new bossStage2);
	SCENEMANAGER->changeScene("introVid");



	return S_OK;
}

//메모리 해제는 여기다 해라!!!!
void playGround::release()
{
	gameNode::release();

	//_gameManager->release();
}

//연산처리는 여기다가!
void playGround::update()
{
	gameNode::update();

	//_gameManager->update();

	//EFFECTMANAGER->update();

	/*if (KEYMANAGER->isOnceKeyDown('4'))
	{
		SCENEMANAGER->changeScene("stage1");
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		SCENEMANAGER->changeScene("stage2");
	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		SCENEMANAGER->changeScene("stage3");
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		SCENEMANAGER->changeScene("bossStage1");
	}
	if (KEYMANAGER->isOnceKeyDown('8'))
	{
		SCENEMANAGER->changeScene("bossStage2");
	}
	//if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	//{
	//	//_ef->startEffect(WINSIZEX / 2, WINSIZEY / 2);
	//	IMAGEMANAGER->addFrameImage("smash", "resources/IMG/effect/Boss smash.bmp", 960, 89, 10, 1, true, RGB(255, 0, 255));
	//	IMAGEMANAGER->frameRender("smash", getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
	//}
	}*/

	//스테이지(씬 매니저)
	SCENEMANAGER->update();
}

//여기다 그려줘라!!!
void playGround::render()
{
	if (_streamSwitch)
	{
		SCENEMANAGER->render();
	}
	else
	{
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		//==============위에는 제발 건드리지 마라 ============

		//스테이지(씬 매니저)
		SCENEMANAGER->render();

		//_gameManager->render();

		//EFFECTMANAGER->render();

		//=============== 밑에도 건들지마라 ================
		_backBuffer->render(getHDC(), 0, 0);
	}
}