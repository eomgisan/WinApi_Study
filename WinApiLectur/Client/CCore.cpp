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
	// ������ �Լ��� ��κ��� return ���� HRESULT �ڷ����̴� �����̸��� �ַ� hr �̴� �ܼ� long���̴�.

	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;	


	// �ػ󵵿� �°� ������ ũ�� ����
	

	RECT rt = {0,0,_ptResolution.x, _ptResolution.y};

	// �츮�� ���ϴ� �ػ󵵸� ����� ���� â ũ��� ������ �������� �޶�
	// �׷��Ƿ� adjustWindowRect�� ���� �����.

	// ( �簢�� ������, �������� ����, �޴��� �������� )
	// ���� = ���ڷ� �־��� �簢�� �������� �������� �����ؼ� ��ȯ��
	// �Ϲ������� ���ϰ��� �ʹ� Ŀ���� �������Ͱ� ������� �ֳĸ� ���ϰ��� �������Ϳ� ����Ǿ�������
	// �׷��Ƿ� ������ �޾ƿͼ� ���ϰ��� �۰� ����°��� �Ϲ��� -> C��Ÿ��
	// ��ü�� ����Լ��� ���� ���� -> C++ ��Ÿ��
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);


	// ���� �ػ� ���� ( �޴�, Ÿ��Ʋ, ���� ������ âũ�� ���� )

	// ( ������, X , ���� x, ����y , xũ��, yũ��, X )
	SetWindowPos(_hWnd,nullptr, 100,10, rt.right-rt.left, rt.bottom-rt.top , 0);

	// BeginPaint �� ���� hdc�� �������°� main���� �̷�������� �� �Լ��� �޼��� ó���� �Լ������� ȣ���� �����ϴ�.
	// �׷��Ƿ� �����쿡�� �����ϴ� getDc�Լ��� ���� hdc�� �����´�.
	m_hDc = GetDC(m_hWnd);

	g_obj.m_ptPos = POINT{ m_ptResolution.x/2, m_ptResolution.y/2 };
	g_obj.m_ptScale = POINT{ 100,100 };

	return S_OK;
}


void CCore::process()
{
	
	// �޼��� �� ������ ó���� �ϵ�

	// ��ü���� ������ Ȯ��
	update();

	// �׸���
	render();
	
	
}

void CCore::update()
{
	// �񵿱�� Ű �Է� �ޱ�
	// ���� ���ϰ��� Ű�Է��� ��� �α׸� �� ( ���ſ� ��������, ���� �������� �� ���ļ� )
	// 0x8000�� ��Ʈ�����ϸ� ���� �������� Ȯ���Ҽ� �ִ�.
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
