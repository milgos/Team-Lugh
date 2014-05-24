#include "FadeLeft.h"


CFadeLeft::CFadeLeft(void)
{
	FadeTex = NULL;
	FadeTex2 = NULL;

	PosX1 = 0;
	PosX2 = 0;
}


CFadeLeft::~CFadeLeft(void)
{
}

void CFadeLeft::Initialize()
{
	FadeTex = new CUIObject;
	FadeTex2 = new CUIObject;
	FadeTex->Init( L"Image\\ETC\\FadeLeft.png");
	FadeTex2->Init( L"Image\\ETC\\FadeLeft2.png");
	FadeTex->Warp(0,0,0.1f);
	FadeTex2->Warp(1526 , 0,0.1f);
}

void CFadeLeft::UnInitialize()
{
	if ( FadeTex != NULL )
	{
		FadeTex->RemoveImage();
		delete FadeTex;
		FadeTex = NULL;
	}
	if ( FadeTex2 != NULL )
	{
		FadeTex2->RemoveImage();
		delete FadeTex2;
		FadeTex2 = NULL;
	}
}

void CFadeLeft::InitializeFill()
{
	FadeTex->Warp( -1920, 0 );
	FadeTex2->Warp( -640, 0 );
}

void CFadeLeft::InitializeUnFill()
{
	FadeTex->Warp( 0, 0 );
	FadeTex2->Warp( 1820, 0 );
}

void CFadeLeft::TransitionIn( short Speed, int& TransitionOption )
{
	PosX1 += ((float)Speed/10000)*( 1920 - PosX1 );

	FadeTex->Move( PosX1, 0 );
	FadeTex2->Move( PosX1*0.7f, 0 );
	if ( FadeTex->GetPosition()->x >= 0  && FadeTex2->GetPosition()->x >= 0 )
	{
		PosX1 = 0;
		TransitionOption = 0;
		FadeTex->Warp( 0, 0 );
		FadeTex2->Warp( 1820, 0 );
	}
}

void CFadeLeft::TransitionOut( short Speed, int& TransitionOption )
{
	PosX2 += ((float)Speed/10000)*( 1920 - PosX2 );

	FadeTex->Move( -PosX2, 0 );
	FadeTex2->Move( -PosX2*0.7f, 0 );
	if ( FadeTex->GetPosition()->x <= 5  && FadeTex2->GetPosition()->x <= 5 )
	{
		PosX2 = 0;
		TransitionOption = 0;
		FadeTex->Warp( -1920, 0 );
		FadeTex2->Warp( -640, 0 );
	}
}

void CFadeLeft::Render()
{
	FadeTex->Process();
	FadeTex2->Process();

	FadeTex->Render();
	FadeTex2->Render();
}
