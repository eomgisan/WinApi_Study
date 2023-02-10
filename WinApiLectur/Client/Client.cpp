// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "Client.h"

#include "CCore.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


// SAL : 주석언어 msdn SAL 확인해보자
// _In_, _In_opt_ 등.. 특수한 주석으로 무시되는것이다. 해당 변수의 용도를 확인하는 것이다.
// _In_ : 입력해야만 하는거
// _In_opt_ : 옵션으로 선택해서 입력하는거 그니깐 뭐 입력해도 되고 안해도되지만 그냥 다 적어주자
// window의 구버전과 연동이 되기 위해서 이것을 안지우고 남겨둔것 같다.

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,             // 프로세스의 시작 주소
                     _In_opt_ HINSTANCE hPrevInstance,      // 같은 프로그램의 이전프로세스의 시작 주소 ( 같은 프로그램 여러개 킬때 )
                                                            // 현재는 같은 프로그램을 여러개 켜도 프로세스의 시작주소는 같다.
                                                            // 과거는 다른 프로세스 시작 주소를 가졌다. ( 현재는 가상메모리 시스템을 사용하기때문에 )
                     _In_ LPWSTR    lpCmdLine,              // LPWSTR 은 wchar_t의 포인터 타입으로써 cmd에서 커맨드로 프로그램 실행할수 있게 하는것
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);                  //  == (hPrevInstance) <- 컴파일러가 알아서 무시하고 삭제하는 라인이 된다.
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    
    
    MyRegisterClass(hInstance);                             // 윈도우 정보 등록




    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    
    // 코어 객체 초기화
    // 코어에는 윈도우 사이즈와 해상도를 설정하자 또한 윈도우핸들값을 가져야겠지!
    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{800, 600}))) {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"Error", MB_OK);

        return FALSE;
    }



    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));      
    // 단축키 테이블 정보 로딩  aceelerator 리소스뷰에 등록되어있다.
    // 단축키에 해당되는 ID값을 실행한다.





    MSG msg;


    /*
        // msg.hwnd : 발생한 윈도우 정보
    // 기본 메시지 루프입니다:
    // 메세지가 없으면 종료되는것이 아닌 대기하는것이다.
    while (GetMessage(&msg, nullptr, 0, 0))                      // 무한 반복문 (프로세스의 메세지 확인 될때까지 대기)
    {                                                            // GetMessage가 true 또는 false를 반환함
                                                                 // true : 메세지가 있는게 아닌 WM_QUIT이 아니면 다 ture
                                                                 // false : 프로그램 종료 -> 메세지가 없는게 아닌 프로그램 종료 메세지가 올때
                                                                 // msg.message == WM_QUIT 이 발생하면 false
                                                                 // 윈도우가 종료되고 모든것이 해제 되면 그 다음에 WM_QUIT이 발생
        // 메세지가 없으면 동작하지 않고 메세지가 있어야만 동작하게된다.
        // 이는 게임 개발에 부적합하다. 
        // 왜??? -> 메세지 큐에 들어올때까지 동작을 안해! 타이머를 통해 계속 렌더링 처리하게하기엔 너무 느린 프로그램이 되는거야
        // 그러므로 우리는 getmessage를 사용 안할거야 대신 peekMessage()를 사용 -> 가져오는것이 아닌 슬쩍 보는거야


         if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))                     // 단축키 정보등록된거 발생했나?
        {
            // 메세지 처리
            TranslateMessage(&msg);                         // 키보드 입력이 왔을때 연속된 문자열을 통해 메세지를 만듬
            DispatchMessage(&msg);                          // 메세지를 winproc 함수로 보냄
        }
    }
    */

    // peekMessage()는 getMessage의 인자 + 마지막에 옵션이 추가됨 메세지 있는지 확인하고 처리 방법을 정하는거야
    // PM_REMOVE를 통해 메세지를 삭제 시켜줘야 getMessage처럼 동작을 하며 메세지 큐가 계속 차있는걸 방지함

    // PeekMessage 는 항상 리턴값 반환
    // true : 메세지 있으면 
    // false : 메세지 없으면
    // 그러므로 while문의 조건으로 하기엔 부적합함
    DWORD dwTotalPrevCount = GetTickCount();
    DWORD dwMsgCount = 0;
    while (true) {

        // 메세지 처리시간과 메세지 처리안하는시간의 비율을 확인해보자
        // 시간체크는 GetTickCount(); 함수가 있다.
        // DWORD = unsigned long 4바이트 정수 , 1000 당 1초
       // DWORD dwPrevCount = GetTickCount();
        
        
        // 메세지가 있을경우 처리할거
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
           
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))                     // 단축키 정보등록된거 발생했나?
            {
                // 메세지 처리
                TranslateMessage(&msg);                         // 키보드 입력이 왔을때 연속된 문자열을 통해 메세지를 만듬
                DispatchMessage(&msg);                          // 메세지를 winproc 함수로 보냄
            }
            //DWORD dwCurCount = GetTickCount();
            //dwMsgCount += dwCurCount - dwPrevCount;

        }

        // 메세지 없을경우 처리할거 즉 백그라운드 작업은 여기에 하면된다
        else {
            
            // 하지만 메세지 기반이 아니기 때문에 우리 창이 포커스 되어있지않아도 동작할수도 있다.
            // 메세지 처리 기반은 포커스에 잡힐때만 처리되니 이것이 장점
            // 하지만 비동기 처리기반은 놀고있는 시간에 백그라운드 처리할수 있는게 장점

            // 메세지 처리 시간 비율 확인해보기 확인 결과 1퍼센트정도도 안됨
            /*DWORD dwNowCount = GetTickCount();

            if (dwNowCount - dwTotalPrevCount > 10000) {
                float a =  dwMsgCount / (dwNowCount - dwTotalPrevCount);
                wchar_t szBuff[50] = {};
                swprintf_s(szBuff, L"비율 : %f", a);
                SetWindowTextW(g_hWnd, szBuff);
            }
            */

            // 게임코드 수행
            // 디자인 패턴 ( 설계 유형 )
            // 자주 쓰이는 유형은 알아두자 하지만 모든 유형별로 알필요는.. 하지만 환경마다 자주 쓰이는게 다르다.
            // 싱글톤 패턴 ( 무조건 알아두기 )
            // 
            CCore::GetInst()->process();


        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);                             // nullptr 일 경우 메뉴바 사용 안함
    wcex.lpszClassName  = szWindowClass;                                            // initInstance 시 이 문자열을 가지고 프로세스를 찾는다
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   // hWnd == 커널 오브젝트인 윈도우의 id값 저장됨


   // createWindowW = 윈도우 객체 정보는 우리가 직접 건드리지 못해 커널obj라서 
   // 윈도우에 대해 size나 크기 이런거를 변경하고 싶으면 객체에 직접 접근을 못하고
   // 커널 오브젝트의 id값을 가져와서 함수에 id값을 넣어주는거야
   // createWIndowW 가 id값을 반환해줘

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//


// 메세지 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// 키보드 정보 : wParam -> 입력된 키보드 값
// 마우스 정보 : lParam -> 마우스의 좌표 ( 4바이트 값으로 y축 | x축 좌표를 나타내며 각 축별로 2바이트만큼 표현된다 )

{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:  
        // 무효화 영역 ( invalidate Rect == 가려졌던 부분이라는데 진짜일까..? 중단점 걸어서 확인해보자 )이 발생한 경우
        // 무효화 영역 = 그려진 영역이 비트맵 데이터로 어디인지 알고있어. 그러므로 요즘은 가려졌다 나와도 중단 안걸림

        {   // switch case안에서 새로운 지역변수 만들고 싶으면 {}로 묶어야해 


            PAINTSTRUCT ps; 
            
            

            // Device COntext 만들어서 id 반환 
            // BeginPaint : 메세지 처리기에서만 호출이 가능한 함수이다.
            HDC hdc = BeginPaint(hWnd, &ps);    
            // 윈도우 핸들 = 커널오브젝트의 id값을 가지고 있는거 커널오브젝트라서 객체에 직접 값에 접근 불가하므로 id값을 함수에 줌으로
            // 함수에서 커널 객체를 관리함
            // Device Context = 그리기 작업에 필요한 데이터들의 집합체 [ 펜, 브러시, 윈도우 ]
            // hdc 만들때 주어진 hWnd 이 윈도우 id, 펜 브러시는 기본펜 (black), 기본 브러시 (white)
            // 프로그래밍 할떄 실수 여지를 줄이기 위해 같은 int값 id이지만 서로다른 이름으로 자료형을 선언한다고 생각하면 된다.

        
            // 자료형이 맞는지를 어찌 확인함..? 그니깐 같은 int인데 이 값이 HDC인지 HWND인지 HPEN인지 어찌알아..? 
            
            // 직접 펜을 안들어 만들어서 DC에 지급
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255,0,0));

            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);
            // hdc에서 직접 값을 변경 불가능해 왜냐면 커널 오브젝트라 그러므로 모두 함수로 지정해줘야함

            

            // RGB 매크로 : B | G | R 의 구조로 3바이트가 색상을 표현함 define으로 정의되어 있는 매크로이다.
            // ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

            HBRUSH hMyBrush = CreateSolidBrush(RGB(0, 255, 0));

            // SelectObject는 hdc에 특정 object를 넣어주는 작업으로 반환은 변경전의 object이다.
            // 여러종류의 object를 변경할 수 있으므로 반환 타입은 현재 typedef void NEAR* HGDIOBJ; 으로 정의되어있다.
            // 즉 void이다 이를 캐스팅을 통해 반환값을 맞춰줌으로써 변경전의 값을 가져올수 있다.
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hMyBrush);



            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // 해상도 확인용
            // Rectangle(hdc, 0, 0, 800, 600);


            // 프레임이 너무 빨라서 화면 깜빡임 현상이 일어남 그러므로 그리는 작업을 60~100 프레임 사이로 맞춰줘야함 
            // 근데 그걸 못해 그러므로 우리는 깜빡임 현상을 없에기 위해 더블 렌더링을 사용해야함
            
            
            // hdc, 좌상단의 좌표, 우하단의 좌표
            // 윈도우 좌표
            // 메뉴바, 상단 타이틀바 제외한 나머지 영역이고 좌표단위는 픽셀단위이다.
            // 좌상단이 (0,0)이다.  우하단이 가장 큰값.


            // 원래거로 되돌려두기
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // 사용완료한 object는 os에게 삭제 요청
            DeleteObject(hRedPen);
            DeleteObject(hMyBrush);
 

            // 그리기 종료
            // 무효화 영역이 없다는 메세지를 전송함
            // 만약 EndPaint가 없다면 WM_PAINT가 메세지 큐에 무한히 쌓이게된다.
            EndPaint(hWnd, &ps);
        }


        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;


    // 키보드 입력 관련 처리 keydown을 계속 유지 시키면 한템포 조금 늦게 반응함
    // 키보드 입력시 꾹 누르고있으면 메세지가 계속 가는게 아니라 처음 1초정도 텀을 두고 그 이후에 계속 메세지를 보냄
  

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
