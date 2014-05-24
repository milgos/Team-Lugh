#include "DirectInput.h"

#include "Core.h"
//#include "SceneManager.h"


CDirectInput::CDirectInput(void)
{

	m_Mouse = NULL;
	m_Mouse_sens = 2.f;

	m_pDirectInput8 = NULL;
	m_pKeyboard = NULL;
	m_pMouse = NULL;
	m_CurrMouseState = DIMOUSESTATE();
	m_PrevMouseState = DIMOUSESTATE();

	ZeroMemory(&m_byCurrKeys, sizeof( m_byCurrKeys ) );
	ZeroMemory(&m_byPrevKeys, sizeof( m_byPrevKeys ) );
}

bool CDirectInput::Initialize()
{
	m_Mouse->Warp( 100.f , 100.f , 0) ;

	return true;
}

void CDirectInput::UnInitialize()
{
	m_Mouse->RemoveImage();
}

bool CDirectInput::TextureInitialize()
{

	m_Mouse = new CUIObject;
	m_Mouse->Init();
	m_Mouse->SetMaxFrame( 2 );
	m_Mouse->SetFrameDelay(100);
	m_Mouse->SetAutoLoop(true);
	m_Mouse->Process();
//	if ( ( m_CreateTexture->AddTexture( L"Image\\Mouse\\mouse_cursor.png" ) ) == false ) return false;
//	if(m_Mouse != NULL ) // Mouse
//	{
//		m_Mouse->ReTextureInitialize(( m_CreateTexture->GetTexture(0) ));
//	}

	return true;
}

void CDirectInput::TextureUnInitialize()
{
	m_Mouse->UnInit();
//	m_CreateTexture->ReleaseTexture();
//	delete m_CreateTexture;
//	m_CreateTexture = NULL;
}


CDirectInput::~CDirectInput(void)
{
}

HRESULT CDirectInput::InitInputDevice( HWND hWnd )
{
	HRESULT hr;
	this->ReleaseInputDevice();

	if( FAILED( hr=DirectInput8Create( GetModuleHandle(NULL) ,
		DIRECTINPUT_VERSION, IID_IDirectInput8, 
		(void**)&m_pDirectInput8, NULL )))
	{
		return hr;
	}

	if( FAILED( hr = m_pDirectInput8->CreateDevice( GUID_SysKeyboard, &m_pKeyboard, NULL ) ))
	{
		return hr;
	}

	if( FAILED( hr = m_pDirectInput8->CreateDevice( GUID_SysMouse, &m_pMouse, NULL )))
	{
		return hr;
	}

	if( FAILED( hr = m_pKeyboard->SetDataFormat( &c_dfDIKeyboard )))
	{
		return hr;
	}

	if( FAILED( hr = m_pMouse->SetDataFormat( &c_dfDIMouse )))
	{
		return hr;
	}

	if( FAILED( hr = m_pMouse->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE )))
	{
		return hr;
	}

	if( FAILED( hr = m_pKeyboard->SetCooperativeLevel( hWnd,DISCL_NONEXCLUSIVE | DISCL_FOREGROUND )))
	{
		return hr;
	}

	return hr;
}

void CDirectInput::KeyboardUpdate()
{
	//const int InputDelay = 200; // Temp

	HRESULT hr;
	if( m_pKeyboard == NULL ) return;

	hr = m_pKeyboard->GetDeviceState( sizeof(m_byCurrKeys), (LPVOID)m_byCurrKeys );

	if( FAILED(hr) )
	{
		hr = m_pKeyboard->Acquire();
		while( hr == DIERR_INPUTLOST )
		{
			hr = m_pKeyboard->Acquire();
		}
		return;
	}
}

void CDirectInput::MouseUpdate()
{
	HRESULT hr;

	if( m_pMouse == NULL ) return;

	hr = m_pMouse->GetDeviceState(sizeof(m_CurrMouseState), (LPVOID)(&m_CurrMouseState));

	if( FAILED( hr ) )
	{
		hr = m_pMouse->Acquire();

		while( hr == DIERR_INPUTLOST )
		{
			hr = m_pMouse->Acquire();
		}

		hr = m_pMouse->GetDeviceState(sizeof(m_pMouse), (LPVOID)(&m_CurrMouseState));

		if( FAILED( hr ) )
		{
			return;
		}
	}
}

void CDirectInput::ReleaseInputDevice()
{
	if( m_pKeyboard )
		m_pKeyboard->Unacquire();

	if( m_pKeyboard != NULL )
	{
		m_pKeyboard->Release();
		m_pKeyboard = NULL;
	}

	if( m_pMouse )
		m_pMouse->Unacquire();

	if( m_pMouse != NULL )
	{
		m_pMouse->Release();
		m_pMouse = NULL;
	}

	if( m_pDirectInput8 != NULL)
	{
		m_pDirectInput8->Release();
		m_pDirectInput8 = NULL;
	}
}

bool CDirectInput::KeyDown( int KeyCode )
{
	if( !(m_byPrevKeys[KeyCode] & 0x80 ) )
	{
		if( m_byCurrKeys[KeyCode] & 0x80 )
		{
			return true;
		}
	}
	return false;
}

bool CDirectInput::KeyPress( int KeyCode )
{
	if( m_byPrevKeys[KeyCode] & 0x80 )
	{
		if( m_byCurrKeys[KeyCode] & 0x80 )
		{
			return true;
		}
	}
	return false;
}

bool CDirectInput::KeyUp( int KeyCode )
{
	if( m_byPrevKeys[KeyCode] & 0x80 )
	{
		if( !( m_byCurrKeys[KeyCode] & 0x80 ) )
		{
			return true;
		}
	}

	return false;
}

bool CDirectInput::LButtonDown()
{
	if( !(m_PrevMouseState.rgbButtons[0] & 0x80) )
	{
		if( m_CurrMouseState.rgbButtons[0] & 0x80 )
		{
			return true;
		}
	}

	return false;
}

bool CDirectInput::RButtonDown()
{
	if( !(m_PrevMouseState.rgbButtons[1] & 0x80) )
	{
		if( m_CurrMouseState.rgbButtons[1] & 0x80 )
		{
			return true;
		}
	}

	return false;
}

bool CDirectInput::LButtonPress()
{
	if( m_PrevMouseState.rgbButtons[0] & 0x80 )
	{
		if( m_CurrMouseState.rgbButtons[0] & 0x80 )
		{			
			return true;
		}
	}
	return false;
}

bool CDirectInput::RButtonPress()
{
	if( m_PrevMouseState.rgbButtons[1] & 0x80 )
	{
		if( m_CurrMouseState.rgbButtons[1] & 0x80 )
		{
			return true;
		}
	}

	return false;
}

bool CDirectInput::LButtonUp()
{
	if( m_PrevMouseState.rgbButtons[0] & 0x80 )
	{
		if( !(m_CurrMouseState.rgbButtons[0] & 0x80) )
		{
			return true;
		}
	}

	return false;
}

bool CDirectInput::RButtonUp()
{
	if( m_PrevMouseState.rgbButtons[1] & 0x80 )
	{
		if( !(m_CurrMouseState.rgbButtons[1] & 0x80) )
		{
			return true;
		}
	}

	return false;
}

bool CDirectInput::CursorPositionCheck( long left, long top, long right, long bottom )
{
	if ( m_CurrMouseState.lX > left )
	{
		if ( m_CurrMouseState.lX < right )
		{
			if ( m_CurrMouseState.lY > top )
			{
				if ( m_CurrMouseState.lY < bottom )
				{
					return true;
				}
			}
		}
	}

	return false;
}

void CDirectInput::MouseProcess()
{

	m_Mouse->Move(m_CurrMouseState.lX * m_Mouse_sens , m_CurrMouseState.lY * m_Mouse_sens);
	
	if( m_Mouse->GetPosition()->x < 0 )
	{
		m_Mouse->Warp( 0 , m_Mouse->GetPosition()->y);
	}	
	if( m_Mouse->GetPosition()->x > Core()->GetScreenWidth() )
	{
		m_Mouse->Warp( Core()->GetScreenWidth() , m_Mouse->GetPosition()->y);
	}
	if(  m_Mouse->GetPosition()->y < 0 )
	{
		m_Mouse->Warp( m_Mouse->GetPosition()->x , 0 );		
	}
	if( m_Mouse->GetPosition()->y > Core()->GetScreenHeight() )
	{
		m_Mouse->Warp(  m_Mouse->GetPosition()->x , Core()->GetScreenHeight() , 0) ;
	}
	
	m_Mouse->Process();
	
//	cout<<m_MousePosX<<" : "<<m_MousePosY<<endl;
}

void CDirectInput::MouseRender()
{
	m_Mouse->Render();
}