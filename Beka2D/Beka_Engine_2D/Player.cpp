#include "Player.h"


CPlayer::CPlayer(void)
{
	
}


CPlayer::~CPlayer(void)
{

}

void CPlayer::Init( int Charactertype = 0 )
{
	m_Run =  new CUIObject;
	m_Jump = new CUIObject;
	m_DJump = new CUIObject;
	m_Beshot = new CUIObject;
	m_Fall = new CUIObject;
	m_HFall = new CUIObject;
	m_Current = &m_Run;
	switch( Charactertype )
	{
	case 0:
		m_Run->Init();
		m_Run->Init();
		m_Jump->Init();
		m_DJump->Init();
		m_Beshot->Init();
		m_Fall->Init();
		m_HFall->Init();
		break;
	}
}

void CPlayer::Render()
{
	(*m_Current)->Render();
}

void CPlayer::Process()
{
	switch( m_State )
	{
	case RUN:
		break;
	case JUMP:
		break;
	case DOUBLEJUMP:
		break;
	case BESHOT:
		break;
	case FALL:
		break;
	case HIGHFALL:
		break;	
	}

	(*m_Current)->Process();
}



void CPlayer::SetState(int val)
{
	m_State = val;
	switch( m_State )
	{
	case RUN:
		m_Current = &m_Run;
		break;
	case JUMP:
		m_Current = &m_Jump;
		break;
	case DOUBLEJUMP:
		m_Current = &m_DJump;
		break;
	case BESHOT:
		m_Current = &m_Beshot;
		break;
	case FALL:
		m_Current = &m_Fall;
		break;
	case HIGHFALL:
		m_Current = &m_HFall;
		break;	
	}
}