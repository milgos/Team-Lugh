#pragma once
// This class only used for the Running game
#include "UIObject.h"

enum{ RUN, JUMP, DOUBLEJUMP, BESHOT , FALL , HIGHFALL     };

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);

	void Init(int charactertype );
	void Render();
	void Process();
	
	void SetState(int val);
	D3DXVECTOR3* GetPosition() { return &m_position; }
private:
	CUIObject* m_Run; // ÇãÂS
	CUIObject* m_Jump;
	CUIObject* m_DJump;
	CUIObject* m_Beshot;
	CUIObject* m_Fall;
	CUIObject* m_HFall;	
	
	CUIObject** m_Current;
	
	int m_State;

	D3DXVECTOR3 m_position;
};

