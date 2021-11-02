#include "pch.h"
#include "introVideo.h"




introVideo::introVideo()
{
}

introVideo::~introVideo()
{
}

HRESULT introVideo::init()
{
    SCENEMANAGER->init();
    //_count = 0;
    //_iskeydown = false;

    _vid = MCIWndCreate(_hWnd, NULL, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, "Resource/VID/intro.wmv");

    MoveWindow(_vid, 0, 0, WINSIZEX, WINSIZEY, NULL);

    MCIWndPlay(_vid);



    _currentGauge = 0;
    _maxGauge = 206;

    _skip = new progressBar;
    _skip->init(WINSIZEX - 250, 20, 206, 78);
    _skip->setGauge(_currentGauge, _maxGauge);



    return S_OK;
}

void introVideo::release()
{
}

void introVideo::update()
{
    if (MCIWndGetLength(_vid) <= MCIWndGetPosition(_vid))
    {
        MCIWndDestroy(_vid);
        SCENEMANAGER->changeScene("imageStorage");

    }
    
    //if (KEYMANAGER->isOnceKeyDown(VK_F5))
    //{
    //    MCIWndDestroy(_vid);
    //    SCENEMANAGER->changeScene("stage1");
    //}

    _skip->setGauge(_currentGauge, _maxGauge);
    _skip->update();

    if (_currentGauge >= _maxGauge)
    {
        //_gameManager->setScriptEnd(true);
        //_gameManager->setScriptStart(false);
        _currentGauge = 0;
        _streamSwitch = false;
        MCIWndDestroy(_vid);
        SCENEMANAGER->changeScene("imageStorage");
    }

    if (KEYMANAGER->isStayKeyDown(VK_RETURN))
    {
        _currentGauge += 2;
    }
    if (KEYMANAGER->isOnceKeyUp(VK_RETURN))
    {
        _currentGauge -= 2;
        if (_currentGauge < 20)
        {
            _currentGauge = 0;
        }
    }
    //if (KEYMANAGER->isOnceKeyUp(VK_RETURN))
    //{
    //    _iskeydown = false;
    //    _count = 0;
    //}
    //
    //if (_count >= 500)
    //{
    //    MCIWndDestroy(_vid);
    //    SCENEMANAGER->changeScene("stage1");
    //}
    //SCENEMANAGER->update();
}

void introVideo::render()
{
    _skip->render();
    //SCENEMANAGER->render();
}
