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
	// GetTickCount는 1초당 1000이야 이를 통해 해결하기에는
	// 현재 프로그램이 초당 만번 이상의 update를 수행하고있어 즉 GetTickCount를 통해 하기엔 무리야

	// 더 확실한 함수가 필요함 -> QueryperformanceCounter() 이는 초당 백만단위로 세고있다.

	QueryPerformanceCounter(&m_llCurCount);

	// 1초가 지날때 얼마나 카운트가 발생하는지
	// 이것도 고정수치가 아니므로 받아와야함
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// 이전 프레임의 카운팅과 현재 프레임의 카운팅의 차이를 구한다.
	// 이를 frequency 를 나누면 update 함수가 다시 호출될때까지의 시간이 나온다.
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
