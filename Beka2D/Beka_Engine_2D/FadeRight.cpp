#include "FadeRight.h"


CFadeRight::CFadeRight(void)
{
	m_FadeTex = NULL;
	m_FadeTex2 = NULL;

	PosX1 = 0;
	PosX2 = 0;
}


CFadeRight::~CFadeRight(void)
{

}

void CFadeRight::Initialize()
{
	m_FadeTex = new CUIObject;
	m_FadeTex2 = new CUIObject;
	m_FadeTex->Init( L"Image\\ETC\\FadeRight.png");
	m_FadeTex2->Init( L"Image\\ETC\\FadeRight2.png");

	m_FadeTex->Warp(-640 , 0 ,0.1f);
	m_FadeTex2->Warp(-1920, 0 , 0.1f);
}

void CFadeRight::UnInitialize()
{
	if ( m_FadeTex != NULL )
	{
		m_FadeTex->RemoveImage();
		delete m_FadeTex;
		m_FadeTex = NULL;
	}
	if ( m_FadeTex2 != NULL )
	{
		m_FadeTex2->RemoveImage();
		delete m_FadeTex2;
		m_FadeTex2 = NULL;
	}
}

void CFadeRight::InitializeFill()
{
	m_FadeTex->Warp( -640, 0 );
	m_FadeTex2->Warp( -640, 0 );
}

void CFadeRight::InitializeUnFill()
{
	m_FadeTex->Warp( 1280, 0 );
	m_FadeTex2->Warp( 640, 0 );
}

void CFadeRight::TransitionIn( short Speed, int& TransitionOption )
{
	PosX1 += ((float)Speed/10000)*( 1920 - PosX1 );

	m_FadeTex->Move( -PosX1, 0 );
	m_FadeTex2->Move( -PosX1*0.7f, 0 );
	if ( m_FadeTex->GetPosition()->x <= -640  && m_FadeTex2->GetPosition()->x <= -640 )
	{
		PosX1 = 0;
		TransitionOption = 0;
		m_FadeTex->Warp( -640, 0 );
		m_FadeTex2->Warp( -640, 0 );
	}
}

void CFadeRight::TransitionOut( short Speed, int& TransitionOption )
{
	PosX2 += ((float)Speed/10000)*( 1920 - PosX2 );

	m_FadeTex->Move( PosX2, 0 );
	m_FadeTex2->Move( PosX2*0.7f, 0 );
	if ( m_FadeTex->GetPosition()->x >= 1280  && m_FadeTex2->GetPosition()->x >= 640 )
	{
		PosX2 = 0;
		TransitionOption = 0;
		m_FadeTex->Warp( 1280, 0 );
		m_FadeTex2->Warp( 640, 0 );
	}
}

void CFadeRight::Render()
{
	m_FadeTex->Process();
	m_FadeTex2->Process();

	m_FadeTex->Render();
	m_FadeTex2->Render();
}
