#pragma once

// ��ũ�� �Լ�
// ������ : ���� �켱���� �� �����ؾ��� �ֳĸ� �̰��� �ڵ带 �ٲ��ִ°��� ���� ��ȯ�ϴ°��� �ƴϴ�.


// Singleton ��ũ��
#define SINGLE(type) public: static type* GetInst() {static type mgr; return &mgr;}\
					 private: type(); ~type();

// �Ʒ��� ����. �� ���͸� ġ�� ������ �������� �������� \ �� �߰��������
/*
#define SINGLE(tpye) static type* GetInst()\
 {\
	static type mgr; \
	return &mgr;\
 }
 */

// Delta Time ��ũ��
#define fDT CTimeMgr::GetInst()->GetfDt()


enum class GROUP_TYPE {
	DEFAULT,

	PLAYER,

	MISSILE,

	MONSTER,


	END = 32,
};