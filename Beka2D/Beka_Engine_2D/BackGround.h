#pragma once

#include "UIObject.h"
#include "Core.h"
#include "CameraManager.h"
class CBackGround
{
public:
	CBackGround(void);
	~CBackGround(void);

	void Init( LPWSTR path, float x , float y, float deep );
	void AddObject(LPWSTR path, float delay , int maxFrame , int x, int y);
	void SetAnimeOption( int num, int x, int y,float delay , int maxFrame );
	void ReleaseObject();
	
	void UnInit();

	void Process();
	void Render(); 
	void SetDeeps(float val){ m_BGDeeps = val; }

private:
	std::vector<CUIObject*> m_AnimeBGStuff; // sub animation Background
	CUIObject* m_BG; // main Background
	
	float m_BGDeeps; // All Backgrounds deeps 
};

