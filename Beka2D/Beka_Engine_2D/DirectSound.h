#pragma once

#include <Windows.h>
#include <vector>
#include <mmsystem.h>
#include <dsound.h>
#include "Singleton.h"

#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")

class CDirectSound : public CSingleton<CDirectSound>
{
public:
	CDirectSound(void);
	~CDirectSound(void);

	
	
	HRESULT Initialize();
	void UnInitialize();
	void UnInitialize( int val );

	HRESULT Load_WaveFile( LPWSTR File_name ); // wav파일을 불러온다.
	void Set_Volume( LONG lVolume = 100 ); // 볼륨설정 기본값 100
	void Set_PlusVolume( LONG lVolume ); // 볼륨설정 기본값 100
	void Original_Set_Volume( LONG lVolume = -10000);
	void Play_Sound(); // 재생
	void Play_Sound( int fileindex, bool bloop = false ); // 사운드파일을 저장하고 있는 벡터에서 fileindex의 값의 위치에 있는 파일을 재생, 반복재생 할것인지
	void Stop_Sound(); // 정지
	void Stop_Sound( int fileindex ); // 사운드파일을 저장하고 있는 벡터에서 fileindex의 값의 위치에 있는 파일을 정지
	inline int GetVolume() { return m_Volume; }

private:
	int m_Volume;
	LPDIRECTSOUND							m_lpDirectSound; // DirectSound 객체
	std::vector< LPDIRECTSOUNDBUFFER >		m_SoundRepository; // 사운드파일을 저장하는 벡터
};

#define DirectSound() CSingleton<CDirectSound>::InstancePtr()