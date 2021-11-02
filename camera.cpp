#include "pch.h"
#include "camera.h"
#include "pixelCollisionClass.h"

HRESULT camera::init()
{

    //실질적 시작 위치


    //카메라 렉트 중심
    _camXrc = WINSIZEX / 2;
    _camYrc = WINSIZEY / 2;

    _cameraRc = RectMakeCenter(_camXrc, _camYrc, 150, 150);

    switch (_stageImg)
    {
    case stageImg::FIRST_STAGE:
        _camX = 0;
        _camY = 0;
        _backGroundImg = IMAGEMANAGER->findImage("STAGE_stage1");
        _pixelImg = IMAGEMANAGER->findImage("STAGE_stagePixel1");
        break;
    case stageImg::SECOND_STAGE:
        _camX = 0;
        _camY = 0;
        _backGroundImg = IMAGEMANAGER->findImage("STAGE_stage4");
        _pixelImg = IMAGEMANAGER->findImage("STAGE_stagePixel4");
        break;
    case stageImg::THIRD_STAGE:
        _camX = 0;
        _camY = 0;
        _backGroundImg = IMAGEMANAGER->findImage("STAGE_normal");
        _pixelImg = IMAGEMANAGER->findImage("STAGE_normalPixel");
        break;
    case stageImg::BOSS_STAGE1:
        _camX = 0;
        _camY = 0;
        _backGroundImg = IMAGEMANAGER->findImage("STAGE_bossStage1");
        _pixelImg = IMAGEMANAGER->findImage("STAGE_bossPixel");
        break;
    case stageImg::BOSS_STAGE2:
        _camX = 0;
        _camY = 0;
        _backGroundImg = IMAGEMANAGER->findImage("STAGE_bossStage2");
        _pixelImg = IMAGEMANAGER->findImage("STAGE_bossPixel");
        break;
    default:
        break;
    }

    return S_OK;
}

void camera::release()
{
}

void camera::update()
{
    switch (_stageImg)
    {
    case stageImg::FIRST_STAGE:
        //_camX = 0;
        //_camY = 0;
        _backGroundImg = IMAGEMANAGER->findImage("STAGE_stage1");
        _pixelImg = IMAGEMANAGER->findImage("STAGE_stagePixel1");
        break;
    case stageImg::SECOND_STAGE:
        //_camX = 0;
        //_camY = 0;
        _backGroundImg = IMAGEMANAGER->findImage("STAGE_stagePixel4");
        _pixelImg = IMAGEMANAGER->findImage("STAGE_stagePixel2");
        break;
    case stageImg::THIRD_STAGE:
        //_camX = 0;
       // _camY = 0;
        _backGroundImg = IMAGEMANAGER->findImage("STAGE_normal");
        _pixelImg = IMAGEMANAGER->findImage("STAGE_normalPixel");
        break;
    case stageImg::BOSS_STAGE1:
        //_camX = 0;
        //_camY = 0;
        _backGroundImg = IMAGEMANAGER->findImage("STAGE_bossStage1");
        _pixelImg = IMAGEMANAGER->findImage("STAGE_bossPixel");
        break;
    case stageImg::BOSS_STAGE2:
        //_camX = 0;
        //_camY = 0;
        _backGroundImg = IMAGEMANAGER->findImage("STAGE_bossStage2");
        _pixelImg = IMAGEMANAGER->findImage("STAGE_bossPixel");
        break;
    default:
        break;
    }

}

void camera::render()
{
    _backGroundImg->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        _pixelImg->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);
        Rectangle(getMemDC(), _cameraRc);
    }
    //Rectangle(getMemDC(), _cameraRc);



    char str[128];

    sprintf_s(str, "camX : %.2f camY : %.2f", _camX, _camY);
    TextOut(getMemDC(), 10, 680, str, strlen(str));
}

void camera::cameraLock(float x, float y)
{
    _camXrc = WINSIZEX / 2;
    _camYrc = WINSIZEY / 2;

    _cameraRc = RectMakeCenter(_camXrc, _camYrc, 150, 150);
}