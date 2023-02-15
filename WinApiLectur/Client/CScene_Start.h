#pragma once
#include "CScene.h"

class CScene_Start :
	public CScene
{

public:
	virtual void Enter();
	// 이미 부모 클래스에서 가상함수 선언이 되어있어 위처럼 virtual 키워드 없이도 ㄱㅊ
	// 하지만 아래처럼 넣어주는 습관을 들이자
	virtual void Exit();

public:
	CScene_Start();
	~CScene_Start();
};

