#pragma once
#include "CScene.h"

class CScene_Start :
	public CScene
{

public:
	virtual void Enter();
	// �̹� �θ� Ŭ�������� �����Լ� ������ �Ǿ��־� ��ó�� virtual Ű���� ���̵� ����
	// ������ �Ʒ�ó�� �־��ִ� ������ ������
	virtual void Exit();

public:
	CScene_Start();
	~CScene_Start();
};

