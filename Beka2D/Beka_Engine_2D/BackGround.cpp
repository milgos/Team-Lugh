#include "BackGround.h"


CBackGround::CBackGround(void)
{
}


CBackGround::~CBackGround(void)
{
}
void CBackGround::Init( LPWSTR path, float x , float y, float deep )
{
	m_BG = new CUIObject;
	SetDeeps( deep);
	m_BG->Init( path );
	m_BG->Warp( x , y , deep );
	m_BG->ConstWarp(x,y,deep);
}

void CBackGround::UnInit()
{
	ReleaseObject();
	m_BG->UnInit();
	delete m_BG;
	m_BG = NULL;
}

void CBackGround::SetAnimeOption( int num=0, int x=0 , int y=0, float delay=-1, int maxFrame=-1 )
{
	if ( m_AnimeBGStuff.empty() == true )
	{
		MessageBox( Core()->GetMainHWND(), L"GetTexture Failed", L"Error", MB_OK );
		return;
	}
	if( delay != -1 )
		m_AnimeBGStuff[num]->SetFrameDelay( delay );
	if( maxFrame != -1 )
		m_AnimeBGStuff[num]->SetMaxFrame( maxFrame );

	m_AnimeBGStuff[num]->Warp( x, y );
}

void CBackGround::AddObject(LPWSTR path, float delay, int maxFrame, int x, int y )
{
	CUIObject* Temp = new CUIObject;

	Temp->Init( path );
	Temp->SetFrameDelay( delay );
	Temp->SetMaxFrame( maxFrame );
	Temp->SetAutoLoop( false );
	Temp->Warp(x,y,m_BGDeeps);

	m_AnimeBGStuff.push_back( Temp );
}

void CBackGround::ReleaseObject()
{
	std::vector<CUIObject*>::iterator iter;

	for(iter = m_AnimeBGStuff.begin(); iter != m_AnimeBGStuff.end(); ++iter)
	{
		(*iter)->UnInit();
		delete (*iter);
		(*iter) = NULL;
	}

	m_AnimeBGStuff.clear();
}

void CBackGround::Process()
{
	static float x = m_BG->GetPosition()->x - Camera()->GetX();
	static float y = m_BG->GetPosition()->y - Camera()->GetY();
	std::vector<CUIObject*>::iterator iter;

	for(iter = m_AnimeBGStuff.begin(); iter != m_AnimeBGStuff.end(); ++iter)
	{
		x = (*iter)->GetConstPosition()->x - Camera()->GetX();
		y = (*iter)->GetConstPosition()->y - Camera()->GetY();

		(*iter)->Warp( x , y ) ;
		(*iter)->Process();
	}
	
	x = m_BG->GetConstPosition()->x - ( Camera()->GetX() * (1 - m_BGDeeps) );
	y = m_BG->GetConstPosition()->y - ( Camera()->GetY() * (1 - m_BGDeeps) ) ;

	m_BG->Warp( x , y) ;
	m_BG->Process();
}

void CBackGround::Render()
{
	std::vector<CUIObject*>::iterator iter;

	for(iter = m_AnimeBGStuff.begin(); iter != m_AnimeBGStuff.end(); ++iter)
	{
		(*iter)->Render();
	}

	m_BG->Render();
}
