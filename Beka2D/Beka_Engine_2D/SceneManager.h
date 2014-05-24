#pragma once

#include "Scene.h"
#include "Singleton.h"

// 게임 내의 씬을 관리해 주는 클래스. 싱글톤화 되어있다.
// m_CurrentScene 변수에 씬을 저장 해 놓고 해당 씬만 업데이트, 입력처리, 그리기를 한다.

class CSceneManager : public CSingleton<CSceneManager> // 씬을 관리하는 클래스
{
public:
	CSceneManager(void);
	~CSceneManager(void);

	void TextureInitialize();
	void TextureUnInitialize();

	void ChangeScene( CScene* scene ); // 화면에 보여질 클래스를 교체함
	void DeleteScene(); // 현재 선택도어있는씬 제거
	void PrepareInput(); // 입력
	void Process();// 계산
	void Render(); // 랜더 (모든 그리기 함수는 이곳으로 와야함)
	CScene* GetCurrentScene() { return m_CurrentScene; }

private:
	CScene* m_CurrentScene; // 현재씬
};

#define SceneManager() CSingleton<CSceneManager>::InstancePtr() // 씬을 관리하는 클래스 (싱글톤)