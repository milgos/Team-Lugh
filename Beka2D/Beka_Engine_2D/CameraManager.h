#pragma once

#include "Singleton.h"

class CCameraManager : public CSingleton<CCameraManager>
{
public:
	CCameraManager(void);
	~CCameraManager(void);

	inline void SetCamera(float _x=0 , float _y=0 ){ x=_x, y=_y; }
	inline void Move( float _x = 0 , float _y = 0 ) {  x+=_x, y+=_y; }
	inline float GetX(){return x;}
	inline float GetY(){return y;}

private:
	float x;
	float y;
};

#define Camera() CSingleton<CCameraManager>::InstancePtr()

