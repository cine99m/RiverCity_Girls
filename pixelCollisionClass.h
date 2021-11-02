#pragma once
#include "gameNode.h"
#include "firstStage.h"
#include "secondStage.h"
#include "thirdStage.h"
#include "bossStage1.h"
#include "bossStage2.h"
#include "camera.h"


class gameManager;
class player;

enum PlayerDir
{
	PLAYERLEFT,
	PLAYERRIGHT
};

enum STAGETYPE
{
	FIRSTSTAGE,
	SECONDSTAGE,
	THIRDSTAGE,
	BOSSSTAGE
};

class pixelCollisionClass : public gameNode
{
private:
	image* _stage;				//스테이지 타입에 따른 스테이지

	STAGETYPE _stageType;		//스테이지 타입

	player* _player;
	gameManager* _gM;

	firstStage*		_first; 
	secondStage*	_second;
	thirdStage*		_third;
	bossStage1*		_boss1;
	bossStage2*		_boss2;

	camera* _camera;

	RECT _probeLBox, _probeRBox, _probeTBox, _probeBBox;

	RECT _rc;
	float _x, _y;

	//픽셀 탐색기
	float _probeLX, _probeTY, _probeRX, _probeBY,_probeMid;

	//player 방향
	int _dir;

	bool _isCheck;


	bool _event;



public:
	pixelCollisionClass();
	~pixelCollisionClass();

	virtual HRESULT init();
	virtual HRESULT init(float x, float y, int type);
	virtual void release();
	virtual void update();
	virtual void render();

	void Colloision();

	void setPixelPlayer(player* player) { _player = player; }

	inline RECT getRect() { return _rc; }
	int getPixelType() { return (int)_stageType; }

	void setfIRSTSTAGEMemoryAddressLink(firstStage* first) { _first = first; }
	void setSECONDSTAGEMemoryAddressLink(secondStage* second) { _second = second; }
	void setTHIRDSTAGEMemoryAddressLink(thirdStage* third) { _third = third; }
	void setBOSSSTAGE1MemoryAddressLink(bossStage1* boss1) { _boss1 = boss1; }
	void setBOSSSTAGE2MemoryAddressLink(bossStage2* boss2) { _boss2 = boss2; }
	void setCAMERAMemoryAddressLink(camera* camera) { _camera = camera; }

	//void setIsCheck(bool isCheck) { _isCheck = isCheck; }

	void setGameManager(gameManager* gm) { _gM = gm; }
};