#pragma once

#include"Texture.h"

class CUIObject
{
public:
	CUIObject(void);
	~CUIObject(void);

	bool Init();
	bool Init(LPITexture);
	bool Init(LPWSTR);

	void RemoveImage();

	void UnInit();

	void Process();
	void Render();

	void Move(float x= 0, float y = 0, float z = 0);
	void Warp(float x =0, float y = 0, float z = 0);
	
	void ConstMove(float x= 0, float y = 0, float z = 0);
	void ConstWarp(float x =0, float y = 0, float z = 0);
	
	void ChangeAlpha( WORD Alpha );

	void SetMaxFrame(int val);
	int GetMaxFrame(){return m_MaxFrame;}
	
	void SetFrameDelay(DWORD val){ m_FrameDelay = val; }
	int  GetFrameDelay(){ return m_FrameDelay; } 

	void SetOneLoop(){ isOneLoop = true; }
	void SetAutoLoop(bool val){ isAuto = val; }

	bool FrameNext();
	void FrameNum(int val);
	
	inline D3DXVECTOR3* GetPosition() { return &m_Position; }
	inline D3DXVECTOR3* GetConstPosition() { return &m_constPositon; }
private:
	CTexture*		 m_Tex;
	int				 width;
	int				 height;
	int				m_Alpha;

	D3DXVECTOR3		m_constPositon;
	D3DXVECTOR3		m_Position;
	RECT			m_SrcRect;
	D3DXMATRIX		m_matWorld;

	int				m_FrameDelay;
	int				m_CurrentFrame;
	int				m_MaxFrame;

	bool			isAuto;
	bool			isOneLoop;

};

