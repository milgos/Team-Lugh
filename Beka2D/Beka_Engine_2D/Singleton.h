#ifndef Singleton
#define Singleton

template <typename T> class CSingleton
{
public:
	// 함수를 처음 호출 할 때는 새로 동적할당을 하여 할당된 객체를 반환하며
	// 두번 째 부터는 이미 할당되어 있는 메모리의 주소를 반환한다.
	static T* InstancePtr()
	{
		if( m_Instance == 0 )
		{
			m_Instance = new T;
		}
		return m_Instance;
	}

	// 메모리를 해제하고 포인터를 NULL로 초기화한다.
	static void DestroyInstance()
	{
		if( m_Instance != 0 )
		{
			delete m_Instance;
			m_Instance = 0;
		}
	}

private:
	static T* m_Instance;
};

// m_Instance 변수를 NULL로 초기화 해 주기 위한 코드
template <typename T> T* CSingleton<T>::m_Instance = 0;

#endif