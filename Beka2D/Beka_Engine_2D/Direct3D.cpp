#include <windows.h>
#include "Direct3D.h"
#include "DirectInput.h"
#include "Core.h"


CDirect3D::CDirect3D(void)
{
	// 객체가 생성 될 때 변수들의 값을 NULL로 초기화
	m_pD3D9 = NULL;
	m_pDevice = NULL;
	m_pSprite = NULL;
}

CDirect3D::~CDirect3D(void)
{
}

HRESULT CDirect3D::Initialize( HWND hWnd, int Screen_width, int Screen_height, bool Windowed, bool mBox )
{
	// SDK의 버젼을 확인하고 Direct3D9 객체를 만든다.
	if ( ( m_pD3D9 = Direct3DCreate9( D3D_SDK_VERSION ) ) == NULL )
	{
		if ( mBox == true )
		{
			MessageBox(hWnd, L"Direct3D Create Error!", L"Error!", MB_OK );
		}
		return E_FAIL;
	}

	////////////////////////////////////////////////////////
	// Parameter Seting 
	// Direct3D Device의 속성을 결정한다.
	////////////////////////////////////////////////////////
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));

	d3dpp.BackBufferWidth = Screen_width;
	d3dpp.BackBufferHeight = Screen_height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = Windowed; // 화면
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // 깊이 포맷
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; // 

	//////////////////////////////////////////////////////////
	// Create IDirect3D Device9 Interface
	//////////////////////////////////////////////////////////
	HRESULT hr;

	hr = m_pD3D9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pDevice);
	if( FAILED( hr ) )
	{
		if ( mBox == true )
		{
			MessageBox( hWnd, L"Direct3D Create Device Error!", L"Error!", MB_OK );
		}
		return E_FAIL;
	}

	// D3DXSPRITE 객체를 생성한다.
	if( FAILED( ::D3DXCreateSprite(m_pDevice, &m_pSprite) ) )
	{
		if ( mBox == true )
		{
			MessageBox( hWnd, L"Create Sprite Error!", L"Error!", MB_OK );
		}
		return E_FAIL;
	}

	m_pDevice->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, TRUE );
	m_pDevice->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );

	return S_OK;
}

void CDirect3D::UnInitialize()
{
	if( m_pSprite != NULL )
	{
		m_pSprite->Release();
		m_pSprite = NULL;
	}

	if( m_pDevice != NULL )
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	if( m_pD3D9 != NULL )
	{
		m_pD3D9->Release();
		m_pD3D9 = NULL;
	}
}

void CDirect3D::Render()
{
	if( NULL == m_pDevice) return;

	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_ARGB(255,255,255,255), 1.0f, 0);	// 후면 버퍼를 해당 속성으로 지운다.

	if( SUCCEEDED( m_pDevice->BeginScene() ) )
	{
		if( SUCCEEDED( m_pSprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK ) ) )
		{
			Core()->Render();
			//DirectInput()->MouseRender();
			// 모든 그리기 코드는 이 곳으로 와야 한다.
			//어차피 텍스쳐를 랜더링 하는거다 자세한것을 니가 알 필요는 없는거 같다.
			m_pSprite->End();
		}
		m_pDevice->EndScene();
	}

	if ( FAILED(m_pDevice->Present(NULL, NULL, NULL, NULL)) )
	{
		if ( Core()->ResolutionChange( 1280, 720, true ) == true );
			//std::cout << "SUCCEED" << std::endl;
	}
}
