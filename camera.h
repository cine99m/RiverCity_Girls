#pragma once
#include "gameNode.h"


enum class stageImg
{
	FIRST_STAGE,
	SECOND_STAGE,
	THIRD_STAGE,
	BOSS_STAGE1,
	BOSS_STAGE2,
};

class pixelCollisionClass;

class camera : public gameNode
{

private:
	stageImg _stageImg;

	RECT _cameraRc;

	int  _stage;


	image* _backGroundImg;
	image* _pixelImg;

	float _camX, _camY;
	float _camXrc, _camYrc;

	pixelCollisionClass* _pixel;

	 
public:

	 HRESULT init();
	 void release();
	 void update();
	 void render();



	 float getCamX() { return _camX; }
	 float getCamY() { return _camY; }

	 void setCamX(float camX) { _camX = camX; }
	 void setCamY(float camY) { _camY = camY; }


	 void setStage(int nowStageNum) { _stageImg = (stageImg)nowStageNum; }
	 stageImg getstage() { return _stageImg; }

	 image* getBgImage() { return _backGroundImg; }

	 image* getPixImage() { return _pixelImg; }

	 RECT getCameraRc() { return _cameraRc; }


	 void cameraLock(float x, float y);

	 
	 
};

