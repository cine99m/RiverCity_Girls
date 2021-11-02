#pragma once
#include "gameNode.h"

#define LOADINGMAX 1

class imageStorage : public gameNode
{
private:
	
	image* _background;
	image* _loading;


	int _count,frameX;
	
public:
	imageStorage();
	~imageStorage();

	int _currentCount;

	 HRESULT init();
	 void release();
	 void update();
	 void render();



	
};
static DWORD CALLBACK threadFunction(LPVOID lpParameter);