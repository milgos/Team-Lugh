#pragma once

#include "UIObject.h"
#include "Transition.h"

class CFadeLeft : public CTransition // 왼쪽에서 오른쪽으로 점점 보여지는 페이드 효과 (어두워질때는 그 반대)
{
public:
	CFadeLeft(void);
	~CFadeLeft(void);

	void Initialize();
	void UnInitialize();

	void InitializeFill(); // 화면을 가릴 텍스쳐를 CFadeLeft기준으로 화면이 가려질 위치로
	void InitializeUnFill(); // 화면을 가릴 텍스쳐를 CFadeLeft기준으로 화면이 보여질 위치로
	void TransitionIn( short Speed, int& TransitionOption ); // 점점 보이도록
	void TransitionOut( short Speed, int& TransitionOption ); // 점점 안보이도록

	void Render(); // CFadeLeft 페이드효과를 화면에 띄운다. (페이드 효과를 사용할 시 무조건 Render부분에 추가해야함)

private:
	CUIObject* FadeTex; // 페이드효과 텍스쳐 (사각형)
	CUIObject* FadeTex2; // 페이드효과 텍스쳐(그라디언트)

	float PosX1;
	float PosX2;
};

#define FadeLeft() CSingleton<CFadeLeft>::InstancePtr() // CFadeLeft 싱글톤

