#include "pch.h"
#include "CCore.h"
#include "CObject.h"


#include "CTimeMgr.h"
#include "CKeyMgr.h"
CObject g_obj;

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

	
	g_obj.SetPos(Vec2( (int)(m_ptResolution.x / 2) , (int)(m_ptResolution.y /2) ));
	g_obj.SetScale(Vec2( 100,100 ));

	return S_OK;
}


void CCore::process()
{
	// �޼��� �� ������ ó���� �ϵ�
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

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



	// �����̴� ���� �������̸� update Ƚ���� ��ǻ�� ���ɺ��� �ٸ��� �ӵ��� �޶���
	// �׷��Ƿ� �츮�� �������� �ƴ� ������ �����
	// �̵��� X (1/������) = �ʴ簡����� �̵���

	// ���� �������� ��� ��ȭ�ϴ� �Ŵ����� ���� ����ؼ� ����� �Ǿ����

	Vec2 vPos = g_obj.GetPos();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD) {
		vPos.x -= 200.f * fDT;
	}
	
	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD) {
		vPos.x += 200.f * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD) {
		vPos.y -= 200.f * fDT;
	}
	
	if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD) {
		vPos.y += 200.f * fDT;
	}

	g_obj.SetPos(vPos);

	
}


// ���� ���۸��� ���� �ܻ��� ������!
void CCore::render()
{
	// m_memDC�� �׸���


	// ȭ�� û�� ( ���� �ػ󵵺��� -1 , +1 �� ���� �������� ���� �׵θ����� ���������� )
	Rectangle(m_memDc, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1); // �̰� �ʹ� �����Ű�����


	// ���� �׸��� �ڵ� �κ��� ���⼭���� �׸���!!!!!!!!!!!!

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_memDc,
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));



	// m_hDc�� �ű��

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
