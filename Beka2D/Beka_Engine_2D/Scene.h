#pragma once

#define V(p) { if( (p) == false ) { return false; } }

class CScene // 순수 가상클래스로 씬을 만들 때는 반드시 이 클래스를 상속해서 사용할 것.
{
public:
	CScene(void);
	virtual ~CScene(void);

	virtual bool Initialize() = 0;
	virtual void UnInitialize() = 0;

	virtual bool TextureInitialize() = 0;
	virtual void TextureUnInitialize() = 0;

	virtual void PrepareInput() = 0;
	virtual void Process() = 0;
	virtual void Render() = 0;
};