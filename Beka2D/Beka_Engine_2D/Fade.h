#pragma once

#include "UIObject.h"
#include "Transition.h"

class CFade : public CTransition // 일반적인 페이드효과
{
public:
	CFade(void);
	~CFade(void);

	void Initialize();
	void UnInitialize();

	void InitializeFill();  // 화면을 가릴 텍스쳐를 CFade기준으로 화면이 가려질 위치로
	void InitializeUnFill(); // 화면을 가릴 텍스쳐를 CFade기준으로 화면이 가려질 위치로
	void TransitionIn( short Speed, int& TransitionOption ); // 점점 안보이 지도록
	void TransitionOut( short Speed, int& TransitionOption ); // 점점 보이지도록

	void Render(); // CFade 페이드효과를 화면에 띄운다. (페이드 효과를 사용할 시 무조건 Render부분에 추가해야함)

private:
	CUIObject* FadeTex; // 페이드효과 텍스쳐

	short t1;
	DWORD dwTimeStart1;

	short t2;
	DWORD dwTimeStart2;
};