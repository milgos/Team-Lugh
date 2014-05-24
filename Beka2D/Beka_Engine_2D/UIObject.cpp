#include "UIObject.h"
#include "Core.h"

CUIObject::CUIObject(void)
{
	m_Tex = new CTexture;
	m_SrcRect.top = m_SrcRect.left = 0;
	m_MaxFrame = 1;
	isAuto = false;
	m_FrameDelay = 1000;
	m_CurrentFrame = 0;
}


CUIObject::~CUIObject(void)
{
}

bool CUIObject::Init()
{
	m_Tex->LoadTexture();
	width = m_Tex->GetTexture()->_imageifo.Width;
	height =  m_Tex->GetTexture()->_imageifo.Height;
	m_SrcRect.right = width;
	m_SrcRect.bottom = height;
	
	return true;
}

bool CUIObject::Init(LPITexture Tex)
{
	m_Tex->LoadTexture( Tex ) ;	
	width = m_Tex->GetTexture()->_imageifo.Width;
	height =  m_Tex->GetTexture()->_imageifo.Height;
	m_SrcRect.right = width;
	m_SrcRect.bottom = height;
	
	return true;
}

bool CUIObject::Init(LPWSTR filename)
{
	m_Tex->LoadTexture( filename ) ;	
	width = m_Tex->GetTexture()->_imageifo.Width;
	height =  m_Tex->GetTexture()->_imageifo.Height;
	m_SrcRect.right = width;
	m_SrcRect.bottom = height;
	
	return true;
}

void CUIObject::UnInit()
{
	if( m_Tex != NULL)
	{
		m_Tex->ReleaseTexture();
	}
	m_Tex = NULL;
}






void CUIObject::Render()
{
	Direct3D()->GetD3D9Sprite()->SetTransform(&m_matWorld);

	Direct3D()->GetD3D9Sprite()->Draw( m_Tex->GetTexture()->_Texture , &m_SrcRect, NULL, NULL, D3DCOLOR_ARGB(m_Alpha, 255,255,255));

}

void CUIObject::Process()
{
	static DWORD SpritePlayDelay = Core()->MyGetTickCount();
	if( SpritePlayDelay <= Core()->MyGetTickCount() - m_FrameDelay )
	{
		if( isAuto )
		{
			FrameNext();
		}

		if( isOneLoop && ! isAuto )
		{
			if( FrameNext() )
			{
				isOneLoop = false;
			}
		}
		SpritePlayDelay = Core()->MyGetTickCount();
	}


	D3DXMatrixTransformation(&m_matWorld, // 결과를 저장할 행렬주소
	NULL,	// 확대시에 기준점(NULL로 두면 그림의 왼쪽 상단)
	NULL,	// 확대를 할때의 방향(NULL로 두면 오른쪽 아랫방향으로 확대)
	NULL,	// X,Y확대율을 저장할 D3DXVECTOR3
	NULL,	// 회전을시킬때 중점
	NULL,	// 회전각
	&m_Position);	// 이동시킬위치
}






void CUIObject::Move( float x, float y, float z  )
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}

void CUIObject::Warp( float x, float y, float z  )
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void CUIObject::ConstMove( float x, float y, float z  )
{
	m_constPositon.x += x;
	m_constPositon.y += y;
	m_constPositon.z += z;
}

void CUIObject::ConstWarp( float x, float y, float z  )
{
	m_constPositon.x = x;
	m_constPositon.y = y;
	m_constPositon.z = z;
}

void CUIObject::ChangeAlpha( WORD Alpha )
{
	m_Alpha = Alpha;
}

void CUIObject::RemoveImage()
{
	if( m_Tex != NULL )
	{
		m_Tex->ReleaseTexture();
		m_Tex = NULL;
	}
	else
	{
		m_Tex = NULL;
	}
}

void CUIObject::SetMaxFrame(int val)
{
	m_MaxFrame = val;
	width /= m_MaxFrame;
	m_SrcRect.top	 = 0;
	m_SrcRect.left	 = m_CurrentFrame * width;
	m_SrcRect.right	 = m_SrcRect.left + width;
	m_SrcRect.bottom = height;
}

bool CUIObject::FrameNext()
{
	bool isDone = false;

	if( m_MaxFrame > 1 )
	{
		if( ++m_CurrentFrame >= m_MaxFrame)
		{
			isDone = true;
			m_CurrentFrame = 0;
		}
		
		m_SrcRect.top	 = 0;
		m_SrcRect.left	 = m_CurrentFrame * width;
		m_SrcRect.right	 = m_SrcRect.left + width;
		m_SrcRect.bottom = height;
	}
	return isDone;
}

void CUIObject::FrameNum(int val)
{
	if(val > m_MaxFrame)
	{
		val = 0;
	}
	m_CurrentFrame = val;
}