#include "TileManager.h"


CTileManager::CTileManager(void)
{
}


CTileManager::~CTileManager(void)
{

}

void CTileManager::uninit()
{
	for(texiter = m_TexStuff.begin();texiter != m_TexStuff.end(); )
	{
		texiter = m_TexStuff.erase(texiter);
	}
}

void CTileManager::TexInit(LPCWSTR filename)
{
	m_TexStuff.push_back( new ITexture);
	texiter = m_TexStuff.begin();
	if( FAILED( ::D3DXCreateTextureFromFileExW( Direct3D()->GetD3D9Device(), filename, 
		D3DX_DEFAULT_NONPOW2,D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, &((*texiter)->_imageifo),
		NULL, &((*texiter)->_Texture)) ) )
	{
		WCHAR* ErrorMessage = new TCHAR[255];
		wsprintf(ErrorMessage,L"\"%s\"Image File Load Error!",filename);
		MessageBox( NULL, ErrorMessage, L"Error!", MB_OK );
		delete[] ErrorMessage;
	}
	++texiter;
}
void CTileManager::init()
{
	m_TexStuff.push_back( new ITexture);
	
	TexInit(L"Image\\Tile\\test_tile_On_1.png");

	texiter = m_TexStuff.begin();  //안전을 위하여
	
}


void CTileManager::AddTexture()
{

}

void CTileManager::AddTile(int type , float G_x , float G_y,float zbuffer)
{
	int i = 0;
	for(texiter = m_TexStuff.begin(); i < type ; ++i , ++texiter );
	
	LPITexture temp = *texiter;

	m_TileStuff.push_back( new CTile);

	tileiter = m_TileStuff.begin();	
	while( tileiter != m_TileStuff.end()  )
	{	
		++tileiter;
	}	
	--tileiter;

	(*tileiter)->init( temp , G_x , G_y , zbuffer , type);
}

void CTileManager::AllTileErase()
{
	for(tileiter = m_TileStuff.begin(); tileiter != m_TileStuff.end() ;  )
	{
		tileiter = m_TileStuff.erase(tileiter);
	}
}

void CTileManager::Process()
{
	for(tileiter = m_TileStuff.begin(); tileiter != m_TileStuff.end() ; ++tileiter )
	{
		(*tileiter)->Process();
	}
}

void CTileManager::Render()
{
	for(tileiter = m_TileStuff.begin(); tileiter != m_TileStuff.end() ; ++tileiter )
	{
		(*tileiter)->Render();
	}
}

TINFO CTileManager::StartPos()
{
	tileiter = m_TileStuff.begin();
	check.Pos =  (*tileiter)->GetCurPos();
	check.width = (*tileiter)->Getwidth();
	check.height =  (*tileiter)->Getheigth();
	return check;
}
TINFO CTileManager::GetTilePos(int num)
{
	if( num > m_TileStuff.size() )
	{
		WCHAR* ErrorMessage = new TCHAR[255];
		wsprintf(ErrorMessage,L"Out of vector",NULL);
		MessageBox( NULL, ErrorMessage, L"Error!", MB_OK );
	}
	else
	{
	check.Pos =  tileiter[num]->GetCurPos();
	check.width = tileiter[num]->Getwidth();
	check.height =  tileiter[num]->Getheigth();
	}
	return check;
}