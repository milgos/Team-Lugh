#include "Tile.h"


CTile::CTile(void)
{
}


CTile::~CTile(void)
{
	delete m_iTexture;
}


void CTile::init(LPCWSTR filename , float G_x , float G_y ,float zbuffer,int type)
{
	m_iTexture = new ITexture;
	
	if( FAILED( ::D3DXCreateTextureFromFileExW( Direct3D()->GetD3D9Device(), filename, 
		D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, &(m_iTexture->_imageifo),
		NULL, &(m_iTexture->_Texture)) ) )
	{
		WCHAR* ErrorMessage = new TCHAR[255];
		wsprintf(ErrorMessage,L"\"%s\"Image File Load Error!",filename);
		MessageBox( NULL, ErrorMessage, L"Error!", MB_OK );
		delete[] ErrorMessage;
	}

	
	m_SrcRect.top = m_SrcRect.left = 0;

	m_SrcRect.right = width = m_iTexture->_imageifo.Width;
	m_SrcRect.bottom = heigth = m_iTexture->_imageifo.Height;

	m_constPosition.x = G_x;
	m_constPosition.y = G_y;
	m_Position.z = zbuffer;

	m_Position.x = m_constPosition.x - Camera()->GetX();
	m_Position.y = m_constPosition.y - Camera()->GetY();

	Floortype = type;
}

void CTile::init(LPITexture &iTex , float G_x , float G_y ,float zbuffer ,int type  = TILE_TYPE::ON )
{
	m_iTexture = iTex;

	m_SrcRect.top = m_SrcRect.left = 0;

	m_SrcRect.right = width = m_iTexture->_imageifo.Width;
	m_SrcRect.bottom = heigth = m_iTexture->_imageifo.Height;

	m_constPosition.x = G_x;
	m_constPosition.y = G_y;
	m_Position.z = zbuffer;

	m_Position.x = m_constPosition.x - Camera()->GetX();
	m_Position.y = m_constPosition.y - Camera()->GetY();

	Floortype = type;	
}

void CTile::Process()
{
	m_Position.x = m_constPosition.x - Camera()->GetX();
	m_Position.y = m_constPosition.y - Camera()->GetY();

	D3DXMatrixTransformation(&m_matWorld, // 결과를 저장할 행렬주소
		NULL,	// 확대시에 기준점(NULL로 두시면 그림의 왼쪽 상단)
		NULL,	// 확대를 할때의 방향(NULL로 두시면 오른쪽 아랫방향으로 확대)
		NULL,	// X,Y확대율을 저장할 D3DXVECTOR2 변수(2차원백터에요)
		NULL,	// 회전을시킬때 중점
		NULL,	// 회전각
		&m_Position);	// 이동시킬위치
}

void CTile::Render()
{
	if( m_Position.x + width > 0 && m_Position.x < Core()->GetScreenWidth() )
		if( m_Position.y + heigth > 0 && m_Position.y < Core()->GetScreenHeight() )
		{
			Direct3D()->GetD3D9Sprite()->SetTransform(&m_matWorld);
			Direct3D()->GetD3D9Sprite()->Draw( m_iTexture->_Texture, &m_SrcRect, NULL, NULL,
				D3DCOLOR_ARGB( 255, 255, 255, 255 ));
		}
}

void CTile::TileMove(float x , float y)
{
	m_Position.x += x;
	m_Position.y += y;
}