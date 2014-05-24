#pragma once

#include "Transition.h"
#include "Singleton.h"
#include "Fade.h"
#include "FadeLeft.h"
#include "FadeRight.h"

namespace TransitionOption // 화면 전환을 할 옵션 ( 끄기, 점점안보이게, 점점보이게)
{
	// Off : 끄기
	// In :: 점점 보이게
	// Out :: 점점 안보이게
	enum { Off, In, Out };
}

namespace TransitionType // 화면을 어떤 방식으로 전환할 것인지
{
	// Empty : 없음
	// Fade : 일반적인 페이드
	// FadeLeft : 왼쪽에서 오른쪽으로 점점 보여지는 페이드 효과 (어두워질때는 그 반대)
	// FadeRight : 오른쪽에서 왼쪽으로 점점 보여지는 페이드 효과 (어두워질때는 그 반대)
	enum { Empty, Fade, FadeLeft, FadeRight };
}

class CTransitionManager : public CSingleton<CTransitionManager> // 화면전환효과 (이 효과를 사용할시  해당 씬의 Render()부분에 이 클래스의 Render()함수를 추가 해야함)
{
public:
	CTransitionManager(void);
	~CTransitionManager(void);

	void UnInitialize();

	void SetTransition( int TransitionOptionNum, short Speed = 7 ); //  화면전환 효과
	inline int GetTransitionOption() { return m_TransitionOptionNum; } // 화면전환효과

	inline long GetTransitionType() // 현재 화면전환 타입을 리턴
	{ return m_CurrentTransitionType; }

	void TransitionChange( long TransitionType ); // 화면전환 효과를 입력받은 효과로 바꿈

	void ReInitialize();

	void InitializeFill(); // 현재 화면전환 효과에서의 텍스쳐를 화면이 가려질 위치로
	void InitializeUnFill(); // 현재 화면전환 효과에서의 텍스쳐를 화면이 보여질 위치로

	void TransitionIn( short Speed ); // 현재 화면전환 효과로 점점 안보이게
	void TransitionOut( short Speed ); // 현재 화면전환 효과로 점점 보이게

	void Render(); // 랜더 ( 화면전환 효과를 사용하려면 무조건 해당 씬에있는 Render()함수에 추가해야함 )

private:
	CTransition* m_CurrentTransition; // 현재 화면전환 효과의 클래스
	long m_CurrentTransitionType; // 현재 설정된 화면전환 효과
	int m_TransitionOptionNum;
};

#define TransitionManager() CSingleton<CTransitionManager>::InstancePtr() // 화면전환 효과 싱글톤
