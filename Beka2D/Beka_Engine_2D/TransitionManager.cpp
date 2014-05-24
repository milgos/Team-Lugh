#include "TransitionManager.h"
#include "Direct3D.h"
#include "Core.h"

CTransitionManager::CTransitionManager(void)
{
	m_CurrentTransition = NULL;
	m_CurrentTransitionType = 0;
	m_TransitionOptionNum = 0;

}


CTransitionManager::~CTransitionManager(void)
{
}

void CTransitionManager::SetTransition( int TransitionOptionNum, short Speed )
{
	m_TransitionOptionNum = TransitionOptionNum;

	if ( m_TransitionOptionNum == 0 )
		return;
	else if ( m_TransitionOptionNum == 1 )
		this->TransitionIn( Speed );
	else if ( m_TransitionOptionNum == 2 )
		this->TransitionOut( Speed );

}

void CTransitionManager::TransitionChange( long TransitionType )
{
	switch ( TransitionType )
	{
	case 0:
		{
			this->UnInitialize();
			m_CurrentTransition = NULL;
			m_CurrentTransitionType = TransitionType::Empty;
			break;
		}
	case 1:
		{
			this->UnInitialize();
			CFade* _Fade = new CFade;
			_Fade->Initialize();
			m_CurrentTransition = _Fade;
			m_CurrentTransitionType = TransitionType::Fade;
			break;
		}
	case 2:
		{
			this->UnInitialize();
			CFadeLeft* _FadeLeft = new CFadeLeft;
			_FadeLeft->Initialize();
			m_CurrentTransition = _FadeLeft;
			m_CurrentTransitionType = TransitionType::FadeLeft;
			break;
		}
	case 3:
		{
			this->UnInitialize();
			CFadeRight* _FadeRight = new CFadeRight;
			_FadeRight->Initialize();
			m_CurrentTransition = _FadeRight;
			m_CurrentTransitionType = TransitionType::FadeRight;
			break;
		}
	}
}

void CTransitionManager::ReInitialize()
{
	this->TransitionChange( m_CurrentTransitionType );
	this->InitializeUnFill();
}

void CTransitionManager::UnInitialize()
{
	if ( m_CurrentTransition != NULL )
	{
		m_CurrentTransition->UnInitialize();
		delete m_CurrentTransition;
		m_CurrentTransition = NULL;
	}
}

void CTransitionManager::InitializeFill()
{
	m_CurrentTransition->InitializeFill();
}

void CTransitionManager::InitializeUnFill()
{
	m_CurrentTransition->InitializeUnFill();
}

void CTransitionManager::TransitionIn( short Speed )
{
	if ( m_CurrentTransitionType == 0 )
		return;

	m_CurrentTransition->TransitionIn( Speed, m_TransitionOptionNum );
}

void CTransitionManager::TransitionOut( short Speed )
{
	if ( m_CurrentTransitionType == 0 )
		return;

	m_CurrentTransition->TransitionOut( Speed, m_TransitionOptionNum );
}

void CTransitionManager::Render()
{
	if ( m_CurrentTransitionType == 0 )
		return;

	m_CurrentTransition->Render();
}