#pragma once

class CTransition
{
public:
	CTransition(void);
	virtual ~CTransition(void);

	virtual void Initialize() = 0;
	virtual void UnInitialize() = 0;
	virtual void InitializeFill() = 0;
	virtual void InitializeUnFill() = 0;
	virtual void TransitionIn( short Speed, int& TransitionOption ) = 0; // 어두웠던 화면에서 점점 밝아지게
	virtual void TransitionOut( short Speed, int& TransitionOption ) = 0; // 밝았던 화면에서 점점 어두워지게
	virtual void Render() = 0;
};

