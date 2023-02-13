#pragma once
#include "pch.h"
// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 너무 중요하니깐 1개로 제한하고 언제 어디든 접근 가능해야함 : 외부변수 extern
// 하지만 실수로라도 extern은 1개 제한 강제성이 없어
// 이를 불가능하게 하려면 아래의 방법이 있다.





/*
// 1.생성자를 숨기는거야. -> 생성자가 숨겨져서  외부변수 선언도 불가능해져... 이럼 객체를 못만들어
// 1-1. 자기스스로를 만들어주는 멤버함수로 만들자! 그리고 하나의 객체만 관리해서 그거를 반환하자
//     그런데 멤버함수를 호출하려면 애초에 해당 클래스가 존재해야하잖아 이건 어찌 처리하지?
//     객체가 없어도 멤버함수 호출 가능하게 하려면 static 키워드가 붙은 멤버함수!





class CCore
{
private:
	// 정적 멤버 변수는 선언 이후 클래스 밖에서 반드시 초기화 해줘야함 ( 이건 문법임 )
	static CCore* g_pInst;

public:

	// 객체 없이 호출가능하게 하는 키워드 : static 
	// 객체 없이 호출하므로 객체 멤버에 접근이 불가능.. -> this 키워드 사용 불가능 \
	// 하지만 정적 멤버는 접근 가능 ( static ) -> static이므로 
	// 정적변수 ( 데이터 영역에 선언됨 )
	// 1. 함수안에 선언되었을때 -> 함수의 종료와 상관없이 프로그램 끝날때 지워짐
	// 2. 파일에 선언되었을때 -> 파일 안에서만 접근이 가능하기 때문에 다른 파일의 같은 이름의 전역변수가 있어도 상관 없다.
	// 3. 클래스 안에 선언되었을때 -> 정적멤버 : 클래스 내부에서 언제나 접근 가능 -> 객체별로 다른게 아닌 클래스가 꼭 1개만 가짐
	//    즉 객체 여러개 만들어도 정적멤버 변수는 객체 메모리영역이 아닌 데이터영역에 존재 고로 접근시 this 키워드가 필요없다.

	static CCore* GetInstance() {
		// 최초 호출될경우
		if (nullptr == g_pInst) {
			CCore::g_pInst = new CCore;
		}
		return g_pInst;		
	}

	static void Release() {
		if (nullptr != g_pInst) {
			delete g_pInst;
			g_pInst = nullptr;
		}
	}

private :
	CCore();
	~CCore();
};
*/


// 2. 템플릿 상속


// 3. 데이터 영역 활용
// 아예 객체를 데이터 영역에 올리자

// 장점 : 해제에 신경쓸 필요 없다.
// 단점 : 지울수가 없다. 하지만 보통 싱글톤으로 제작하는 객체는 매니저 역할이 커
// 즉 매니저 역할은 많은 데이터를 가지고있는것이 아닌 여러것들의 참조만 가지고있으므로 그냥 들고다니는것도 나쁘진 않아

class CCore {
private:
	HWND		m_hWnd;			// 메인 윈도우 핸들러
	POINT		m_ptResolution;	// 메인 윈도우 해상도
	HDC			m_hDc;			// 그리기 커널 오브젝트


	// 이중 버퍼리을 위한 객체들
	HBITMAP		m_hBit;			
	HDC			m_memDc;
	/*
	static CCore* GetInst() {
		static CCore core;   
		// 여기서 정적 멤버변수를 선언하는거야 어쨌는 멤버함수니깐 이것이 가능함.

		// 주소를 주니깐 함수안에서 선언했다고 함수 안에서만 접근 가능한것이 아닌 밖에서도 포인터연산으로 접근이 가능하게됨
		return &core;
	}
	*/
	// 매크로 함수를 통해 위의 정의와 똑같이 만들기
	SINGLE(CCore);


public:
	int init(HWND _hWnd, POINT _ptResolution);
	void process();

private:
	void update();
	void render();

public:
	HWND getHWND();

};











// 지금까지의 3개의 방법중 정답은 없다.
