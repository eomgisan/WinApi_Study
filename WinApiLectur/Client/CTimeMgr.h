#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);


private:
	// ������ fps �� ���ؾ���
// 1�����Ӵ� �ð� : Delta Time
// 
	// ���� ī��Ʈ
	LARGE_INTEGER	 m_llCurCount;

	// ���� ī��Ʈ
	LARGE_INTEGER	m_llPrevCount;

	// �ʴ� ī��Ʈ�� �󸶳� �ö󰡴���
	LARGE_INTEGER	m_llFrequency;

	// ��Ÿ Ÿ��
	double			m_dDt;

	// ��Ÿ Ÿ�� ������ ���� 1�� ���� -> �̸� ���� FPS ���
	double			m_dAcc;

	// ȣ�� Ƚ��
	UINT			m_iCallCount;

	// FPS
	UINT			m_iFPS;

public:
	void init();

	// �� �����Ӹ��� ������Ʈ�ؾ���
	void update();

	double GetDt();
	float GetfDt();
};


