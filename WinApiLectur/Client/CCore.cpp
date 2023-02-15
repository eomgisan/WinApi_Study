#include "pch.h"
#include "CCore.h"
#include "CObject.h"


#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"


CCore::CCore() :
	m_hWnd(0),
	m_ptResolution{},
	m_hDc(0),
	m_hBit(0),
	m_memDc(0)
{
}

CCore::~CCore()
{
	// 윈도우 핸들러로 만든 getDc 를 통해 만든거는 release로 지우기
	ReleaseDC(m_hWnd, m_hDc);

	// createcompatable 로생성된 DC는 release가 아닌 delete로 지우기
	DeleteDC(m_memDc);
	DeleteObject(m_hBit);
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

	// 더블 버퍼링 용도의 비트맵과 dc를 만든다.

	// compatible -> 나중에 m_hBit와 m_hDc와 호환해야하니 호환성 고려해서 사용되는 함수임을 알려줌
	m_hBit = CreateCompatibleBitmap(m_hDc, m_ptResolution.x, m_ptResolution.y);
	m_memDc = CreateCompatibleDC(m_hDc);


	// mem_Dc 와 hBit 와 연결시켜주는거 펜 브러시 바꾸는것과 같은거야
	// 기본적으로 1픽셀짜리 비트맵과 연결되어있어 이건 필요없으니 바로 지우는거!
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDc, m_hBit);
	DeleteObject(hOldBit);

	// Manager 초기화

	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	return S_OK;
}


void CCore::process()
{
	// 메세지 가 없을때 처리될 일들
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	// 물체들의 변경점 확인
	CSceneMgr::GetInst()->update();


	//=============
	//==rendering==
	//=============

	// 화면 청소 ( 실제 해상도보다 -1 , +1 을 통해 마지막에 남는 테두리까지 지워버리기 )
	Rectangle(m_memDc, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1); // 이건 너무 느릴거같은뎅
	
	CSceneMgr::GetInst()->render(m_memDc);

	// 서로 다른 DC끼리 각 픽셀을 모두 복붙시키기
	// ( 목적지, 크기, 출발지, 시작 지점, 명령어 )
	BitBlt(m_hDc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDc, 0, 0, SRCCOPY);

	// 더이상 아무리 그림그린다해도 거의 프레임 안떨어짐 왜냐면 그리는것보다 옮기고 이러는 for문이 비용이 훨씬 큼
	// 또한 Debug모드는 표준 라이브러리에서 예외처리가 많이 되어있는데 Release모드에서는 예외처리가 다 떨어져 나가면서 
	// 프레임이 오르게된다.
	
}


HWND CCore::getHWND()
{
	return m_hWnd;
}
