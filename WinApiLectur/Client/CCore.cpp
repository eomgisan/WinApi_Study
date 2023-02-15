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
	// ������ �ڵ鷯�� ���� getDc �� ���� ����Ŵ� release�� �����
	ReleaseDC(m_hWnd, m_hDc);

	// createcompatable �λ����� DC�� release�� �ƴ� delete�� �����
	DeleteDC(m_memDc);
	DeleteObject(m_hBit);
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

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� dc�� �����.

	// compatible -> ���߿� m_hBit�� m_hDc�� ȣȯ�ؾ��ϴ� ȣȯ�� ����ؼ� ���Ǵ� �Լ����� �˷���
	m_hBit = CreateCompatibleBitmap(m_hDc, m_ptResolution.x, m_ptResolution.y);
	m_memDc = CreateCompatibleDC(m_hDc);


	// mem_Dc �� hBit �� ��������ִ°� �� �귯�� �ٲٴ°Ͱ� �����ž�
	// �⺻������ 1�ȼ�¥�� ��Ʈ�ʰ� ����Ǿ��־� �̰� �ʿ������ �ٷ� ����°�!
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDc, m_hBit);
	DeleteObject(hOldBit);

	// Manager �ʱ�ȭ

	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	return S_OK;
}


void CCore::process()
{
	// �޼��� �� ������ ó���� �ϵ�
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	// ��ü���� ������ Ȯ��
	CSceneMgr::GetInst()->update();


	//=============
	//==rendering==
	//=============

	// ȭ�� û�� ( ���� �ػ󵵺��� -1 , +1 �� ���� �������� ���� �׵θ����� ���������� )
	Rectangle(m_memDc, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1); // �̰� �ʹ� �����Ű�����
	
	CSceneMgr::GetInst()->render(m_memDc);

	// ���� �ٸ� DC���� �� �ȼ��� ��� ���ٽ�Ű��
	// ( ������, ũ��, �����, ���� ����, ��ɾ� )
	BitBlt(m_hDc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDc, 0, 0, SRCCOPY);

	// ���̻� �ƹ��� �׸��׸����ص� ���� ������ �ȶ����� �ֳĸ� �׸��°ͺ��� �ű�� �̷��� for���� ����� �ξ� ŭ
	// ���� Debug���� ǥ�� ���̺귯������ ����ó���� ���� �Ǿ��ִµ� Release��忡���� ����ó���� �� ������ �����鼭 
	// �������� �����Եȴ�.
	
}


HWND CCore::getHWND()
{
	return m_hWnd;
}
