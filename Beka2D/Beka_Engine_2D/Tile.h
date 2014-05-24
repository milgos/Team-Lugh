#pragma once

#include "UIObject.h"
#include "Cameramanager.h"
#include "Core.h"

//타일 타입 등록하기
namespace TILE_TYPE
{
	enum
	{
		ON , BLOCK , LEFTUP , RIGHTIP, MOVED, // 레프트 /  라이트는 반대
	};
}

class CTile
{
public:
	CTile(void);
	~CTile(void);

	void init(LPCWSTR filename , float G_x , float G_y ,float zbuffer ,int type  );
	void init(LPITexture &iTex , float G_x , float G_y ,float zbuffer ,int type );
	void Render();
	void Process();
	
	void TileMove(float x , float y);
	int Getwidth(){return width;}
	int Getheigth(){return heigth;}
	int GetTileType(){ return Floortype; }
	LPITexture GetTex(){ return m_iTexture; }
	D3DXVECTOR3 GetCurPos(){return m_Position;}		
	
private:
	LPITexture	m_iTexture; // for the memory
	D3DXMATRIX			m_matWorld;
	RECT				m_SrcRect;
	D3DXVECTOR3			m_Position;
	D3DXVECTOR3			m_constPosition;

	int width;
	int heigth;
	
	int Floortype;

};


