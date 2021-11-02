#pragma once
#pragma comment (lib,"Vfw32.lib")

#include "gameNode.h"
//#include <Windows.h>
#include <Vfw.h>
#include "progressBar.h"



class introVideo : public gameNode
{
private:
	HWND _vid;
	int _count;
	bool _iskeydown;



	progressBar* _skip;
	float _currentGauge, _maxGauge;


public:
	introVideo();
	~introVideo();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


};

