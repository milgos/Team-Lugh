#include "DirectSound.h"
#include "Core.h"

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define DSVOLUME_TO_DB(Volume)  ((DWORD)(-30*(100-Volume))) 


CDirectSound::CDirectSound(void)
{
	m_lpDirectSound = NULL;
	m_Volume = -100000;
}


CDirectSound::~CDirectSound(void)
{
}

HRESULT CDirectSound::Initialize()
{
	if( FAILED( DirectSoundCreate( NULL, &m_lpDirectSound, NULL ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( m_lpDirectSound->SetCooperativeLevel( Core()->GetMainHWND() , DSSCL_PRIORITY) ) )
	{
		return E_FAIL;
	}



	return S_OK;
}

void CDirectSound::UnInitialize()
{
	std::vector< LPDIRECTSOUNDBUFFER >::iterator  iter;	

	for(iter = m_SoundRepository.begin();  iter != m_SoundRepository.end(); ++iter )
	{
		SAFE_RELEASE( *iter );
	}

	m_SoundRepository.clear();

	if( m_lpDirectSound != NULL )
		SAFE_RELEASE( m_lpDirectSound );
}

void CDirectSound::UnInitialize( int val )
{
	int temp = val;
	std::vector<LPDIRECTSOUNDBUFFER>::iterator iter = m_SoundRepository.begin();
	while (temp--)
	{
		++iter;
	}

	SAFE_RELEASE( m_SoundRepository[val] );
	m_SoundRepository.erase(iter);
}

HRESULT CDirectSound::Load_WaveFile( LPWSTR File_name )
{
	std::vector< LPDIRECTSOUNDBUFFER >::iterator  iter;	

	LPDIRECTSOUNDBUFFER temp_sound;

	HMMIO wavefile;
	wavefile = mmioOpen (File_name, 0, MMIO_READ | MMIO_ALLOCBUF);

	if (wavefile == NULL) 
	{
		return E_FAIL;
	}

	MMCKINFO parent;
	memset (&parent, 0, sizeof(MMCKINFO));
	parent.fccType = mmioFOURCC ('W', 'A', 'V', 'E');
	mmioDescend (wavefile, &parent, 0, MMIO_FINDRIFF);

	MMCKINFO child;
	memset (&child, 0, sizeof(MMCKINFO));
	child.fccType = mmioFOURCC ('f', 'm', 't', ' ');
	mmioDescend (wavefile, &child, &parent, 0);

	WAVEFORMATEX wavefmt;
	mmioRead (wavefile, (char*)&wavefmt, sizeof(wavefmt));
	if(wavefmt.wFormatTag != WAVE_FORMAT_PCM)
	{
		return E_FAIL;
	}

	mmioAscend (wavefile, &child, 0);
	child.ckid = mmioFOURCC ('d', 'a', 't', 'a');
	mmioDescend (wavefile, &child, &parent, MMIO_FINDCHUNK);

	DSBUFFERDESC bufdesc;
	memset (&bufdesc, 0, sizeof(DSBUFFERDESC));
	bufdesc.dwSize = sizeof(DSBUFFERDESC);

	bufdesc.dwFlags = 0;
	bufdesc.dwBufferBytes = child.cksize;
	bufdesc.lpwfxFormat = &wavefmt;
	bufdesc.dwFlags = DSBCAPS_CTRLVOLUME;
	if( FAILED(m_lpDirectSound->CreateSoundBuffer (&bufdesc, &temp_sound, NULL) ) )
	{
		return E_FAIL;
	}

	void *write1 = 0, *write2 = 0;
	unsigned long length1,length2;
	temp_sound->Lock (0, child.cksize, &write1, &length1, &write2, &length2, 0);
	if(write1 > 0)
		mmioRead (wavefile, (char*)write1, length1);
	if (write2 > 0)
		mmioRead (wavefile, (char*)write2, length2);
	temp_sound->Unlock (write1, length1, write2, length2);

	m_SoundRepository.push_back( temp_sound );

	mmioClose (wavefile, 0);

	return S_OK;

}

void CDirectSound::Play_Sound()
{
	std::vector< LPDIRECTSOUNDBUFFER >::iterator  iter;	

	for(iter = m_SoundRepository.begin();  iter != m_SoundRepository.end(); ++iter )
	{
		(*iter)->SetCurrentPosition( 0 );
		(*iter)->Play( 0, 0, 0 );
	}
}

void CDirectSound::Play_Sound( int fileindex, bool bloop)
{
	m_SoundRepository[fileindex]->SetCurrentPosition( 0 );
	m_SoundRepository[fileindex]->Play(0, 0, bloop);
}

void CDirectSound::Stop_Sound()
{
	std::vector< LPDIRECTSOUNDBUFFER >::iterator  iter;	

	for(iter = m_SoundRepository.begin();  iter != m_SoundRepository.end(); ++iter )
	{
		(*iter)->Stop();
	}
}

void CDirectSound::Stop_Sound( int fileindex )
{
	m_SoundRepository[fileindex]->Stop();
}

void CDirectSound::Set_Volume( LONG lVolume )
{
	std::vector< LPDIRECTSOUNDBUFFER >::iterator  iter;
	
	for(iter = m_SoundRepository.begin(); iter != m_SoundRepository.end(); ++iter )
	{
		(*iter)->SetVolume( DSVOLUME_TO_DB(lVolume) );
	}  
	m_Volume = DSVOLUME_TO_DB(lVolume);
}

void CDirectSound::Set_PlusVolume( LONG lVolume )
{
	int temp = m_Volume + lVolume;
	if ( temp < -10000 || temp > 0)
	{
		return;
	}

	m_Volume += lVolume;

	std::vector< LPDIRECTSOUNDBUFFER >::iterator  iter;

	for(iter = m_SoundRepository.begin(); iter != m_SoundRepository.end(); ++iter )
	{
		(*iter)->SetVolume( m_Volume );
	}
}

void CDirectSound::Original_Set_Volume( LONG lVolume )
{
	std::vector< LPDIRECTSOUNDBUFFER >::iterator  iter;

	for(iter = m_SoundRepository.begin(); iter != m_SoundRepository.end(); ++iter )
	{
		(*iter)->SetVolume( lVolume );
	}
	m_Volume = lVolume;
}