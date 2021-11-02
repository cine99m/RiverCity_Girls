#pragma once
#include "gameNode.h"
#include "stageManager.h"

class testScen : public gameNode
{
private:
	stageManager* _stage;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

