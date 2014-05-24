#include "Texture.h"
#include "Core.h"

CTexture::CTexture(void)
{
}


CTexture::~CTexture(void)
{
}

bool CTexture::LoadTexture( )
{
	 m_Texture = new ITexture;
	 LPWSTR filename = L"Image\\Default\\Default_UI.png";

	if( FAILED( ::D3DXCreateTextureFromFileExW( Direct3D()->GetD3D9Device(), filename, 
		D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, &(m_Texture->_imageifo),
		NULL, &(m_Texture->_Texture)) ) )
	{
		WCHAR* ErrorMessage = new TCHAR[255];
		wsprintf(ErrorMessage,L"\"%s\"Image File Load Error!",filename);
		MessageBox( NULL, ErrorMessage, L"Error!", MB_OK );
		delete[] ErrorMessage;
		return false;
	}
	return true;
}
bool CTexture::LoadTexture(LPITexture Tex )
{
	m_Texture = Tex;
	return true;
}

bool CTexture::LoadTexture( LPWSTR filename )
{
	 m_Texture = new ITexture;

	if( FAILED( ::D3DXCreateTextureFromFileExW( Direct3D()->GetD3D9Device(), filename, 
		D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, &(m_Texture->_imageifo),
		NULL, &(m_Texture->_Texture)) ) )
	{
		WCHAR* ErrorMessage = new TCHAR[255];
		wsprintf(ErrorMessage,L"\"%s\"Image File Load Error!",filename);
		MessageBox( NULL, ErrorMessage, L"Error!", MB_OK );
		delete[] ErrorMessage;
		return false;
	}
	return true;
}

void CTexture::ReleaseTexture()
{
	m_Texture->_Texture->Release();
}
