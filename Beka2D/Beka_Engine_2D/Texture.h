#pragma once

#include "Direct3D.h"
#include <vector>

typedef struct _ITexture
{
	LPDIRECT3DTEXTURE9 _Texture;
	D3DXIMAGE_INFO _imageifo;
}ITexture, *LPITexture;
// 이 구조체에는 텍스쳐와 이미지의 크기가 들어있다.

class CTexture
{
public:
	CTexture(void);
	~CTexture(void);
	bool LoadTexture();
	bool LoadTexture(LPITexture);
	bool LoadTexture( LPWSTR filename ); // 텍스쳐를 추가함, . 그리고 GetTexture()로 텍스쳐를 구한다.
	LPITexture GetTexture(){ return m_Texture;} // 텍스쳐 리턴, 매개변수는 추가한 순서로
	void ReleaseTexture(); 
private:
	LPITexture m_Texture;
};

