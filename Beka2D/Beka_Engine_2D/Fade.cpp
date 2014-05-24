#include "Direct3D.h"
#include "Fade.h"

#include "Core.h"

CFade::CFade(void)
{
	FadeTex = NULL;
	t1 = 255;
	t2 = 0;
	dwTimeStart1 = 0;
	dwTimeStart2 = 0;
}

CFade::~CFade(void)
{

}

void CFade::Initialize()
{
	FadeTex = new CUIObject;
	FadeTex->Init( L"Image\\ETC\\Fade.png");

	FadeTex->Process();
}

void CFade::UnInitialize()
{
	if ( FadeTex != NULL )
	{
		FadeTex->RemoveImage();
		delete FadeTex;
		FadeTex = NULL;
	}
}

void CFade::InitializeFill()
{
	FadeTex->ChangeAlpha( 255 );
}

void CFade::InitializeUnFill()
{
	FadeTex->ChangeAlpha( 0 );
}

void CFade::TransitionIn( short Speed, int& TransitionOption )
{
	if( dwTimeStart1 - GetTickCount() > 100)
	{
		t1 -= Speed;

		dwTimeStart1 = GetTickCount();
	}
	FadeTex->ChangeAlpha(t1);

	if ( t1 <= Speed )
	{
		t1 = 255;
		dwTimeStart1 = 0;
		TransitionOption = 0;
		FadeTex->ChangeAlpha( 0 );
	}
}

void CFade::TransitionOut( short Speed, int& TransitionOption )
{
	if(dwTimeStart2 - GetTickCount() > 80)
	{
		t2 += Speed;

		dwTimeStart2 = GetTickCount();
	}

	FadeTex->ChangeAlpha(t2);

	if ( t2 >= 255 - Speed )
	{
		t2 = 0;
		dwTimeStart2 = 0;
		TransitionOption = 0;
		FadeTex->ChangeAlpha( 255 );
	}
}

void CFade::Render()
{
	FadeTex->Render();
}