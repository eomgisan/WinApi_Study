#pragma once

// ��ũ�� �Լ�
// ������ : ���� �켱���� �� �����ؾ��� �ֳĸ� �̰��� �ڵ带 �ٲ��ִ°��� ���� ��ȯ�ϴ°��� �ƴϴ�.


// Singleton ��ũ��
#define SINGLE(type) public: static type* GetInst() {static type mgr; return &mgr;}

// �Ʒ��� ����. �� ���͸� ġ�� ������ �������� �������� \ �� �߰��������
/*
#define SINGLE(tpye) static type* GetInst()\
 {\
	static type mgr; \
	return &mgr;\
 }
 */