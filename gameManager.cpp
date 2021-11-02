#include "pch.h"
#include "gameManager.h"
#include "pixelCollisionClass.h"
#include "player.h"



gameManager::gameManager()
{
}

gameManager::~gameManager()
{
}

HRESULT gameManager::init()
{
	//플레이어 UI 프로필
	_playerProfile._image = IMAGEMANAGER->findImage("BATTLE_playerPortrait");
	_playerProfile._rc = RectMakeCenter(200, 70, _playerProfile._image->getWidth(), _playerProfile._image->getHeight());
	
	//플레이어 UI바
	_playerHPBar._image = IMAGEMANAGER->findImage("BATTLE_playerBar");
	_playerHPBar._rc = RectMakeCenter(450, 86, _playerHPBar._image->getWidth(), _playerHPBar._image->getHeight());

	//플레이어 HP
	_playerHP = _player->getPlayerHp();

	for (int i = 0; i < _playerHP; i++)
	{
		_playerHPPoint[i]._image = IMAGEMANAGER->findImage("BATTLE_HP");
		_playerHPPoint[i]._rc = RectMakeCenter(270 + i * 16, 53, _playerHPPoint[i]._image->getWidth(), _playerHPPoint[i]._image->getHeight());
	}

	//대화 스크립트
	scriptStart = false;
	scriptEnd = true;
	_scriptSkip = false;
	scriptImage = IMAGEMANAGER->findImage("SCENE_dialogWindow");
	scriptRc = RectMakeCenter(WINSIZEX / 2, 670, scriptImage->getWidth(), scriptImage->getHeight());
	_scriptIndex = _txtIndex = 0;
	scriptSkip = IMAGEMANAGER->findImage("SCENE_skipOutlines2");
	_vScript = TXTDATA->txtLoad("Resource/대화.txt");
	kScript = IMAGEMANAGER->findImage("SCENE_kyoko1");
	mScript = IMAGEMANAGER->findImage("SCENE_misuzu1");
	scriptName = IMAGEMANAGER->findImage("SCENE_kyokoName");

	//맵 이벤트
	mapLocked = false;
	mapUnlocked = true;
	chainTop = IMAGEMANAGER->findImage("BATTLE_stageChainTop");
	chainBottom = IMAGEMANAGER->findImage("BATTLE_stageChainBottom");
	chainLeft = IMAGEMANAGER->findImage("BATTLE_stageChainLeft");
	chainRight = IMAGEMANAGER->findImage("BATTLE_stageChainRight");
	chainLock = IMAGEMANAGER->findImage("BATTLE_lockAppear");

	/*_currentGauge = 0;
	_maxGauge = 206;

	_skip = new progressBar;
	_skip->init(WINSIZEX - 250, 20, 206, 78);
	_skip->setGauge(_currentGauge, _maxGauge);*/

	return S_OK;
}

void gameManager::release()
{
}

void gameManager::update()
{
	_playerHP = _player->getPlayerHp();
	/*_skip->setGauge(_currentGauge, _maxGauge);
	_skip->update();

	if (_currentGauge >= _maxGauge)
	{
		scriptEnd = true;
		scriptStart = false;
		_currentGauge = 0;
	}*/

	//플레이어 HP
	//if (KEYMANAGER->isOnceKeyDown(VK_F3) && _playerHP > 0)
	//{
	//	_playerHP -=1;
	//}
	//if (KEYMANAGER->isOnceKeyDown(VK_F4) && _playerHP < 24)
	//{
	//	_playerHP +=1;
	//}
	for (int i = 0; i < _playerHP; i++) 
	{
		_playerHPPoint[i]._rc = RectMakeCenter(270 + i * 16, 53, _playerHPPoint[i]._image->getWidth(), _playerHPPoint[i]._image->getHeight());
	}

	//대화 스크립트
	if (KEYMANAGER->isOnceKeyDown(VK_F1) && !scriptStart && scriptEnd)
	{
		scriptStart = true;
		scriptEnd = false;
	}

	if (!_scriptSkip)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			_scriptSkip = true;
	}
	if (_scriptSkip)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			_scriptSkip = false;
	}
	
	/*if (scriptStart && !scriptEnd)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RETURN))
		{
			_currentGauge += 2;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RETURN))
		{
			_currentGauge = 0;
		}
	}*/

	//맵 이벤트
	if (KEYMANAGER->isOnceKeyDown(VK_F2) && !mapLocked)
	{
		mapLocked = true;
	}
	

	_count++;
	if (_count % 30 == 0)
	{
		chainLock->setFrameX(_index);
		_index++;

		if (_index >= chainLock->getMaxFrameX()) _index = 6;
		_count = 0;
	}
}

void gameManager::render()
{
	_playerHPBar._image->render(getMemDC(), _playerHPBar._rc.left, _playerHPBar._rc.top);
	_playerProfile._image->render(getMemDC(), _playerProfile._rc.left, _playerProfile._rc.top);


	for (int i = 0; i < _playerHP; i++) {
		_playerHPPoint[i]._image->render(getMemDC(), _playerHPPoint[i]._rc.left, _playerHPPoint[i]._rc.top);
	}

	if (scriptStart)
	{
		scriptPlay();
		scriptImage->render(getMemDC(), scriptRc.left, scriptRc.top);
		scriptSkip->render(getMemDC(), 1070, 10); 
		scriptName->render(getMemDC(), 0, 610);

		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		RECT rcText = RectMake(190, 630, 1070, 200);

		HFONT font = CreateFont(35, 0, 0, 0, 200, false, false, false,
			DEFAULT_CHARSET, OUT_STROKE_PRECIS, CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("휴먼매직체"));

		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);

		DrawText(getMemDC(), TEXT(_txt.c_str()), _txtIndex, &rcText, DT_VCENTER | DT_VCENTER | DT_WORDBREAK);

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
	}
	if (scriptEnd)
	{
		//보스 스테이지 시작
	}

	if (mapLocked)
	{
		eventMap();
	}
	if (!mapLocked)
	{
		//카메라 움직임,.????/ 나도 잘모르겟음 *한별남김

	}

	//_skip->render();
}

void gameManager::scriptPlay()
{
	_txt = _vScript[_scriptIndex];

	if (_scriptIndex == 0 || _scriptIndex == 1 || _scriptIndex == 3 || _scriptIndex == 5 || _scriptIndex == 7 || _scriptIndex == 9 || _scriptIndex == 10)
	{
		if ( _scriptIndex == 5)
		{
			kScript = IMAGEMANAGER->findImage("SCENE_kyoko2");
		}
		if (_scriptIndex == 7 || _scriptIndex == 9 || _scriptIndex == 10)
		{
			kScript = IMAGEMANAGER->findImage("SCENE_kyoko3");
		}
		kScript->render(getMemDC(), 30, 150);
		scriptName = IMAGEMANAGER->findImage("SCENE_kyokoName");
	}
	
	if (_scriptIndex == 2 || _scriptIndex == 4 || _scriptIndex == 6 || _scriptIndex == 8 || _scriptIndex == 11)
	{
		mScript = IMAGEMANAGER->findImage("SCENE_misuzu1");
		if (_scriptIndex == 6 || _scriptIndex == 11)
		{
			mScript = IMAGEMANAGER->findImage("SCENE_misuzu2");
		}
		if (_scriptIndex == 8)
		{
			mScript = IMAGEMANAGER->findImage("SCENE_misuzu3");
		}
		mScript->render(getMemDC(), 850, 160);
		scriptName = IMAGEMANAGER->findImage("SCENE_misuzuName");
	}

	if (!_scriptSkip) {
		scriptSkip = IMAGEMANAGER->findImage("SCENE_skipOutlines2");
		if (_txtIndex < _txt.length())
		{
			_txtIndex++;
		}
		else if (_txtIndex >= _txt.length())
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_scriptSkip = false;

				_txtIndex = 0;
				_scriptIndex++;


				//Sleep(700);
			}

		}
	} 
	else if (_scriptSkip)
	{
		scriptSkip = IMAGEMANAGER->findImage("SCENE_skipOutlines1");
		if (_txtIndex >= _txt.length())
		{
			_scriptSkip = false;
			_txtIndex = 0;
			_scriptIndex++;

			//Sleep(200);
		}
		else if (_txtIndex < _txt.length())
		{
			_scriptSkip = false;
			_txtIndex = _txt.length();
		}
	}
	if (_scriptIndex >= _vScript.size())
	{
		scriptStart = false;
		scriptEnd = true;
	}
}

void gameManager::eventMap()
{
	chainTop->render(getMemDC(), 0, 0);
	chainBottom->render(getMemDC(), 0, WINSIZEY-40);
	chainLeft->render(getMemDC(), 0, 0);
	chainRight->render(getMemDC(), WINSIZEX-40, 0);

	chainLock = IMAGEMANAGER->findImage("BATTLE_lockAppear");
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		chainLock = IMAGEMANAGER->findImage("BATTLE_lockDamage1");
	}
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		chainLock = IMAGEMANAGER->findImage("BATTLE_lockDamage2");
	}
	else if (KEYMANAGER->isOnceKeyDown('3'))
	{
		chainLock = IMAGEMANAGER->findImage("BATTLE_lockDisappear");
		
		mapLocked = false;
	}
	
	chainLock->frameRender(getMemDC(), WINSIZEX / 2, 0);
}

