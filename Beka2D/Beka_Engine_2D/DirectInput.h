#pragma once

#include <dinput.h>
#include "Singleton.h"
#include "UIObject.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

class CDirectInput : public CSingleton<CDirectInput> // 입력받는 객체
{
public:
	CDirectInput(void);
	~CDirectInput(void);

	bool					Initialize();
	void					UnInitialize();

	bool					TextureInitialize();

	void					TextureUnInitialize();
	void					MouseRender();
	void					MouseProcess();

	HRESULT					InitInputDevice( HWND hWnd ); // 입력을 받을 창을 설정 (윈도우 핸들)
	void					KeyboardUpdate();
	void					MouseUpdate();

	void					ReleaseInputDevice();

	bool					KeyDown( int KeyCode );
	bool					KeyPress( int KeyCode );
	bool					KeyUp( int KeyCode );

	inline void				CopyInputMemory()
	{
		memcpy( m_byPrevKeys, m_byCurrKeys, sizeof( m_byPrevKeys ) );
		m_PrevMouseState = m_CurrMouseState;
	}
	
	bool					LButtonDown();
	bool					RButtonDown();

	bool					LButtonPress();
	bool					RButtonPress();

	bool					LButtonUp();
	bool					RButtonUp();

	bool					CursorPositionCheck( long left, long top, long right, long bottom );

	long					GetCursorX(){ return m_CurrMouseState.lX; }
	long					GetCursorY(){ return m_CurrMouseState.lY; }

	D3DXVECTOR3*			GetMPos(){return m_Mouse->GetPosition();}
	float					GetMSens(){return m_Mouse_sens;}
	void					SetMSens(float val){ m_Mouse_sens = val;}

	LPDIRECTINPUT8			GetInputDevice(){ return m_pDirectInput8; }
private:
	
	CUIObject*					m_Mouse;
	float						m_Mouse_sens;

	LPDIRECTINPUT8				m_pDirectInput8;
	LPDIRECTINPUTDEVICE8		m_pKeyboard;
	LPDIRECTINPUTDEVICE8		m_pMouse;

	DIMOUSESTATE				m_CurrMouseState;
	DIMOUSESTATE				m_PrevMouseState;
	
	BYTE						m_byCurrKeys[256];
	BYTE						m_byPrevKeys[256];

	enum { LEFTMOUSE, RIGHTMOUSE };
};

#define DirectInput() CSingleton<CDirectInput>::InstancePtr()
