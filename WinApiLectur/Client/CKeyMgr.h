#pragma once



// getasynckeystate�� ���� Ű �Է��� �������� ������

// ��������� �����Ǵ°� ���� ����, ���⼭ Ű�鿡 ���°��� �ο��ϰ� Ű�Ŵ����� ���� ������ ��Ŀ�� ������
// Ű�Է� �����ϴ� ��ɵ� �߰��غ���

// GetAsyncKeyState �Լ��� ���ϸ� if������ ���� Ȯ���ؾ� �˼��־�
// ���� 1������ ����������� Ű �Է� ���°� �ٲ���µ� getasynckeystate�� �̸� Ű�Է� ���� �ٲ�Ÿ� �˷���
// �׷��Ƿ� 1������ �ȿ��� Ű�Է� ���°� �ٲ�� �ִٴ°��̾�.
// �̴� ������ ����ȭ�� �̷������ �ʾҴٰ� ����

// keymanager�� ���ٰ��� ������ ����ȭ �۾��̾�
// �� �����ӿ��� �߻��� Ű�Է��� ������ ���¸� �ؾ��Ѵٴ°��̾�  �� 1�����Ӵ� Ű �Է��� fix ���ѵ־���


// �ؾ�����
// 1. ������ ����ȭ
// 2. Ű�Է� �̺�Ʈ ó�� : tap, hold, away
// 3. ��Ŀ�� ó��
// -> ���� ���ڱ� �������� ��Ŀ���� Ǯ���� tap���� �ٷ� none���� ���� away�ÿ� �߻��ؾ��ϴ� ������ ���۾��ϴϱ�.
// -> ��� Ű�� tap -> away -> none // hold -> away -> none ���� �����ؾ��Ѵ�.


enum class KEY {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,H,J,K,L,
	Z,X,C,V,B,
	ALT,
	CTRL,
	LSHIFT,

	ENTER,
	SPACE,
	ESC,
	

	LAST,			// ��
};


enum class KEY_STATE {
	TAP,			// �� ���� ����
	HOLD,			// ������ �ִ� ����
	AWAY,			// �� �� ����
	NONE,			// ������ �ʰ�, �������� ������ ���� ����
};

struct tKeyInfo {
	KEY_STATE	eState;			// �ش� Ű�� ����
	bool		bPrevPush;			// ���� �����ӿ��� ���ȴ��� ����
};

class CKeyMgr
{
SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;

public:
	void init();

	// �� �����Ӹ��� Ű ���� ������Ʈ
	void update();

	KEY_STATE GetKeyState(KEY _key);


};

