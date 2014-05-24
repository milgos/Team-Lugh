#pragma once

#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "Singleton.h"

using namespace std;

enum
{
	Play, Stop
};


// 게임의 중앙관리자 같은 역할
// 게임의 초기화, 해제, 그리기, 처리 등을 전부 관리한다.
// 싱글톤화 되어있기 때문에 Core.h만 추가하면 어디서든 접근 가능하다.

class CCore : public CSingleton<CCore>
{
public:
	CCore(void);
	~CCore(void);

	bool			Initialize( HWND hWnd, int Screen_width, int Screen_height, bool Windowed ); // 윈도우핸들, 창의 크기, 창모드인지 전체화면인지를 받아서 해당 윈도우에 다이렉트x 를 초기화
	void			UnInitialize(); // 모두 해제

	bool			ResolutionChange ( int Screen_width, int Screen_height, bool Windowed );

	void			PrepareInput(); // 키보드 마우스 등의 사용자 입력 처리
	void			Process(); // 되도록이면 모든 처리는 이곳에
	void			Render(); // 출력 (모든 그리기 코드는 이곳에)

	inline HWND		GetMainHWND() { return m_hWnd; } // 메인 윈도우의 핸들을 반환.
	inline int		GetScreenWidth() { return m_ScreenWidth; } // 최초 설정된 화면의 넓이를 반환
	inline int		GetScreenHeight() { return m_ScreenHeight; } // 최초 설정된 화면의 높이를 반환.

	DWORD			MyGetTickCount();
	void			SetTickState( int val );
	void			TickProcess();

	void			FramePerSecond(); // 프레임 계산 함수
	float			GetElapsedTime() { return m_fElapsedTime; } // 한 프레임이 경과하기 까지의 경과시간을 반환하는 함수

	int Random( int Start, int End ) { return (rand()%End+Start+1)-Start;  }
private:
	HWND	m_hWnd; // 메인 윈도우의 핸들

	int		m_ScreenWidth; // 창의 크기 x
	int		m_ScreenHeight; // 창의 크기 y
	
	// 프레임의 계산에 사용되는 변수들
	DWORD	m_dwFPS_Frames;
	float	m_fFPS_LastTime;
	float	m_FPS_Time;

	float	m_fElapsedTime;
	int		m_iFPS_Num;

	int		m_TransitionOption; // 화면 전환용 변수

	DWORD	m_Tick;
	DWORD	m_TickFix;
	int		m_TickVal;

};

#define Core() CSingleton<CCore>::InstancePtr()
