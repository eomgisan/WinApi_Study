#pragma once

// ��ũ�� �Լ�
// ������ : ���� �켱���� �� �����ؾ��� �ֳĸ� �̰��� �ڵ带 �ٲ��ִ°��� ���� ��ȯ�ϴ°��� �ƴϴ�.


// Singleton ��ũ��
#define SINGLE(type) public: static type* GetInst() {static type mgr; return &mgr;}\
					 private: type(); ~type();

// �Ʒ��� ����. �� ���͸� ġ�� ������ �������� �������� \ �� �߰��������
/*
#define SINGLE(tpye) 
public:
static type* GetInst()\
 {\
	static type mgr; \
	return &mgr;\
 }
 private: \
 type(); ~type(); \
 */

// Delta Time ��ũ��
#define fDT CTimeMgr::GetInst()->GetfDt()

// scene ������Ʈ �з��� �׷�
enum class GROUP_TYPE {
	DEFAULT,
	PLAYER,
	MISSILE,
	MONSTER,
	END = 32,
};

enum class SCENE_TYPE {
	TOOL,
	START,
	STAGE_1,
	STAGE_2,
	

	END,
};