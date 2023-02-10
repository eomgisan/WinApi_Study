#include "pch.h"
#include "CCore.h"
#include "CObject.h"


CObject g_obj;

CCore::CCore() :
	m_hWnd(0),
	m_ptResolution({}),
	m_hDc(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDc);
}
int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	// 윈도우 함수의 대부분의 return 값은 HRESULT 자료형이다 변수이름은 주로 hr 이는 단순 long값이다.

	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;	


	// 해상도에 맞게 윈도우 크기 조정
	

	RECT rt = {0,0,_ptResolution.x, _ptResolution.y};

	// 우리가 원하는 해상도를 만들기 위한 창 크기는 윈도우 버전마다 달라
	// 그러므로 adjustWindowRect를 통해 만든다.

	// ( 사각형 포인터, 윈도우모양 설정, 메뉴바 설정여부 )
	// 리턴 = 인자로 넣어준 사각형 포인터의 참조값을 수정해서 반환함
	// 일반적으로 리턴값이 너무 커지면 레지스터가 힘들어함 왜냐면 리턴값은 레지스터에 저장되어있으니
	// 그러므로 포인터 받아와서 리턴값을 작게 만드는것이 일반적 -> C스타일
	// 객체의 멤버함수를 통해 변경 -> C++ 스타일
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);


	// 실제 해상도 결정 ( 메뉴, 타이틀, 왼쪽 오른쪽 창크기 제외 )

	// ( 윈도우, X , 시작 x, 시작y , x크기, y크기, X )
	SetWindowPos(_hWnd,nullptr, 100,10, rt.right-rt.left, rt.bottom-rt.top , 0);

	// BeginPaint 를 통해 hdc를 가져오는게 main에서 이루어지지만 이 함수는 메세지 처리기 함수에서만 호출이 가능하다.
	// 그러므로 윈도우에서 제공하는 getDc함수를 통해 hdc를 가져온다.
	m_hDc = GetDC(m_hWnd);

	g_obj.m_ptPos = POINT{ m_ptResolution.x/2, m_ptResolution.y/2 };
	g_obj.m_ptScale = POINT{ 100,100 };

	return S_OK;
}


void CCore::process()
{
	
	// 메세지 가 없을때 처리될 일들

	// 물체들의 변경점 확인
	update();

	// 그리기
	render();
	
	
}

void CCore::update()
{
	// 비동기식 키 입력 받기
	// 원래 리턴값은 키입력의 모든 로그를 줌 ( 과거에 눌린건지, 지금 눌린건지 다 합쳐서 )
	// 0x8000과 비트연산하면 지금 눌린건지 확인할수 있다.
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		g_obj.m_ptPos.x -= 1;
	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		g_obj.m_ptPos.x += 1;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		g_obj.m_ptPos.y += 1;
	}
	
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		g_obj.m_ptPos.x -= 1;
	}


	
}

void CCore::render()
{
	Rectangle(m_hDc,
		g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2,
		g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2,
		g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2,
		g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2
	);
}
