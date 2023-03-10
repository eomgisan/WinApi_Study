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


// 그런데 애초에 여기에서도 눌린지 안눌린지 확인하는게 비동기적 아닌가..? 그 이후에는 프레임 동기화되긴 하지만
// 이를 해결할 방법은 없낭
void CKeyMgr::update()
{
	HWND hMainWnd = CCore::GetInst()->getHWND();
	// GetFocus : 현재 포커스 된 윈도우의 핸들값을 반환함 없다면 0 = nullptr
	HWND hWnd = GetFocus();

	// 물론 현재 메인 윈도우와 현재 윈도우의 핸들값을 확인하면 되지만 
	// 나중에 창을 여러개 쓸수도 있잖아 그러므로 일단 null인지만 확인하는거부터 시작을하자


	// 윈도우가 포커싱될때
	if (hWnd != nullptr) {
		for (int i = 0; i < (int)KEY::LAST; ++i) {

			// 비동기식 키 입력 받기
			// 원래 리턴값은 키입력의 모든 로그를 줌 ( 과거에 눌린건지, 지금 눌린건지 다 합쳐서 )
			// 0x8000과 비트연산하면 지금 눌린건지 확인할수 있다.



			// 움직이는 값이 고정값이면 update 횟수가 컴퓨터 성능별로 다르니 속도가 달라져
			// 그러므로 우리는 고정값이 아닌 변수를 줘야함
			// 이동량 X (1/프레임) = 초당가고싶은 이동량

			// 또한 프레임은 계속 변화하니 매니저를 만들어서 계속해서 계산이 되어야함


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

	// 윈도우 포커싱 해제
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
