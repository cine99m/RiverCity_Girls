#include "pch.h"
#include "pixelCollisionClass.h"
#include "player.h"
#include "gameManager.h"

pixelCollisionClass::pixelCollisionClass()
{
}

pixelCollisionClass::~pixelCollisionClass()
{
}

HRESULT pixelCollisionClass::init()
{

	return S_OK;
}

HRESULT pixelCollisionClass::init(float x, float y, int stageType)
{
	_stageType = (STAGETYPE)stageType;
	
	if (_stageType == FIRSTSTAGE) _stage = IMAGEMANAGER->findImage("STAGE_stagePixel1");
	if (_stageType == 1) _stage = IMAGEMANAGER->findImage("STAGE_stagePixel4");
	if (_stageType == THIRDSTAGE) _stage = IMAGEMANAGER->findImage("STAGE_normalPixel");
	if (_stageType == BOSSSTAGE) _stage = IMAGEMANAGER->findImage("STAGE_bossPixel");

	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _stage->getWidth(), _stage->getHeight());

	_camera = new camera;
	_camera->init();

	_stageType = FIRSTSTAGE;

	_isCheck = false;

	return S_OK;
}

void pixelCollisionClass::release()
{
}

void pixelCollisionClass::update()
{
	_probeLX = _player->getShadowX() - (_player->getShadowImg()->getWidth()  / 2 +10);
	_probeRX = _player->getShadowX() + (_player->getShadowImg()->getWidth()  / 2 -10);
	_probeTY = _player->getShadowY() - (_player->getShadowImg()->getHeight() / 2 +10);
	_probeBY = _player->getShadowY() + (_player->getShadowImg()->getHeight() / 2 -10);
	_probeMid = _player->getShadowY();

	/*if (_stageType == FIRSTSTAGE) _stage = IMAGEMANAGER->findImage("STAGE_stagePixel1");
	if (_stageType == 1) _stage = IMAGEMANAGER->findImage("STAGE_stagePixel4");
	if (_stageType == THIRDSTAGE) _stage = IMAGEMANAGER->findImage("STAGE_normalPixel");
	if (_stageType == BOSSSTAGE) _stage = IMAGEMANAGER->findImage("STAGE_bossPixel");*/

	_stage = _camera->getPixImage();

	//_dir = _player->getDir();

	Colloision();
}

void pixelCollisionClass::render()
{
//	char str[128];
	
//	sprintf_s(str, "%0.2f,%0.2f", _camera->getCamY(), _player->getShadowY());

//	TextOut(getMemDC(), 0, WINSIZEY / 2, str, strlen(str));

	//_stage->render(getMemDC(), 0 - _camera->getCamX(), 0 - _camera->getCamY());
}

void pixelCollisionClass::Colloision()
{	
		for (int i = _probeLX - 1; i < _probeLX + 1; i++)  // 좌우
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i + _camera->getCamX(), _player->getShadowY() + _camera->getCamY());

			int R = GetRValue(color);
			int G = GetGValue(color);
			int B = GetBValue(color);

			if (_player->getIsJump())
			{
				if ((R == 255 && G == 0 && B == 0) || (R == 0 && G == 255 && B == 0))			//레드
				{
					_player->setLK(true);
				}
			}
			else
			{
				_player->setLK(false);
			}


				//아이콘 출현 구간
				if (R == 0 && G == 255 && B == 255 && KEYMANAGER->isOnceKeyDown('J'))	//민트 스테이지2 넘어갈 때
				{
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
					//특정 키 입력시 다음 스테이지로 이동
					_camera->setStage(2);
					_player->setShadowX(200);
					_player->setShadowY(580);
					_camera->setCamX(0);
					_camera->setCamY(100);
					_stageType = THIRDSTAGE;
				} 
				else if (R == 100 && G == 0 && B == 100 && KEYMANAGER->isOnceKeyDown('J'))	//스테이지2에서 스테이지1 넘어갈 때
				{
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
					//특정 키 입력시 다음 스테이지로 이동
					_camera->setStage(0);
					_player->setShadowX(669);
					_player->setShadowY(423);
					_camera->setCamX(1239);
					_camera->setCamY(110);
					_stageType = FIRSTSTAGE;
				}
				else if (R == 100 && G == 100 && B == 100 && KEYMANAGER->isOnceKeyDown('J'))	//스테이지2에서 스테이지3 넘어갈 때
				{
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
					//특정 키 입력시 다음 스테이지로 이동
					_camera->setStage(3);
					_player->setShadowX(400);
					_player->setShadowY(540);
					_camera->setCamX(0);
					_camera->setCamY(210);
					_stageType = BOSSSTAGE;
					_gM->setScriptStart(true);
				}
				

		}
	
		for (int i = _probeTY - 1; i < _probeTY +1 ; i++)	// 위아래
		{
			COLORREF color = GetPixel(_stage->getMemDC(), _player->getShadowX() + _camera->getCamX(), i + _camera->getCamY());

			int R = GetRValue(color);
			int G = GetGValue(color);
			int B = GetBValue(color);

				if ((R == 255 && G == 0 && B == 0) || (R == 0 && G == 255 && B == 0))			//레드
				{
					_player->setUK(true);
				}
				else if ((R == 0 && G == 255 && B == 0) && _player->getIsJump())
				{
					_player->setUK(false);
				}
				else
				{
					_player->setUK(false);
				}

		
				//책상 바닥
				if ((R == 0 && G == 255 && B == 0))	//그린 - 0으로 변경
				{

					if (KEYMANAGER->isOnceKeyUp(VK_UP))
					{
						_player->setShadowY(_player->getShadowY() + _player->getSpeed() * 1.5);


						_player->setSpeed(0);
					}

					if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
					{
						_player->setShadowY(_player->getShadowY() - _player->getSpeed() * 1.5);
					}

					_player->setSpeed(0);
				}

				//아이콘 출현 구간
				if ((R == 0 && G == 255 && B == 255) && KEYMANAGER->isOnceKeyDown('J'))	//민트 스테이지2 넘어갈 때
				{
					_isCheck = false;
					//_player->setSpeed(6);
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
						_camera->setStage(2);
						_player->setShadowX(200);
						_player->setShadowY(580);
						_camera->setCamX(0);
						_camera->setCamY(100);
						_stageType = THIRDSTAGE;
				}
				else if (R == 100 && G == 0 && B == 100 && KEYMANAGER->isOnceKeyDown('J'))	//스테이지2에서 스테이지1 넘어갈 때
				{
					_isCheck = true;
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력 _isCheck->setIsCheck(getIsCheck()) == true
					//특정 키 입력시 다음 스테이지로 이동
					_camera->setStage(0);
					_player->setShadowX(669);
					_player->setShadowY(423);
					_camera->setCamX(1239);
					_camera->setCamY(110);
					_stageType = FIRSTSTAGE;
				}
				else if (R == 100 && G == 100 && B == 100 && KEYMANAGER->isOnceKeyDown('J'))	//스테이지2에서 보스 스테이지 넘어갈 때
				{
					_isCheck = false;
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
					//특정 키 입력시 다음 스테이지로 이동
					_camera->setStage(3);
					_player->setShadowX(400);
					_player->setShadowY(540);
					_camera->setCamX(0);
					_camera->setCamY(210);
					_stageType = BOSSSTAGE;
					_gM->setScriptStart(true);
				}

		}
		
		
		for (int i = _probeRX - 1; i < _probeRX + 1; i++)  // 좌우
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i + _camera->getCamX(), _player->getShadowY() + _camera->getCamY());

			int R = GetRValue(color);
			int G = GetGValue(color);
			int B = GetBValue(color);

			if ((R == 255 && G == 0 && B == 0) || (R == 0 && G == 255 && B == 0))			//레드
			{
				_player->setRK(true);
			}
			else if ((R == 0 && G == 255 && B == 0) && _player->getIsJump())
			{
				_player->setRK(false);
			}
			else
			{
				_player->setRK(false);
			}


				//아이콘 출현 구간
				if (R == 0 && G == 255 && B == 255 && KEYMANAGER->isOnceKeyDown('J'))	//민트 스테이지2 넘어갈 때
				{
					_isCheck = false;
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
					//특정 키 입력시 다음 스테이지로 이동
					_camera->setStage(2);
					_player->setShadowX(200);
					_player->setShadowY(580);
					_camera->setCamX(0);
					_camera->setCamY(100);
					_stageType = THIRDSTAGE;
				}
				else if (R == 100 && G == 0 && B == 100 && KEYMANAGER->isOnceKeyDown('J'))	//스테이지2에서 스테이지1 넘어갈 때
				{
					_isCheck = true;
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
					//특정 키 입력시 다음 스테이지로 이동
					_camera->setStage(0);
					_player->setShadowX(669);
					_player->setShadowY(423);
					_camera->setCamX(1239);
					_camera->setCamY(110);
					_stageType = FIRSTSTAGE;
				}
				else if (R == 100 && G == 100 && B == 100 && KEYMANAGER->isOnceKeyDown('J'))	//스테이지2에서 스테이지3 넘어갈 때
				{
					_isCheck = false;
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
					//특정 키 입력시 다음 스테이지로 이동
					_camera->setStage(3);
					_player->setShadowX(400);
					_player->setShadowY(540);
					_camera->setCamX(0);
					_camera->setCamY(210);
					_stageType = BOSSSTAGE;
					_gM->setScriptStart(true);
					
				}

		}
		
		

		for (int i = _probeBY - 1; i < _probeBY + 1; i++)	// 위아래
		{
			COLORREF color = GetPixel(_stage->getMemDC(), _player->getShadowX() + _camera->getCamX(), i + _camera->getCamY());

			int R = GetRValue(color);
			int G = GetGValue(color);
			int B = GetBValue(color);

			if ((R == 255 && G == 0 && B == 0) || (R == 0 && G == 255 && B == 0))			//레드
			{
				_player->setDK(true);
			}
			else if ((R == 0 && G == 255 && B == 0)&&_player->getIsJump())
			{
				_player->setDK(false);
			}
			else
			{
				_player->setDK(false);
			}
		

				//아이콘 출현 구간
				if ((R == 0 && G == 255 && B == 255) && KEYMANAGER->isOnceKeyDown('J'))	//민트 스테이지2 넘어갈 때
				{
					//_player->setSpeed(6);
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
					_camera->setStage(2);
					_player->setShadowX(200);
					_player->setShadowY(580);
					_camera->setCamX(0);
					_camera->setCamY(100);
					_stageType = THIRDSTAGE;
				}
				else if (R == 100 && G == 0 && B == 100 && KEYMANAGER->isOnceKeyDown('J'))	//스테이지2에서 스테이지1 넘어갈 때
				{
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
					//특정 키 입력시 다음 스테이지로 이동
					_camera->setStage(0);
					_player->setShadowX(669);
					_player->setShadowY(423);
					_camera->setCamX(1239);
					_camera->setCamY(110);
					_stageType = FIRSTSTAGE;
				}
				else if (R == 100 && G == 100 && B == 100 && KEYMANAGER->isOnceKeyDown('J'))	//스테이지2에서 보스 스테이지 넘어갈 때
				{
					//_player->setSpeed(6);
					// 플레이어 주변에 문 애니메이션 출력
					//특정 키 입력시 다음 스테이지로 이동
					_camera->setStage(3);
					_player->setShadowX(400);
					_player->setShadowY(540);
					_camera->setCamX(0);
					_camera->setCamY(210);
					_stageType = BOSSSTAGE;
					_gM->setScriptStart(true);
				}
			

		}

		//바닥값을 받는
		for (int i = _probeMid - 1; i < _probeMid + 1; i++)	// 위아래
		{
			COLORREF color = GetPixel(_stage->getMemDC(), _player->getShadowX() + _camera->getCamX(), i + _camera->getCamY());

			int R = GetRValue(color);
			int G = GetGValue(color);
			int B = GetBValue(color);


			if (R == 255 && G == 255 && B == 0)
			{
				_player->setShadowY(i);
			}
	/*		else if (R == 255 && G == 0 && B == 255)
			{
				_player->setShadowY(+10);
			}*/
		}
}
