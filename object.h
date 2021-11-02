#pragma once
#include "gameNode.h"
#include "player.h"
//#include "pixelCollisionClass.h"

class pixelCollisionClass;//-삭제 가능

enum OBJECTTYPE
{
	DESK,
	LPILLAR,
	RPILLAR,
	PARTICLE1,
	PARTICLE2,
	PARTICLE3
};

class object : public gameNode
{
private:
	//bool _isBreak;					//기둥 소멸
	//bool _isCheck;					//기둥 & 보스 충돌
	//bool _isShot;						//기둧 파편 발사
	
	player* _player;

	pixelCollisionClass* _pixel;// - 삭제 가능

	image* _objectImg;

	RECT _objectRc;

	OBJECTTYPE _objectType;

	float _objectMX, _objectMY;		//오브젝트 가이드 중점값 - 반환형
	float _objectOX, _objectOY;		//오브젝트 중점값

	float _particleAngle;			//기둥 파편의 각도값
	float _particleSpeed;			//기둥 파편의 속도값
	float _particleGravity;			//기둥 파편의 중력값

public:
	object();
	~object();

	virtual HRESULT init();
	virtual HRESULT init(float x, float y, int type);
	virtual void release();
	virtual void update();
	virtual void render();

	////오브젝트 가이트 중점 x
	float getObjectMX() { return _objectMX; }
	void setObjectMX(float objectMX) { _objectMX = objectMX; }
	
	//오브젝트 가이트 중점 y
	float getObjectMY() { return _objectMY; }
	void setObjectMY(float objectMY) { _objectMY = objectMY; }
	
	//오브젝트 중점 x
	float getObjectOX() { return _objectOX; }
	void setObjectOX(float objectOX) { _objectOX = objectOX; }
	
	//오브젝트 중점 y
	float getObjectOY() { return _objectOY; }
	void setObjectOY(float objectOY) { _objectOY = objectOY; }
	
	//파편의 각도
	float getParticleAngle() { return _particleAngle; }
	void setParticleAngle(float particleAngle) { _particleAngle = particleAngle; }
	//
	//파편의 속도
	float getParticleSpeed() { return _particleSpeed; }
	void setParticleSpeed(float particleSpeed) { _particleSpeed = particleSpeed; }
	
	//파편의 중력
	float getParticleGravity() { return _particleGravity; }
	void setParticleGravity(float particleGravity) { _particleGravity = particleGravity; }

	//오브젝트 렉트 & 타입
	inline RECT getObjectRect() { return _objectRc; }
	int getObjectType() { return (int)_objectType; }
	
	//오브젝트 이미지
	image* getObjectImg() { return	_objectImg; }
	void setObjectImg(image* objectImg) { _objectImg = objectImg; }

	void setPlayerMemoryAddrsLink(player* player) { _player = player; }

	virtual float getPosY() { return _objectMY; }
};

