#include "SceneHeader.h"
#include "DirectSound.h"
#include "SceneManager.h"
#include "TransitionManager.h"
//#include "User.h"
#include <Windows.h>

#define NULL 0


CSceneManager::CSceneManager(void)
{
	m_CurrentScene = NULL;
	/*
	DirectSound()->Load_WaveFile( L"Sound\\Menu\\BGMusic\\Swordland.wav" );
	DirectSound()->Load_WaveFile( L"Sound\\Menu\\Effect\\Move1.wav" );
	DirectSound()->Load_WaveFile( L"Sound\\Menu\\Effect\\Click1.wav" );
	DirectSound()->Load_WaveFile( L"Sound\\Menu\\Effect\\Move2.wav" );
	DirectSound()->Load_WaveFile( L"Sound\\Menu\\Effect\\Click2.wav" );
	DirectSound()->Load_WaveFile( L"Sound\\Menu\\Effect\\Move3.wav" );
	DirectSound()->Load_WaveFile( L"Sound\\Menu\\Effect\\Click3.wav" );
	DirectSound()->Load_WaveFile( L"Sound\\Menu\\BGMusic\\CreditBGM.wav" );
	DirectSound()->Load_WaveFile( L"Sound\\Menu\\Effect\\Change.wav" );*/
}

CSceneManager::~CSceneManager(void)
{
	this->DeleteScene();
}

void CSceneManager::TextureInitialize()
{
	m_CurrentScene->TextureInitialize();
}

void CSceneManager::TextureUnInitialize()
{
	m_CurrentScene->TextureUnInitialize();
}

void CSceneManager::ChangeScene(CScene* scene )
{
	this->DeleteScene();

	m_CurrentScene = scene;

	if( (m_CurrentScene->TextureInitialize()) == false )
	{
		MessageBox( NULL, L"SceneTextureLoadedError!", L"Error!", MB_OK );
	}

	if( (m_CurrentScene->Initialize()) == false )
	{
		MessageBox( NULL, L"SceneLoadedError!", L"Error!", MB_OK );
	}
}

void CSceneManager::PrepareInput()
{
	m_CurrentScene->PrepareInput();
}

void CSceneManager::Process()
{
	m_CurrentScene->Process();
/*
	switch (User()->GetGameState())
	{
	case GameState::GameOver:
		{
			User()->ChangeGameState(GameState::Normal);
//			this->ChangeScene( new CGameOver() );
			TransitionManager()->SetTransition( TransitionOption::In );
			break;
		}

	case GameState::MainMenu:
		{
			User()->ChangeGameState(GameState::Normal);
			this->ChangeScene( new CStartScene() );
			TransitionManager()->SetTransition( TransitionOption::In );
			break;
		}

	case GameState::Retry:
		{
			User()->ChangeGameState(GameState::Normal);
			this->m_CurrentScene->UnInitialize();
			this->m_CurrentScene->Initialize();
			User()->Initialize();
			break;
		}
	}*/
}

void CSceneManager::Render()
{
	m_CurrentScene->Render();
}

void CSceneManager::DeleteScene()
{
	if( m_CurrentScene != NULL )
	{
		m_CurrentScene->TextureUnInitialize();
		m_CurrentScene->UnInitialize();
		delete m_CurrentScene;
		m_CurrentScene = NULL;
	}
}