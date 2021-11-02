#pragma once
#include "gameNode.h"
class sfxStorage : public gameNode
{

private:

public:
	sfxStorage();
	~sfxStorage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

