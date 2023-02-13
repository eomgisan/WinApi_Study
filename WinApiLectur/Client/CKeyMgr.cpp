#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

int g_arrVK[(int)KEY::LAST] = {
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q',	'W',	'E',	'R',	'T',	'Y',	'U',	'I',	'O',	'P',
	'A',	'S',	'D',	'F',	'G',	'H',	'J',	'K',	'L',
	'Z',	'X',	'C',	'V',	'B',

	VK_MENU,	// alt
	VK_CONTROL, // ctl
	VK_LSHIFT,

	VK_RETURN,	// enter
	VK_SPACE,
	VK_ESCAPE	// esc
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{

	for (int i = 0; i < (int)KEY::LAST; ++i) {
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}


}


// �׷��� ���ʿ� ���⿡���� ������ �ȴ����� Ȯ���ϴ°� �񵿱��� �ƴѰ�..? �� ���Ŀ��� ������ ����ȭ�Ǳ� ������
// �̸� �ذ��� ����� ����
void CKeyMgr::update()
{
	HWND hMainWnd = CCore::GetInst()->getHWND();
	// GetFocus : ���� ��Ŀ�� �� �������� �ڵ鰪�� ��ȯ�� ���ٸ� 0 = nullptr
	HWND hWnd = GetFocus();

	// ���� ���� ���� ������� ���� �������� �ڵ鰪�� Ȯ���ϸ� ������ 
	// ���߿� â�� ������ ������ ���ݾ� �׷��Ƿ� �ϴ� null������ Ȯ���ϴ°ź��� ����������


	// �����찡 ��Ŀ�̵ɶ�
	if (hWnd != nullptr) {
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) {
				if (m_vecKey[i].bPrevPush) {
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else {
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}
			else {
				if (m_vecKey[i].bPrevPush == true) {
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else {
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}
	}

	// ������ ��Ŀ�� ����
	else {
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			m_vecKey[i].bPrevPush = false;
			if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD) {
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (m_vecKey[i].eState == KEY_STATE::AWAY) {
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}

	
}

KEY_STATE CKeyMgr::GetKeyState(KEY _key)
{
	return m_vecKey[(int)_key].eState;
}
