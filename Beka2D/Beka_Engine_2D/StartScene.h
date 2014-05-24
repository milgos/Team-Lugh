#pragma once

#include "Scene.h"
#include "Core.h"
#include "FileIO.h"
#include "ValuesHeader.h"
#include "UIObject.h"
#include "BackGround.h"
#include "CameraManager.h"

class CStartScene : public CScene
{
public:
	CStartScene(void); // 이 클래스의 모든 텍스쳐및 멤버변수 초기화
	~CStartScene(void); // 이 클래스의 모든 멤버변수를 할당해제

	bool Initialize(); // 텍스쳐 생성
	void UnInitialize(); // 이 씬에서 할당한 모든 것을 메모리에서 해제

	bool TextureInitialize();
	void TextureUnInitialize();

	void PrepareInput(); // 입력을 받는 부분
	void Process(); // 계산을 하는부분
	void Render(); // 화면에 그리는 부분 (모든 그리기 코드는 이곳에 와야함)

private:
	DWORD m_CurrentCursor; // 현재 가리키고 있는 위치
	bool m_Click; // 클릭 했는지

	float m_fStartTime;
	float m_fElapsedTime;

	CBackGround* BG1;
	CBackGround* BG2;

	CFileIO temp;
};