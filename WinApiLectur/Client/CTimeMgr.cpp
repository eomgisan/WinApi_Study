#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"


CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDt(0.)
	, m_iCallCount(0)
{}

CTimeMgr::~CTimeMgr()
{}

void CTimeMgr::init()
{
	// GetTickCount�� 1�ʴ� 1000�̾� �̸� ���� �ذ��ϱ⿡��
	// ���� ���α׷��� �ʴ� ���� �̻��� update�� �����ϰ��־� �� GetTickCount�� ���� �ϱ⿣ ������

	// �� Ȯ���� �Լ��� �ʿ��� -> QueryperformanceCounter() �̴� �ʴ� �鸸������ �����ִ�.

	QueryPerformanceCounter(&m_llCurCount);

	// 1�ʰ� ������ �󸶳� ī��Ʈ�� �߻��ϴ���
	// �̰͵� ������ġ�� �ƴϹǷ� �޾ƿ;���
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// ���� �������� ī���ð� ���� �������� ī������ ���̸� ���Ѵ�.
	// �̸� frequency �� ������ update �Լ��� �ٽ� ȣ��ɶ������� �ð��� ���´�.
	m_dDt = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	m_llPrevCount = m_llCurCount;

	++m_iCallCount;

	m_dAcc += m_dDt;

	if (m_dAcc >= 1.) {

		m_iFPS = m_iCallCount;

		m_iCallCount = 0.;
		m_dAcc = 0.;

		wchar_t szBuffer[255] = {};

		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDt);

		SetWindowText(CCore::GetInst()->getHWND(), szBuffer);
	}
}

double CTimeMgr::GetDt()
{
	return m_dDt;
}

float CTimeMgr::GetfDt()
{
	return (float)m_dDt;
}
